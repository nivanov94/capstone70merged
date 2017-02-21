/*******************************************************************************
* File Name: High_Thresh.h  
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

#if !defined(CY_PINS_High_Thresh_H) /* Pins High_Thresh_H */
#define CY_PINS_High_Thresh_H

#include "cytypes.h"
#include "cyfitter.h"
#include "High_Thresh_aliases.h"


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
} High_Thresh_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   High_Thresh_Read(void);
void    High_Thresh_Write(uint8 value);
uint8   High_Thresh_ReadDataReg(void);
#if defined(High_Thresh__PC) || (CY_PSOC4_4200L) 
    void    High_Thresh_SetDriveMode(uint8 mode);
#endif
void    High_Thresh_SetInterruptMode(uint16 position, uint16 mode);
uint8   High_Thresh_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void High_Thresh_Sleep(void); 
void High_Thresh_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(High_Thresh__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define High_Thresh_DRIVE_MODE_BITS        (3)
    #define High_Thresh_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - High_Thresh_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the High_Thresh_SetDriveMode() function.
         *  @{
         */
        #define High_Thresh_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define High_Thresh_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define High_Thresh_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define High_Thresh_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define High_Thresh_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define High_Thresh_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define High_Thresh_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define High_Thresh_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define High_Thresh_MASK               High_Thresh__MASK
#define High_Thresh_SHIFT              High_Thresh__SHIFT
#define High_Thresh_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in High_Thresh_SetInterruptMode() function.
     *  @{
     */
        #define High_Thresh_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define High_Thresh_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define High_Thresh_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define High_Thresh_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(High_Thresh__SIO)
    #define High_Thresh_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(High_Thresh__PC) && (CY_PSOC4_4200L)
    #define High_Thresh_USBIO_ENABLE               ((uint32)0x80000000u)
    #define High_Thresh_USBIO_DISABLE              ((uint32)(~High_Thresh_USBIO_ENABLE))
    #define High_Thresh_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define High_Thresh_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define High_Thresh_USBIO_ENTER_SLEEP          ((uint32)((1u << High_Thresh_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << High_Thresh_USBIO_SUSPEND_DEL_SHIFT)))
    #define High_Thresh_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << High_Thresh_USBIO_SUSPEND_SHIFT)))
    #define High_Thresh_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << High_Thresh_USBIO_SUSPEND_DEL_SHIFT)))
    #define High_Thresh_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(High_Thresh__PC)
    /* Port Configuration */
    #define High_Thresh_PC                 (* (reg32 *) High_Thresh__PC)
#endif
/* Pin State */
#define High_Thresh_PS                     (* (reg32 *) High_Thresh__PS)
/* Data Register */
#define High_Thresh_DR                     (* (reg32 *) High_Thresh__DR)
/* Input Buffer Disable Override */
#define High_Thresh_INP_DIS                (* (reg32 *) High_Thresh__PC2)

/* Interrupt configuration Registers */
#define High_Thresh_INTCFG                 (* (reg32 *) High_Thresh__INTCFG)
#define High_Thresh_INTSTAT                (* (reg32 *) High_Thresh__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define High_Thresh_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(High_Thresh__SIO)
    #define High_Thresh_SIO_REG            (* (reg32 *) High_Thresh__SIO)
#endif /* (High_Thresh__SIO_CFG) */

/* USBIO registers */
#if !defined(High_Thresh__PC) && (CY_PSOC4_4200L)
    #define High_Thresh_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define High_Thresh_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define High_Thresh_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define High_Thresh_DRIVE_MODE_SHIFT       (0x00u)
#define High_Thresh_DRIVE_MODE_MASK        (0x07u << High_Thresh_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins High_Thresh_H */


/* [] END OF FILE */
