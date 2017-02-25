/*******************************************************************************
* File Name: Fire_Peak.h  
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

#if !defined(CY_PINS_Fire_Peak_H) /* Pins Fire_Peak_H */
#define CY_PINS_Fire_Peak_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Fire_Peak_aliases.h"


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
} Fire_Peak_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Fire_Peak_Read(void);
void    Fire_Peak_Write(uint8 value);
uint8   Fire_Peak_ReadDataReg(void);
#if defined(Fire_Peak__PC) || (CY_PSOC4_4200L) 
    void    Fire_Peak_SetDriveMode(uint8 mode);
#endif
void    Fire_Peak_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fire_Peak_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Fire_Peak_Sleep(void); 
void Fire_Peak_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Fire_Peak__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Fire_Peak_DRIVE_MODE_BITS        (3)
    #define Fire_Peak_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Fire_Peak_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Fire_Peak_SetDriveMode() function.
         *  @{
         */
        #define Fire_Peak_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Fire_Peak_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Fire_Peak_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Fire_Peak_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Fire_Peak_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Fire_Peak_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Fire_Peak_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Fire_Peak_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Fire_Peak_MASK               Fire_Peak__MASK
#define Fire_Peak_SHIFT              Fire_Peak__SHIFT
#define Fire_Peak_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fire_Peak_SetInterruptMode() function.
     *  @{
     */
        #define Fire_Peak_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Fire_Peak_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Fire_Peak_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Fire_Peak_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Fire_Peak__SIO)
    #define Fire_Peak_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Fire_Peak__PC) && (CY_PSOC4_4200L)
    #define Fire_Peak_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Fire_Peak_USBIO_DISABLE              ((uint32)(~Fire_Peak_USBIO_ENABLE))
    #define Fire_Peak_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Fire_Peak_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Fire_Peak_USBIO_ENTER_SLEEP          ((uint32)((1u << Fire_Peak_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Fire_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fire_Peak_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Fire_Peak_USBIO_SUSPEND_SHIFT)))
    #define Fire_Peak_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Fire_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fire_Peak_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Fire_Peak__PC)
    /* Port Configuration */
    #define Fire_Peak_PC                 (* (reg32 *) Fire_Peak__PC)
#endif
/* Pin State */
#define Fire_Peak_PS                     (* (reg32 *) Fire_Peak__PS)
/* Data Register */
#define Fire_Peak_DR                     (* (reg32 *) Fire_Peak__DR)
/* Input Buffer Disable Override */
#define Fire_Peak_INP_DIS                (* (reg32 *) Fire_Peak__PC2)

/* Interrupt configuration Registers */
#define Fire_Peak_INTCFG                 (* (reg32 *) Fire_Peak__INTCFG)
#define Fire_Peak_INTSTAT                (* (reg32 *) Fire_Peak__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Fire_Peak_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Fire_Peak__SIO)
    #define Fire_Peak_SIO_REG            (* (reg32 *) Fire_Peak__SIO)
#endif /* (Fire_Peak__SIO_CFG) */

/* USBIO registers */
#if !defined(Fire_Peak__PC) && (CY_PSOC4_4200L)
    #define Fire_Peak_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Fire_Peak_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Fire_Peak_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Fire_Peak_DRIVE_MODE_SHIFT       (0x00u)
#define Fire_Peak_DRIVE_MODE_MASK        (0x07u << Fire_Peak_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Fire_Peak_H */


/* [] END OF FILE */
