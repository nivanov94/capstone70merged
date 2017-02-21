#include <project.h>
#include "OTAOptional.h"
#include "common.h"
#include "stdio.h"
#include "CyBLE_custom.h"
#include "main.h"


#include "filter.h"
#include "queue.h"
#include "PWM.h"
#include "IDAC.h"
#include "adc.h"
#include "PGA.h"

#include "user_cfg_def.h"



alarm_state_e alarmStateOld = TYPE_NO_ALARM;
uint8 alarmNotify   = 1; // Always notify

// Device modifies this 
alarm_state_e alarm_state    = TYPE_NO_ALARM;

// Configuration updated by the app
vib_type_e      curFireAlarmVibType = VIBTYPE_CONTINUOUS;
vib_type_e      curAmbulanceVibType = VIBTYPE_CONTINUOUS;
vib_duration_e  curVibDuration      = DURATION_5S;
vib_intensity_e curVibIntensity     = INTENSITY_LOW;


/* LED control defines (active low)*/
#define LIGHT_OFF                       (1u)
#define LIGHT_ON                        (0u)
#define SIZE 2000U

#define LOW_FILT  0
#define MID_FILT  1
#define HIGH_FILT 2

#define MIC_GAIN 68/2.2

#define MOTOR_ON  1
#define MOTOR_OFF 0

/* Selects the active blinking LED */
uint8 activeLed;
// Flag to indicate when to sample digital lines.
uint8 sample_lines;


/*******************************************************************************
* Defines the interrupt service routine and allocates a vector to the interrupt.
* We use one handler for both the Capture and Terminal Count interrupts
* We toggle the active LED upon each Terminal Count interrupt
* We toggle the color (active LED) between blue and green upon each Capture 
* interrupt
********************************************************************************/

CY_ISR(InterruptHandler)
{    
    if (Timer_INTR_MASK_TC == Timer_GetInterruptSource()) {
        // Timer has overflowed, 1ms has elapsed.
        // Clear interrupt, then set flag to execute finite state control loop.
        Timer_ClearInterrupt(Timer_INTR_MASK_TC);
        sample_lines = 1;        
    }
}

void notifyFireAlarm() {
    alarm_state = TYPE_FIRE_ALARM;
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;

	CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;

    tempHandle.attrHandle = CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *)&alarm_state;
    tempHandle.value.len = 2; 
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    
    /* send notification to client*/
    if (alarmNotify) {
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    }
}

void notifyAmbulance(){
    alarm_state = TYPE_AMBULANCE;
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;

	CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;

    tempHandle.attrHandle = CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *)&alarm_state;
    tempHandle.value.len = 2; 
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    
    /* send notification to client*/
    if (alarmNotify) {
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    }
}

void setVibIntensity(int intensity){
    curVibIntensity = intensity;
}

void setFireAlarmVibType(int vibType){
    curFireAlarmVibType = vibType;
}

void setAmbulanceVibType(int vibType){
    curAmbulanceVibType = vibType;
}

void setVibDuration(int vibDuration){
    curVibDuration = vibDuration;
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
                setVibIntensity(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            /* request to update the alarm status notification enablement */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_HANDLE) 
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                alarmNotify = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }	
            
            /* request to update the alarm status */
            if (wrReqParam->handleValPair.attrHandle == CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE)
            {
                if (CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    alarm_state = wrReqParam->handleValPair.value.val[0];
                }
                
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

            break;
        
        default:
            UART_PutString("Other events\n");
            break;
    }
}


/***************************************************************
 * Main
 **************************************************************/
