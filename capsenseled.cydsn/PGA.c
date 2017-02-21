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

#include "PGA.h"
#include "project.h"

#define TAP_POSITIONS  32
#define MAX_RESISTANCE 200000
#define GAIN_DENOM     2200

#define LOW  0u
#define HIGH 1u

static uint8 current_tap_pos = 15; //tap positon set to midscale on reset

void PGA_set_gain(float gain) {
    float resistance = gain*GAIN_DENOM;
    
    if (resistance > MAX_RESISTANCE) {
        resistance = MAX_RESISTANCE;
    }
    
    PGA_program_resistor(resistance);
}

void PGA_program_resistor(float resistance) {

    uint8 new_tap_pos = resistance*(TAP_POSITIONS-1)/MAX_RESISTANCE;
    int tap_pos_diff = new_tap_pos - current_tap_pos;
    int i;
    
    PGA_CS_Write(LOW);
    if (tap_pos_diff > 0) {
        PGA_U_Db_Write(HIGH);
        for (i = 0; i < tap_pos_diff; i++) {
            PGA_INC_Write(LOW);
            PGA_INC_Write(HIGH);
        }
    }
    else {
        PGA_U_Db_Write(LOW);
        for (i = tap_pos_diff; i < 0; i++) {
            PGA_INC_Write(LOW);
            PGA_INC_Write(HIGH);
        }
    }
    
    PGA_CS_Write(HIGH);
    current_tap_pos = new_tap_pos;
}

/* [] END OF FILE */
