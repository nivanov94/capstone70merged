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

#ifndef PWM_H
#define PWM_H
    
#include <project.h>
    
void init_PWM(void);
void update_PWM_threshold(float volt_value, int thresh_index);
void set_PWM_duty_cycles(int thresh_index);
void set_PWM_threshold(int thresh_index); 
    
#endif

/* [] END OF FILE */
