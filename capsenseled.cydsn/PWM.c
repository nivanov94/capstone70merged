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



#include "PWM.h"
#include <project.h>
#include "adc.h"

#define MAX_VOLTAGE 5.0
#define MIN_VOLTAGE 0.0

#define PWM_PERIOD 200.0

#define LOW_FILT  0
#define MID_FILT  1
#define HIGH_FILT 2

#define FEEDBACK_GAIN 0.9
#define CONTROLLER_THRESH 0.08
#define TOLERANCE 0.02

static uint8 PWM_duty_cycles[] = {0, 0, 0};
static float voltage_thresholds[] = {1.2, 1.2, 1.15};

void init_PWM(void) {
    
    PWM_Low_Thresh_Start();
    PWM_Mid_Thresh_Start();
    PWM_High_Thresh_Start();
    
    Clock_PWM_Start();
}

void set_PWM_duty_cycles(int thresh_index) {
    
    if (thresh_index == LOW_FILT) {
        PWM_Low_Thresh_WriteCompare(PWM_duty_cycles[LOW_FILT]);
    }
    else if (thresh_index == MID_FILT) {
        PWM_Mid_Thresh_WriteCompare(PWM_duty_cycles[MID_FILT]);
    }
    else {
        PWM_High_Thresh_WriteCompare(PWM_duty_cycles[HIGH_FILT]);
    }
}

void update_PWM_threshold(float volt_val, int thresh_index) {
    
    if (volt_val < MAX_VOLTAGE && volt_val > MIN_VOLTAGE) {
        voltage_thresholds[thresh_index] = volt_val;
    }
    else if (volt_val > MAX_VOLTAGE) {
        voltage_thresholds[thresh_index] = MAX_VOLTAGE;
    }
    else {
        voltage_thresholds[thresh_index] = MIN_VOLTAGE;
    }
    
    set_PWM_threshold(thresh_index);
}

void set_PWM_threshold(int thresh_index) {
   
    int delta;
    int new_duty_cycle;
    float current_out = ADC_read(thresh_index);
    float error = voltage_thresholds[thresh_index] - current_out;
    
    while (error > CONTROLLER_THRESH || error < -CONTROLLER_THRESH) {
        
        delta = (int)(error*FEEDBACK_GAIN*PWM_PERIOD/MAX_VOLTAGE);
        new_duty_cycle = PWM_duty_cycles[thresh_index] + delta;
    
        if (new_duty_cycle <= PWM_PERIOD && new_duty_cycle >= 0) {
            PWM_duty_cycles[thresh_index] = new_duty_cycle;
        }
        else if (new_duty_cycle > PWM_PERIOD) {
            PWM_duty_cycles[thresh_index] = 100;
        }
        else {
            PWM_duty_cycles[thresh_index] = 0;
        }
 
    
        set_PWM_duty_cycles(thresh_index);
        CyDelay(100);
        
        current_out = ADC_read(thresh_index);
        error = voltage_thresholds[thresh_index] - current_out;
    }

    
    while (error > TOLERANCE || error < -TOLERANCE) {
        if (error > 0 && PWM_duty_cycles[thresh_index] < 200 ) {
            PWM_duty_cycles[thresh_index]++;
        }
        else if (PWM_duty_cycles[thresh_index] > 0) {
            PWM_duty_cycles[thresh_index]--;
        }

        set_PWM_duty_cycles(thresh_index);
        CyDelay(100);
        current_out = ADC_read(thresh_index);
        error = voltage_thresholds[thresh_index] - current_out;
    }

}
/* [] END OF FILE */
