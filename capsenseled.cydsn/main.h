/*******************************************************************************
* File Name: main.h
*
* Version: 1.30
*
* Description:
*  BLE HID keyboard example project that supports both input and output reports
*  in boot and protocol mode. The example also demonstrates handling suspend 
*  event from the central device and enters low power mode when suspended.
*
* References:
*  BLUETOOTH SPECIFICATION Version 4.1
*  HID Usage Tables spec ver 1.12
*
* Hardware Dependency:
*  CY8CKIT-042 BLE
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H
#include "OTAMandatory.h"
#include "OTAOptional.h"
#include "common.h"

/*


void AppCallBack(uint32 event, void* eventParam);

extern CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteAttributeValue
		(
            CYBLE_GATT_HANDLE_VALUE_PAIR_T	* handleValuePair,
            uint16                          offset,
            CYBLE_CONN_HANDLE_T       		* connHandle,
            uint8                           flags
		);
        
extern CYBLE_API_RESULT_T CyBle_GapFixAuthPassKey(uint8 isFixed, uint32 fixedPassKey);
*/
    
void notifyAmbulance();
void notifyFireAlarm();
#endif /* MAIN_H */

/* [] END OF FILE */
