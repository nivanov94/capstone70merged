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
#include "OTAOptional.h"
#include "common.h"
#include "CyBLE_custom.h"
#include "BLE.h"
#include "user_cfg_def.h"
#include "fsm.h"

void notifyFireAlarm() {
    
    alarm_state_e temp_alarm_state = TYPE_FIRE_ALARM;
    
    fsm_set_alarm_state(TYPE_FIRE_ALARM);
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;

	CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;

    tempHandle.attrHandle = CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *)&temp_alarm_state;
    tempHandle.value.len = 2; 
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    
    /* send notification to client*/
    CyBle_GattsNotification(cyBle_connHandle,&tempHandle);

}

void notifyAmbulance(){
    alarm_state_e temp_alarm_state = TYPE_AMBULANCE;
    
    fsm_set_alarm_state(TYPE_AMBULANCE);
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;

	CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;

    tempHandle.attrHandle = CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *)&temp_alarm_state;
    tempHandle.value.len = 2; 
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    
    /* send notification to client*/
    CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
}


void AppCallBack(uint32 event, void* eventParam);


/***************************************************************
 * Function to update the LED state in the GATT database
 **************************************************************/
void updateLed()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
   
    //uint8 red_State = !red_Read();
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    tempHandle.attrHandle = CYBLE_LEDCAPSENSE_LED_CHAR_HANDLE;
  	//tempHandle.value.val = (uint8 *) &red_State;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED);  
}
    

/***************************************************************
 * Function to handle the BLE stack
 **************************************************************/
