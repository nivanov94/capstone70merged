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

#include "project.h"
#include "IDAC.h"
#include "adc.h"

#define MAX_VOLTAGE 5.0
#define MIN_VOLTAGE 0.0

#define MAX_CURRENT_VAL 255

#define RESISTOR 15000
#define MAX_CURR 0.000306

#define FEEDBACK_GAIN 1.0
#define CONTROLLER_THRESH 0.02

#define FIRE_THRESH_INDEX 3

static uint8 IDAC_current = 0x00;
static float voltage_threshold = 1.4;

void init_IDAC(void) {
    
    IDAC_Fire_Thresh_Enable();
    
    IDAC_Fire_Thresh_Start();
    
    set_IDAC_current();
}

void set_IDAC_current(void) {
    
    IDAC_Fire_Thresh_SetValue(IDAC_current);
}

void update_IDAC_threshold(float volt_val) {
    
    /* call function to set value based on feedback*/
    if (volt_val < MAX_VOLTAGE && volt_val > 0) {
        voltage_threshold = volt_val;
    }
    else if (volt_val > MAX_VOLTAGE) {
        voltage_threshold = MAX_VOLTAGE;
    }
    else {
        voltage_threshold = 0;
    }
    
    set_IDAC_threshold();
    
}

void set_IDAC_threshold(void) {

    int delta;
    int new_current;
    float current_out = ADC_read(FIRE_THRESH_INDEX);
    float error = voltage_threshold - current_out;
    
    while (error > CONTROLLER_THRESH || error < -CONTROLLER_THRESH) {
        
        delta = (int)(error*FEEDBACK_GAIN*MAX_CURRENT_VAL/(RESISTOR*MAX_CURR));
        new_current = IDAC_current + delta;
    
        if (new_current <= MAX_CURRENT_VAL && new_current >= 0) {
            IDAC_current = new_current;
        }
        else if (new_current > MAX_CURRENT_VAL) {
            IDAC_current = MAX_CURRENT_VAL;
        }
        else {
            IDAC_current = 0;
        }
    
   
    
        set_IDAC_current();
        CyDelay(500);
        
        current_out = ADC_read(FIRE_THRESH_INDEX);
        error = voltage_threshold - current_out;
    }

}    


/* [] END OF FILE */
