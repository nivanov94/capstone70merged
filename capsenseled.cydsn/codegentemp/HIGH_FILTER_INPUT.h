/*******************************************************************************
* File Name: HIGH_FILTER_INPUT.h  
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

#if !defined(CY_PINS_HIGH_FILTER_INPUT_H) /* Pins HIGH_FILTER_INPUT_H */
#define CY_PINS_HIGH_FILTER_INPUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HIGH_FILTER_INPUT_aliases.h"


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
} HIGH_FILTER_INPUT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HIGH_FILTER_INPUT_Read(void);
void    HIGH_FILTER_INPUT_Write(uint8 value);
uint8   HIGH_FILTER_INPUT_ReadDataReg(void);
#if defined(HIGH_FILTER_INPUT__PC) || (CY_PSOC4_4200L) 
    void    HIGH_FILTER_INPUT_SetDriveMode(uint8 mode);
#endif
void    HIGH_FILTER_INPUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   HIGH_FILTER_INPUT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HIGH_FILTER_INPUT_Sleep(void); 
void HIGH_FILTER_INPUT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HIGH_FILTER_INPUT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HIGH_FILTER_INPUT_DRIVE_MODE_BITS        (3)
    #define HIGH_FILTER_INPUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HIGH_FILTER_INPUT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HIGH_FILTER_INPUT_SetDriveMode() function.
         *  @{
         */
        #define HIGH_FILTER_INPUT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HIGH_FILTER_INPUT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HIGH_FILTER_INPUT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HIGH_FILTER_INPUT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HIGH_FILTER_INPUT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HIGH_FILTER_INPUT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HIGH_FILTER_INPUT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HIGH_FILTER_INPUT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HIGH_FILTER_INPUT_MASK               HIGH_FILTER_INPUT__MASK
#define HIGH_FILTER_INPUT_SHIFT              HIGH_FILTER_INPUT__SHIFT
#define HIGH_FILTER_INPUT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HIGH_FILTER_INPUT_SetInterruptMode() function.
     *  @{
     */
        #define HIGH_FILTER_INPUT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HIGH_FILTER_INPUT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HIGH_FILTER_INPUT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HIGH_FILTER_INPUT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HIGH_FILTER_INPUT__SIO)
    #define HIGH_FILTER_INPUT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HIGH_FILTER_INPUT__PC) && (CY_PSOC4_4200L)
    #define HIGH_FILTER_INPUT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HIGH_FILTER_INPUT_USBIO_DISABLE              ((uint32)(~HIGH_FILTER_INPUT_USBIO_ENABLE))
    #define HIGH_FILTER_INPUT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HIGH_FILTER_INPUT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HIGH_FILTER_INPUT_USBIO_ENTER_SLEEP          ((uint32)((1u << HIGH_FILTER_INPUT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HIGH_FILTER_INPUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define HIGH_FILTER_INPUT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HIGH_FILTER_INPUT_USBIO_SUSPEND_SHIFT)))
    #define HIGH_FILTER_INPUT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HIGH_FILTER_INPUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define HIGH_FILTER_INPUT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HIGH_FILTER_INPUT__PC)
    /* Port Configuration */
    #define HIGH_FILTER_INPUT_PC                 (* (reg32 *) HIGH_FILTER_INPUT__PC)
#endif
/* Pin State */
#define HIGH_FILTER_INPUT_PS                     (* (reg32 *) HIGH_FILTER_INPUT__PS)
/* Data Register */
#define HIGH_FILTER_INPUT_DR                     (* (reg32 *) HIGH_FILTER_INPUT__DR)
/* Input Buffer Disable Override */
#define HIGH_FILTER_INPUT_INP_DIS                (* (reg32 *) HIGH_FILTER_INPUT__PC2)

/* Interrupt configuration Registers */
#define HIGH_FILTER_INPUT_INTCFG                 (* (reg32 *) HIGH_FILTER_INPUT__INTCFG)
#define HIGH_FILTER_INPUT_INTSTAT                (* (reg32 *) HIGH_FILTER_INPUT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HIGH_FILTER_INPUT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HIGH_FILTER_INPUT__SIO)
    #define HIGH_FILTER_INPUT_SIO_REG            (* (reg32 *) HIGH_FILTER_INPUT__SIO)
#endif /* (HIGH_FILTER_INPUT__SIO_CFG) */

/* USBIO registers */
#if !defined(HIGH_FILTER_INPUT__PC) && (CY_PSOC4_4200L)
    #define HIGH_FILTER_INPUT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HIGH_FILTER_INPUT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HIGH_FILTER_INPUT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HIGH_FILTER_INPUT_DRIVE_MODE_SHIFT       (0x00u)
#define HIGH_FILTER_INPUT_DRIVE_MODE_MASK        (0x07u << HIGH_FILTER_INPUT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HIGH_FILTER_INPUT_H */


/* [] END OF FILE */