int main()
{
#if !defined(__ARMCC_VERSION)
    InitializeBootloaderSRAM();
#endif

    motor_Write(0);
    
    CyGlobalIntEnable;
    
    UART_Start();
    
    /* Start BLE stack and register the callback function */
    CyBle_Start(AppCallBack);
    
    CyDelay(100u);

    char str[100];
    sprintf(str, "Application entered \n");
    UART_PutString(str);
    
    ConfigureSharedPins();
    
    //LED_RED_Write(0);
        
    //PGA_set_gain(MIC_GAIN);
    
    /*enable ADC, PWM, and IDAC for threshold initialization */
    init_PWM();
    init_IDAC();
    ADC_init();
    
    /*set comparator thresholds*/
    CyDelay(5);
    set_PWM_threshold(LOW_FILT);
    set_PWM_threshold(MID_FILT);
    set_PWM_threshold(HIGH_FILT);
    set_IDAC_threshold();
    
    /*put ADC to sleep*/
    ADC_sleep();
    
    
    /* Enable interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);

    /* Start sampling timer */
    Timer_Start();
    
    
    // The state of the FSM.
    uint8 state = 0;
    
    queue_t low_prev;
    queue_t med_prev;
    queue_t high_prev;
    queue_t fire_prev;
    queue_t slope_detect;
    queue_t med_deriv;
    queue_t high_deriv;
    
    int low_count = 0;
    int med_count = 0;
    int high_count = 0;
    int fire_count = 0;
    int liveness_count = 0;
    int prev_low_count;
    int prev_med_count;
    int prev_high_count;
    
    init_queue(&low_prev);
    init_queue(&med_prev);
    init_queue(&high_prev);
    init_queue(&fire_prev);
    init_queue(&slope_detect);
    init_queue(&med_deriv);
    init_queue(&high_deriv);

    for(;;)
    {        
        if (sample_lines) {
            sample_lines = 0;
            
            switch(state) {
                
                /* This is the state that is entered upon reset.
                 * In the future, this state should be returned to upon 
                 * event detection if the user applies an input (possibly a
                 * pushbutton to start with, and a BLE signal in the future).
                 */
                case 0:
                    low_count = 0;
                    med_count = 0;
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
                // TODO break up count into helper functions, make new header file.
                case 1:
                    prev_low_count = low_count;
                    prev_med_count = med_count;
                    prev_high_count = high_count;
                    low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);
                    fire_count = filter_count(FIRE_FILTER_INPUT_Read(), &fire_prev, fire_count);
                    push(&slope_detect, low_count - prev_low_count);
                    push(&med_deriv, med_count - prev_med_count);
                    push(&high_deriv, high_count - prev_high_count);
                    
                    // second derivative concavity test
                    if ((sum(&slope_detect) == 0) && (peek(&slope_detect) == 1)) {
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                    }
                    
                    // all filter negative first derivative test
                    if ((sum(&slope_detect) == -6) && (sum(&med_deriv) == -6) && (sum(&high_deriv) == -6)) {
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                    }
                                  
                    
                    /* Check for fire alarm threshold. */
                    if (fire_count > 800) {
                        state = 5;
                        liveness_count = 0;
                        init_queue(&slope_detect);
                        LED_RED_Write(LIGHT_ON);
                    }
                    
                    /* Check for siren threshold. */
                    else if ((low_count > 25) && (med_count > 5) && (high_count < 5) && (low_count >= med_count)) {
                        state = 2;
                        low_count = 0;
                        med_count = 0;
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
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count); 

                    if (liveness_count > 100) {
                        state = 0;                    
                        LED_BLUE_Write(LIGHT_OFF);
                    }
                    else if ((low_count <= med_count) && (med_count > 20) && (med_count > high_count) && (high_count > 12)) {
                        state = 3;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                    }                                            
                    break;
                    
                case 3:
                    liveness_count++;
                    low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);                    
                    
                    if (liveness_count > 100) {
                        state = 0;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                        LED_BLUE_Write(LIGHT_OFF);
                    }
                    else if ((low_count < 20) && (med_count < 30) && (high_count > 95)) {
                        state = 4;
                        low_count = 0;
                        med_count = 0;
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
                    
                /* In this state, indicate detection of the fire alarm.
                 */
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
   
        CyBle_ProcessEvents();
        BootloaderSwitch();
           
    }
}
