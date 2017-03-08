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
#if !defined(BLE_H)
#define BLE_H
#include "OTAMandatory.h"
#include "OTAOptional.h"
#include "common.h"


void AppCallBack(uint32 event, void* eventParam);

extern CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteAttributeValue
		(
            CYBLE_GATT_HANDLE_VALUE_PAIR_T	* handleValuePair,
            uint16                          offset,
            CYBLE_CONN_HANDLE_T       		* connHandle,
            uint8                           flags
		);
        
extern CYBLE_API_RESULT_T CyBle_GapFixAuthPassKey(uint8 isFixed, uint32 fixedPassKey);

void notifyAmbulance();
void notifyFireAlarm();

#endif
/* [] END OF FILE */
