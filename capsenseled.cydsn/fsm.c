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
#define SAMPLE_PERIOD 0.01 //seconds
#define SAMPLE_FREQ 100

alarm_state_e alarmStateOld = TYPE_NO_ALARM;

// Device modifies this 
alarm_state_e alarm_state    = TYPE_NO_ALARM;

// Configuration updated by the app
vib_type_e      curFireAlarmVibType      = VIBTYPE_CONTINUOUS;
vib_type_e      curAmbulanceVibType      = VIBTYPE_CONTINUOUS;
unsigned int    curVibDuration           = 5U;
bool            curAlarmDetectEnable     = 1;
bool            curAmbulanceDetectEnable = 1;

const unsigned int durationLUT[] = {5U, 10U, 20U, 30U};

// The state of the FSM.
static uint8 state;

// FSM Accumulator LPF queues
static queue_t low_prev;
static queue_t mid_prev;
static queue_t high_prev;
static queue_t fire_prev;
static queue_t low_deriv;
static queue_t mid_deriv;
static queue_t high_deriv;

// FSM Filter Accululators
static int low_count;
static int mid_count;
static int high_count;
static int fire_count;
static unsigned int liveness_count;
static int motor_pulse_count;
static int prev_low_count;
static int prev_mid_count;
static int prev_high_count;


void setFireAlarmVibType(int vibType){
    curFireAlarmVibType = vibType;
}

void setAmbulanceVibType(int vibType){
    curAmbulanceVibType = vibType;
}

void setVibDuration(int vibDuration){
    curVibDuration = durationLUT[vibDuration];
        
}

void setAlarmDetectEnable(int enable){
    curAlarmDetectEnable = enable;
}

void setAmbulanceDetectEnable(int enable){
    curAmbulanceDetectEnable = enable;
}


void fsm_init(void) {
    init_queue(&low_prev);
    init_queue(&mid_prev);
    init_queue(&high_prev);
    init_queue(&fire_prev);
    init_queue(&low_deriv);
    init_queue(&mid_deriv);
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
        
            init_queue(&low_deriv);
            init_queue(&mid_deriv);
            init_queue(&high_deriv);
        
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
            prev_mid_count = mid_count;
            prev_high_count = high_count;
            low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
            mid_count = filter_count(MID_FILTER_INPUT_Read(), &mid_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);
            fire_count = filter_count(FIRE_FILTER_INPUT_Read(), &fire_prev, fire_count);
            push(&low_deriv, low_count - prev_low_count);
            push(&mid_deriv, mid_count - prev_mid_count);
            push(&high_deriv, high_count - prev_high_count);
                    
                    
            // second derivative concavity test
            if ((sum(&low_deriv) == 0) && (peek(&low_deriv) == 1)) {
                low_count = 0;
                mid_count = 0;
                high_count = 0;
            }
                    
           /* all filter negative first derivative test */
            if ((sum(&low_deriv) == -6) && (sum(&mid_deriv) == -6) && (sum(&high_deriv) == -6)) {
                low_count = 0;
                mid_count = 0;
                high_count = 0;
            }                      
                    
            /* Check for fire alarm threshold. */
            if (curAlarmDetectEnable && fire_count > 800) {
                state = 5;
                liveness_count = 0;
                init_queue(&low_deriv);
                LED_RED_Write(LIGHT_ON);
            }
                    
            /* Check for siren threshold. */
            else if (curAmbulanceDetectEnable && (low_count > 25) && (mid_count > 5) && (high_count < 5) 
                    && (low_count >= mid_count) && peek(&mid_prev) && !peek(&high_prev)) {
                state = 2;
                low_count = 0;
                mid_count = 0;
                high_count = 0;
                fire_count = 0;
                liveness_count = 0;
                init_queue(&low_deriv);
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
            mid_count = filter_count(MID_FILTER_INPUT_Read(), &mid_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count); 

            if (liveness_count > 100) {
                state = 0;                    
                LED_BLUE_Write(LIGHT_OFF);
            }
            else if ((low_count <= mid_count) && (mid_count > 20) && (mid_count > high_count) 
                    && (high_count > 12) && peek(&high_prev)) {
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
            mid_count = filter_count(MID_FILTER_INPUT_Read(), &mid_prev, mid_count);
            high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);                    
                    
            if (liveness_count > 100) {
                state = 0;
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
            
        /* In this state, indicate detection of the siren. */
        case 4:
            motor_Write(MOTOR_ON);
            notifyAmbulance();
            state = 6;
            motor_pulse_count = 0;
            break;
                    
        /* In this state, indicate detection of the fire alarm */
        case 5:
            motor_Write(MOTOR_ON);
            notifyFireAlarm();
            state = 7;
            motor_pulse_count = 0;
            break;
                
        /* alert acknowledged by user */
        case 6:
            liveness_count++;
            if (alarm_state == TYPE_NO_ALARM || liveness_count > SAMPLE_FREQ*curVibDuration) {
                motor_Write(MOTOR_OFF);
                state = 0;
            }
            else if (curAmbulanceVibType == VIBTYPE_INTERVAL) {
                motor_pulse_count++;
                if (motor_pulse_count == SAMPLE_FREQ) {
                    motor_pulse_count = 0;
                }
                
                if (motor_pulse_count < SAMPLE_FREQ/2) {
                    motor_Write(MOTOR_ON);
                }
                else {
                    motor_Write(MOTOR_OFF);
                }
            }
            break;
            
        case 7:
            liveness_count++;
            if (alarm_state == TYPE_NO_ALARM || liveness_count > SAMPLE_FREQ*curVibDuration) {
                motor_Write(MOTOR_OFF);
                state = 0;
            }
            else if (curFireAlarmVibType == VIBTYPE_INTERVAL) {
                motor_pulse_count++;
                if (motor_pulse_count == SAMPLE_FREQ) {
                    motor_pulse_count = 0;
                }
                
                if (motor_pulse_count < SAMPLE_FREQ/2) {
                    motor_Write(MOTOR_ON);
                }
                else {
                    motor_Write(MOTOR_OFF);
                }
            }
        default:
            break;
    }        
}

void fsm_set_alarm_state(alarm_state_e state) {
    alarm_state = state;
}

/* [] END OF FILE */
