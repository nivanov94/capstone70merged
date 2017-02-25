/*******************************************************************************
* File Name: Low_Peak.h  
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

#if !defined(CY_PINS_Low_Peak_H) /* Pins Low_Peak_H */
#define CY_PINS_Low_Peak_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Low_Peak_aliases.h"


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
} Low_Peak_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Low_Peak_Read(void);
void    Low_Peak_Write(uint8 value);
uint8   Low_Peak_ReadDataReg(void);
#if defined(Low_Peak__PC) || (CY_PSOC4_4200L) 
    void    Low_Peak_SetDriveMode(uint8 mode);
#endif
void    Low_Peak_SetInterruptMode(uint16 position, uint16 mode);
uint8   Low_Peak_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Low_Peak_Sleep(void); 
void Low_Peak_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Low_Peak__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Low_Peak_DRIVE_MODE_BITS        (3)
    #define Low_Peak_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Low_Peak_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Low_Peak_SetDriveMode() function.
         *  @{
         */
        #define Low_Peak_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Low_Peak_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Low_Peak_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Low_Peak_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Low_Peak_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Low_Peak_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Low_Peak_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Low_Peak_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Low_Peak_MASK               Low_Peak__MASK
#define Low_Peak_SHIFT              Low_Peak__SHIFT
#define Low_Peak_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Low_Peak_SetInterruptMode() function.
     *  @{
     */
        #define Low_Peak_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Low_Peak_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Low_Peak_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Low_Peak_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Low_Peak__SIO)
    #define Low_Peak_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Low_Peak__PC) && (CY_PSOC4_4200L)
    #define Low_Peak_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Low_Peak_USBIO_DISABLE              ((uint32)(~Low_Peak_USBIO_ENABLE))
    #define Low_Peak_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Low_Peak_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Low_Peak_USBIO_ENTER_SLEEP          ((uint32)((1u << Low_Peak_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Low_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Low_Peak_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Low_Peak_USBIO_SUSPEND_SHIFT)))
    #define Low_Peak_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Low_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Low_Peak_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Low_Peak__PC)
    /* Port Configuration */
    #define Low_Peak_PC                 (* (reg32 *) Low_Peak__PC)
#endif
/* Pin State */
#define Low_Peak_PS                     (* (reg32 *) Low_Peak__PS)
/* Data Register */
#define Low_Peak_DR                     (* (reg32 *) Low_Peak__DR)
/* Input Buffer Disable Override */
#define Low_Peak_INP_DIS                (* (reg32 *) Low_Peak__PC2)

/* Interrupt configuration Registers */
#define Low_Peak_INTCFG                 (* (reg32 *) Low_Peak__INTCFG)
#define Low_Peak_INTSTAT                (* (reg32 *) Low_Peak__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Low_Peak_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Low_Peak__SIO)
    #define Low_Peak_SIO_REG            (* (reg32 *) Low_Peak__SIO)
#endif /* (Low_Peak__SIO_CFG) */

/* USBIO registers */
#if !defined(Low_Peak__PC) && (CY_PSOC4_4200L)
    #define Low_Peak_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Low_Peak_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Low_Peak_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Low_Peak_DRIVE_MODE_SHIFT       (0x00u)
#define Low_Peak_DRIVE_MODE_MASK        (0x07u << Low_Peak_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Low_Peak_H */


/* [] END OF FILE */
