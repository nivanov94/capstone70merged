/***************************************************************************//**
* \file CYBLE_custom.h
* \version 2.30
* 
* \brief
*  Contains the function prototypes and constants for the Custom Service.
* 
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BLE_CYBLE_CUSTOM_H)
#define CY_BLE_CYBLE_CUSTOM_H
    
#define CYBLE_GATT_DB_LOCALLY_INITIATED (0x00u)
#define CYBLE_GATT_DB_PEER_INITIATED    (0x40u)


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Maximum supported Custom Services */
#define CYBLE_CUSTOMS_SERVICE_COUNT                  (0x01u)
#define CYBLE_CUSTOMC_SERVICE_COUNT                  (0x00u)
#define CYBLE_CUSTOM_SERVICE_CHAR_COUNT              (0x07u)
#define CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT  (0x02u)

/* Below are the indexes and handles of the defined Custom Services and their characteristics */
#define CYBLE_LEDCAPSENSE_SERVICE_INDEX   (0x00u) /* Index of ledcapsense service in the cyBle_customs array */
#define CYBLE_LEDCAPSENSE_LED_CHAR_INDEX   (0x00u) /* Index of led characteristic */
#define CYBLE_LEDCAPSENSE_LED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHAR_INDEX   (0x01u) /* Index of capsense characteristic */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CAPSENSECCCD_DESC_INDEX   (0x00u) /* Index of capsensecccd descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHAR_INDEX   (0x02u) /* Index of vibIntensity characteristic */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_INDEX   (0x03u) /* Index of alarmStatus characteristic */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_INDEX   (0x01u) /* Index of alarmStatusCCCD descriptor */
#define CYBLE_LEDCAPSENSE_VIBDURATION_CHAR_INDEX   (0x04u) /* Index of vibDuration characteristic */
#define CYBLE_LEDCAPSENSE_VIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHAR_INDEX   (0x05u) /* Index of alarmVibType characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHAR_INDEX   (0x06u) /* Index of ambulanceVibType characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */


#define CYBLE_LEDCAPSENSE_SERVICE_HANDLE   (0x000Cu) /* Handle of ledcapsense service */
#define CYBLE_LEDCAPSENSE_LED_CHAR_HANDLE   (0x000Eu) /* Handle of led characteristic */
#define CYBLE_LEDCAPSENSE_LED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x000Fu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHAR_HANDLE   (0x0011u) /* Handle of capsense characteristic */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CAPSENSECCCD_DESC_HANDLE   (0x0012u) /* Handle of capsensecccd descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0013u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHAR_HANDLE   (0x0015u) /* Handle of vibIntensity characteristic */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0016u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE   (0x0018u) /* Handle of alarmStatus characteristic */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0019u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_HANDLE   (0x001Au) /* Handle of alarmStatusCCCD descriptor */
#define CYBLE_LEDCAPSENSE_VIBDURATION_CHAR_HANDLE   (0x001Cu) /* Handle of vibDuration characteristic */
#define CYBLE_LEDCAPSENSE_VIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHAR_HANDLE   (0x001Fu) /* Handle of alarmVibType characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0020u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHAR_HANDLE   (0x0022u) /* Handle of ambulanceVibType characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0023u) /* Handle of Characteristic User Description descriptor */



/** \cond IGNORE */
/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define customServiceCharHandle         customServCharHandle
#define customServiceCharDescriptors    customServCharDesc
#define customServiceHandle             customServHandle
#define customServiceInfo               customServInfo
/** \endcond */


#endif /* CY_BLE_CYBLE_CUSTOM_H  */

/* [] END OF FILE */
