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

#ifndef FSM_H
#define FSM_H
    
#include "user_cfg_def.h"
    
void fsm_init(void);
void fsm_tick(void);

void setFireAlarmVibType(int vibType);
void setAmbulanceVibType(int vibType);
void setVibDuration(int vibDuration);
void setAlarmDetectEnable(int enable);
void setAmbulanceDetectEnable(int enable);
void fsm_set_alarm_state(alarm_state_e status);

#endif

/* [] END OF FILE */
