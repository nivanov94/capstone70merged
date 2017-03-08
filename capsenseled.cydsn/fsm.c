/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "fsm.h"
#include "queue.h"
#include "filter.h"
#include "user_cfg_def.h"
#include "BLE.h"
#include <stdbool.h>

#define LIGHT_ON  0u
#define LIGHT_OFF 1u
#define MOTOR_ON  1u
#define MOTOR_OFF 0u

alarm_state_e alarmStateOld = TYPE_NO_ALARM;

// Device modifies this 
alarm_state_e alarm_state    = TYPE_NO_ALARM;

// Configuration updated by the app
vib_type_e      curFireAlarmVibType      = VIBTYPE_CONTINUOUS;
vib_type_e      curAmbulanceVibType      = VIBTYPE_CONTINUOUS;
vib_duration_e  curVibDuration           = DURATION_5S;
bool            curAlarmDetectEnable     = 1;
bool            curAmbulanceDetectEnable = 1;

// The state of the FSM.
static uint8 state;

// FSM Accumulator LPF queues
static queue_t low_prev;
static queue_t med_prev;
static queue_t high_prev;
static queue_t fire_prev;
static queue_t slope_detect;
static queue_t med_deriv;
static queue_t high_deriv;

// FSM Filter Accululators
static int low_count;
static int mid_count;
static int high_count;
static int fire_count;
static int liveness_count;
static int prev_low_count;
static int prev_med_count;
static int prev_high_count;


void setFireAlarmVibType(int vibType){
    curFireAlarmVibType = vibType;
}

void setAmbulanceVibType(int vibType){
    curAmbulanceVibType = vibType;
}

void setVibDuration(int vibDuration){
    curVibDuration = vibDuration;
}

void setAlarmDetectEnable(int enable){
    curAlarmDetectEnable = enable;
}

void setAmbulanceDetectEnable(int enable){
    curAmbulanceDetectEnable = enable;
}


void fsm_init(void) {
    init_queue(&low_prev);
    init_queue(&med_prev);
    init_queue(&high_prev);
    init_queue(&fire_prev);
    init_queue(&slope_detect);
    init_queue(&med_deriv);
    init_queue(&high_deriv);
    
    state = 0;
    liveness_count = 0;
    
    low_count = 0;
    mid_count = 0;
    high_count = 0;
    fire_count = 0;
}

void fsm_tick(void) {
    
    switch(state) {
                
        /* This is the state that is entered upon reset */
        case 0:
            low_count = 0;
            mid_count = 0;
            high_count = 0;
            fire_count = 0;
            liveness_count = 0;
        
            LED_GREEN_Write(LIGHT_OFF);
            LED_BLUE_Write(LIGHT_OFF);
            LED_RED_Write(LIGHT_OFF);
            state = 1;
            break;
                
        /* In this state, keep a running count of each filtered input.
         * If the counts exceed certain thresholds, proceed to either the
         * alarm recognition state or the siren recognition state.
         */
        case 1:
            prev_low_count = low_count;
            prev_med_count = mid_count;
            prev_high_count = high_count;
            low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
            mid_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);
            fire_count = filter_count(FIRE_FILTER_INPUT_Read(), &fire_prev, fire_count);
            push(&slope_detect, low_count - prev_low_count);
            push(&med_deriv, mid_count - prev_med_count);
            push(&high_deriv, high_count - prev_high_count);
                    
                    
            // second derivative concavity test
            if ((sum(&slope_detect) == 0) && (peek(&slope_detect) == 1)) {
                low_count = 0;
                mid_count = 0;
                high_count = 0;
            }
                    
           /* all filter negative first derivative test */
            if ((sum(&slope_detect) == -6) && (sum(&med_deriv) == -6) && (sum(&high_deriv) == -6)) {
                low_count = 0;
                mid_count = 0;
                high_count = 0;
            }                      
                    
            /* Check for fire alarm threshold. */
            if (curAlarmDetectEnable && fire_count > 800) {
                state = 5;
                liveness_count = 0;
                init_queue(&slope_detect);
                LED_RED_Write(LIGHT_ON);
            }
                    
            /* Check for siren threshold. */
            else if (curAmbulanceDetectEnable && (low_count > 25) && (mid_count > 5) && (high_count < 5) && (low_count >= mid_count)) {
                state = 2;
                low_count = 0;
                mid_count = 0;
                high_count = 0;
                fire_count = 0;
               liveness_count = 0;
                init_queue(&slope_detect);
                LED_BLUE_Write(LIGHT_ON);
            }        
            break;
                
        /* In this state, check to see if the medium frequency range has been
         * captured. If the signal remains too low for too long, return back to the 
         * initial stage.
         */
        case 2:
            liveness_count++;
            low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
            mid_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count); 

            if (liveness_count > 100) {
                state = 0;                    
                LED_BLUE_Write(LIGHT_OFF);
            }
            else if ((low_count <= mid_count) && (mid_count > 20) && (mid_count > high_count) && (high_count > 12)) {
                state = 3;
                low_count = 0;
                mid_count = 0;
                high_count = 0;
                fire_count = 0;
                liveness_count = 0;
            }                                            
            break;
                    
        case 3:
            liveness_count++;
            low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
            mid_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);                    
                    
            if (liveness_count > 100) {
                state = 0;
                low_count = 0;
                mid_count = 0;
                high_count = 0;
                fire_count = 0;
                liveness_count = 0;
                LED_BLUE_Write(LIGHT_OFF);
            }
            else if ((low_count < 20) && (mid_count < 30) && (high_count > 95)) {
                state = 4;
                low_count = 0;
                mid_count = 0;
                high_count = 0;
                fire_count = 0;
                liveness_count = 0;
                LED_BLUE_Write(LIGHT_OFF);
                LED_GREEN_Write(LIGHT_ON);
            }
            break;
            
        /* In this state, indicate detection of the fire alarm. */
        case 4:

            motor_Write(MOTOR_ON);
            notifyAmbulance();
            state = 6;
            break;
                    
        /* In this state, indicate detection of the fire alarm */
        case 5:

            motor_Write(MOTOR_ON);
            notifyFireAlarm();
            state = 6;                   
            break;
                
        /* alert acknowledged by user */
        case 6:
            if (alarm_state == TYPE_NO_ALARM) {
                motor_Write(MOTOR_OFF);
                state = 0;
            }
        default:
            break;
    }        
}

void fsm_set_alarm_state(alarm_state_e state) {
    alarm_state = state;
}

/* [] END OF FILE */