void AppCallBack(uint32 event, void* eventParam)
{
    char str[100];
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    CYBLE_GAP_AUTH_INFO_T *authInfo;

    UART_PutString("CY8CKIT-042 USB-UART");

    UART_PutString("event: ");
    
    sprintf(str, "%lu\n", event);
    UART_PutString(str);
    
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GAP_BD_ADDR_T localAddr;
    uint8 i;
    
    switch(event)
    {
        /* if there is a disconnect or the stack just turned on from a reset then start the advertising and turn on the LED blinking */
        
        case CYBLE_EVT_STACK_ON: 
        /* Enter into discoverable mode so that remote can search it. */
            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(apiResult != CYBLE_ERROR_OK)
            {
                sprintf(str, "StartAdvertisement API Error: %d \r\n", apiResult);
                UART_PutString(str);
            }
            sprintf(str,"Bluetooth On, StartAdvertisement with addr: ");
            UART_PutString(str);
            localAddr.type = 0u;
            CyBle_GetDeviceAddress(&localAddr);
            for(i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
            {
                sprintf(str,"%2.2x", localAddr.bdAddr[i-1]);
                UART_PutString(str);
            }
            sprintf(str,"\r\n");
            UART_PutString(str);
            
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            UART_PutString("Disconnected\n");
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            //blue_Write(0);
            //red_Write(1);
        break;
        case CYBLE_EVT_TIMEOUT: 
            UART_PutString("Timeout\n");
        break;
        /* This event indicates that some internal HW error has occurred. */
        case CYBLE_EVT_HARDWARE_ERROR:
            UART_PutString("CYBLE_EVT_HARDWARE_ERROR \r\n");
        break;
            
        /* This event will be triggered by host stack if BLE stack is busy or not busy.
         *  Parameter corresponding to this event will be the state of BLE stack.
         *  BLE stack busy = CYBLE_STACK_STATE_BUSY,
         *  BLE stack not busy = CYBLE_STACK_STATE_FREE 
         */
        case CYBLE_EVT_STACK_BUSY_STATUS:
            sprintf(str,"EVT_STACK_BUSY_STATUS: %x\r\n", *(uint8 *)eventParam);
            UART_PutString(str);
        case CYBLE_EVT_HCI_STATUS:
            sprintf(str,"EVT_HCI_STATUS: %x \r\n", *(uint8 *)eventParam);
            UART_PutString(str);
        break;
            
            
        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        case CYBLE_EVT_GAP_AUTH_REQ:
            sprintf(str, "EVT_AUTH_REQ: security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).security, 
                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).bonding, 
                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).ekeySize, 
                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).authErr);
            UART_PutString(str);
            break;
        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
            sprintf(str, "EVT_PASSKEY_ENTRY_REQUEST press 'p' to enter passkey \r\n");
            UART_PutString(str);
            break;
        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
            sprintf(str, "EVT_PASSKEY_DISPLAY_REQUEST %6.6ld \r\n", *(uint32 *)eventParam);
            UART_PutString(str);
            break;
        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
            UART_PutString("EVT_GAP_KEYINFO_EXCHNGE_CMPLT \r\n");
            break;
        case CYBLE_EVT_GAP_AUTH_COMPLETE:
            #if (DEBUG_UART_ENABLED == YES)
            authInfo = (CYBLE_GAP_AUTH_INFO_T *)eventParam;
            sprintf(str, "AUTH_COMPLETE: security:%x, bonding:%x, ekeySize:%x, authErr %x \r\n", 
                                    authInfo->security, authInfo->bonding, authInfo->ekeySize, authInfo->authErr);
            UART_PutString(str);
            #endif /* (DEBUG_UART_ENABLED == YES) */
            break;
        case CYBLE_EVT_GAP_AUTH_FAILED:
            sprintf(str, "EVT_AUTH_FAILED: %x \r\n", *(uint8 *)eventParam);
            UART_PutString(str);
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            sprintf(str, "EVT_ADVERTISING, state: %x \r\n", CyBle_GetState());
            UART_PutString(str);
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
            {   
                /* Fast and slow advertising period complete, go to low power  
                 * mode (Hibernate mode) and wait for an external
                 * user event to wake up the device again */
                UART_PutString("Hibernate \r\n");
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            UART_PutString("EVT_GAP_DEVICE_CONNECTED \r\n");
            CyBle_GapFixAuthPassKey (1, 123456);
            break;

        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
            { 
                uint16 mtu;
                CyBle_GattGetMtuSize(&mtu);
                sprintf(str, "CYBLE_EVT_GATTS_XCNHG_MTU_REQ, final mtu= %d \r\n", mtu);
                UART_PutString(str);
            }
            break;
        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
            sprintf(str, "EVT_GAP_ENCRYPT_CHANGE: %x \r\n", *(uint8 *)eventParam);
            UART_PutString(str);
            break;
        case CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE:
            sprintf(str, "EVT_CONNECTION_UPDATE_COMPLETE: %x \r\n", *(uint8 *)eventParam);
            UART_PutString(str);
            break;
            
            
        /***********************************************************/
        
        /* when a connection is made, update the LED and Capsense states in the GATT database and stop blinking the LED */    
        case CYBLE_EVT_GATT_CONNECT_IND:
            UART_PutString("GATT_CONNECT_IND\n");  
            //blue_Write(1);
		break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            UART_PutString("GATT_DISCONNECT_IND\n");
        break;

        /* handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            
            char str[100];
            sprintf(str, "attrHandle = %d \n", (int)(wrReqParam->handleValPair.attrHandle));
            UART_PutString(str);
			      
            /* request write the LED value */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_LED_CHAR_HANDLE)
            {
                /* only update the value and write the response if the requested write is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                }
            }
            
            /* request to update the CapSense notification */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_CAPSENSE_CAPSENSECCCD_DESC_HANDLE) 
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }		

            /* Request to change the vibration intensity -> between mute, low, medium, and high */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_VIBINTENSITY_CHAR_HANDLE)
            {
                //setVibIntensity(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            /* request to update the alarm status notification enablement */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_HANDLE) 
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                // alarm_notify is always 1
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }	
            
            /* request to update the alarm status */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE)
            {
                fsm_set_alarm_state((alarm_state_e)(wrReqParam->handleValPair.value.val[0]));
                CyBle_GattsWriteRsp(cyBle_connHandle);                
            }
            
            /* Request to update the vibration duration */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_VIBDURATION_CHAR_HANDLE)
            {
                setVibDuration(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle); 
            }
            
            /* Request to update the ambulance's vibration type */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHAR_HANDLE)
            {
                setAmbulanceVibType(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle); 
            }
            
            /* Request to update the fire alarm's vibration type */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHAR_HANDLE)
            {
                setFireAlarmVibType(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle); 
            }
            
            /* Request to update whether to enable fire alarm detection */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_CHAR_HANDLE)
            {
                setAlarmDetectEnable(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle); 
            }
            
            /* Request to update whether to enable ambulance detection */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_CHAR_HANDLE)
            {
                setAmbulanceDetectEnable(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle); 
            }

            break;
        
        default:
            UART_PutString("Other events\n");
            break;
    }
}

/* [] END OF FILE */
