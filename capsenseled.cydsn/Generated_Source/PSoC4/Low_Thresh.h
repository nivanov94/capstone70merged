/*******************************************************************************
* File Name: Low_Thresh.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Low_Thresh_H) /* Pins Low_Thresh_H */
#define CY_PINS_Low_Thresh_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Low_Thresh_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Low_Thresh_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Low_Thresh_Read(void);
void    Low_Thresh_Write(uint8 value);
uint8   Low_Thresh_ReadDataReg(void);
#if defined(Low_Thresh__PC) || (CY_PSOC4_4200L) 
    void    Low_Thresh_SetDriveMode(uint8 mode);
#endif
void    Low_Thresh_SetInterruptMode(uint16 position, uint16 mode);
uint8   Low_Thresh_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Low_Thresh_Sleep(void); 
void Low_Thresh_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Low_Thresh__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Low_Thresh_DRIVE_MODE_BITS        (3)
    #define Low_Thresh_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Low_Thresh_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Low_Thresh_SetDriveMode() function.
         *  @{
         */
        #define Low_Thresh_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Low_Thresh_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Low_Thresh_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Low_Thresh_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Low_Thresh_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Low_Thresh_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Low_Thresh_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Low_Thresh_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Low_Thresh_MASK               Low_Thresh__MASK
#define Low_Thresh_SHIFT              Low_Thresh__SHIFT
#define Low_Thresh_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Low_Thresh_SetInterruptMode() function.
     *  @{
     */
        #define Low_Thresh_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Low_Thresh_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Low_Thresh_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Low_Thresh_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Low_Thresh__SIO)
    #define Low_Thresh_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Low_Thresh__PC) && (CY_PSOC4_4200L)
    #define Low_Thresh_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Low_Thresh_USBIO_DISABLE              ((uint32)(~Low_Thresh_USBIO_ENABLE))
    #define Low_Thresh_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Low_Thresh_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Low_Thresh_USBIO_ENTER_SLEEP          ((uint32)((1u << Low_Thresh_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Low_Thresh_USBIO_SUSPEND_DEL_SHIFT)))
    #define Low_Thresh_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Low_Thresh_USBIO_SUSPEND_SHIFT)))
    #define Low_Thresh_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Low_Thresh_USBIO_SUSPEND_DEL_SHIFT)))
    #define Low_Thresh_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Low_Thresh__PC)
    /* Port Configuration */
    #define Low_Thresh_PC                 (* (reg32 *) Low_Thresh__PC)
#endif
/* Pin State */
#define Low_Thresh_PS                     (* (reg32 *) Low_Thresh__PS)
/* Data Register */
#define Low_Thresh_DR                     (* (reg32 *) Low_Thresh__DR)
/* Input Buffer Disable Override */
#define Low_Thresh_INP_DIS                (* (reg32 *) Low_Thresh__PC2)

/* Interrupt configuration Registers */
#define Low_Thresh_INTCFG                 (* (reg32 *) Low_Thresh__INTCFG)
#define Low_Thresh_INTSTAT                (* (reg32 *) Low_Thresh__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Low_Thresh_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Low_Thresh__SIO)
    #define Low_Thresh_SIO_REG            (* (reg32 *) Low_Thresh__SIO)
#endif /* (Low_Thresh__SIO_CFG) */

/* USBIO registers */
#if !defined(Low_Thresh__PC) && (CY_PSOC4_4200L)
    #define Low_Thresh_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Low_Thresh_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Low_Thresh_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Low_Thresh_DRIVE_MODE_SHIFT       (0x00u)
#define Low_Thresh_DRIVE_MODE_MASK        (0x07u << Low_Thresh_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Low_Thresh_H */


/* [] END OF FILE */
