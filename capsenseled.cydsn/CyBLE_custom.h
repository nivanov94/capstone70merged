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
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHAR_INDEX   (0x00u) /* Index of capsense characteristic */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CAPSENSECCCD_DESC_INDEX   (0x00u) /* Index of capsensecccd descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHAR_INDEX   (0x01u) /* Index of vibIntensity characteristic */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_INDEX   (0x02u) /* Index of alarmStatus characteristic */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_INDEX   (0x01u) /* Index of alarmStatusCCCD descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBDURATION_CHAR_INDEX   (0x03u) /* Index of alarmVibDuration characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHAR_INDEX   (0x04u) /* Index of alarmVibType characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBDURATION_CHAR_INDEX   (0x05u) /* Index of ambulanceVibDuration characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHAR_INDEX   (0x06u) /* Index of ambulanceVibType characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_CHAR_INDEX   (0x07u) /* Index of alarmDetectEnabled characteristic */
#define CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_CHAR_INDEX   (0x08u) /* Index of ambulanceDetectEnabled characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_BLACTIVATE_CHAR_INDEX   (0x09u) /* Index of BLActivate characteristic */
#define CYBLE_LEDCAPSENSE_BLACTIVATE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */


#define CYBLE_LEDCAPSENSE_SERVICE_HANDLE   (0x000Cu) /* Handle of ledcapsense service */
#define CYBLE_LEDCAPSENSE_CAPSENSE_DECL_HANDLE   (0x000Du) /* Handle of capsense characteristic declaration */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHAR_HANDLE   (0x000Eu) /* Handle of capsense characteristic */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CAPSENSECCCD_DESC_HANDLE   (0x000Fu) /* Handle of capsensecccd descriptor */
#define CYBLE_LEDCAPSENSE_CAPSENSE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0010u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_DECL_HANDLE   (0x0011u) /* Handle of vibIntensity characteristic declaration */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHAR_HANDLE   (0x0012u) /* Handle of vibIntensity characteristic */
#define CYBLE_LEDCAPSENSE_VIBINTENSITY_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0013u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_DECL_HANDLE   (0x0014u) /* Handle of alarmStatus characteristic declaration */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHAR_HANDLE   (0x0015u) /* Handle of alarmStatus characteristic */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0016u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMSTATUS_ALARMSTATUSCCCD_DESC_HANDLE   (0x0017u) /* Handle of alarmStatusCCCD descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBDURATION_DECL_HANDLE   (0x0018u) /* Handle of alarmVibDuration characteristic declaration */
#define CYBLE_LEDCAPSENSE_ALARMVIBDURATION_CHAR_HANDLE   (0x0019u) /* Handle of alarmVibDuration characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Au) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_DECL_HANDLE   (0x001Bu) /* Handle of alarmVibType characteristic declaration */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHAR_HANDLE   (0x001Cu) /* Handle of alarmVibType characteristic */
#define CYBLE_LEDCAPSENSE_ALARMVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBDURATION_DECL_HANDLE   (0x001Eu) /* Handle of ambulanceVibDuration characteristic declaration */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBDURATION_CHAR_HANDLE   (0x001Fu) /* Handle of ambulanceVibDuration characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBDURATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0020u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_DECL_HANDLE   (0x0021u) /* Handle of ambulanceVibType characteristic declaration */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHAR_HANDLE   (0x0022u) /* Handle of ambulanceVibType characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEVIBTYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0023u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_DECL_HANDLE   (0x0024u) /* Handle of alarmDetectEnabled characteristic declaration */
#define CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_CHAR_HANDLE   (0x0025u) /* Handle of alarmDetectEnabled characteristic */
#define CYBLE_LEDCAPSENSE_ALARMDETECTENABLED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0026u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_DECL_HANDLE   (0x0027u) /* Handle of ambulanceDetectEnabled characteristic declaration */
#define CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_CHAR_HANDLE   (0x0028u) /* Handle of ambulanceDetectEnabled characteristic */
#define CYBLE_LEDCAPSENSE_AMBULANCEDETECTENABLED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0029u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_LEDCAPSENSE_BLACTIVATE_DECL_HANDLE   (0x002Au) /* Handle of BLActivate characteristic declaration */
#define CYBLE_LEDCAPSENSE_BLACTIVATE_CHAR_HANDLE   (0x002Bu) /* Handle of BLActivate characteristic */
#define CYBLE_LEDCAPSENSE_BLACTIVATE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x002Cu) /* Handle of Characteristic User Description descriptor */


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
