/*******************************************************************************
* File Name: Mid_Peak.h  
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

#if !defined(CY_PINS_Mid_Peak_H) /* Pins Mid_Peak_H */
#define CY_PINS_Mid_Peak_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Mid_Peak_aliases.h"


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
} Mid_Peak_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Mid_Peak_Read(void);
void    Mid_Peak_Write(uint8 value);
uint8   Mid_Peak_ReadDataReg(void);
#if defined(Mid_Peak__PC) || (CY_PSOC4_4200L) 
    void    Mid_Peak_SetDriveMode(uint8 mode);
#endif
void    Mid_Peak_SetInterruptMode(uint16 position, uint16 mode);
uint8   Mid_Peak_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Mid_Peak_Sleep(void); 
void Mid_Peak_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Mid_Peak__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Mid_Peak_DRIVE_MODE_BITS        (3)
    #define Mid_Peak_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Mid_Peak_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Mid_Peak_SetDriveMode() function.
         *  @{
         */
        #define Mid_Peak_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Mid_Peak_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Mid_Peak_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Mid_Peak_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Mid_Peak_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Mid_Peak_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Mid_Peak_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Mid_Peak_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Mid_Peak_MASK               Mid_Peak__MASK
#define Mid_Peak_SHIFT              Mid_Peak__SHIFT
#define Mid_Peak_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Mid_Peak_SetInterruptMode() function.
     *  @{
     */
        #define Mid_Peak_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Mid_Peak_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Mid_Peak_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Mid_Peak_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Mid_Peak__SIO)
    #define Mid_Peak_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Mid_Peak__PC) && (CY_PSOC4_4200L)
    #define Mid_Peak_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Mid_Peak_USBIO_DISABLE              ((uint32)(~Mid_Peak_USBIO_ENABLE))
    #define Mid_Peak_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Mid_Peak_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Mid_Peak_USBIO_ENTER_SLEEP          ((uint32)((1u << Mid_Peak_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Mid_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Mid_Peak_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Mid_Peak_USBIO_SUSPEND_SHIFT)))
    #define Mid_Peak_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Mid_Peak_USBIO_SUSPEND_DEL_SHIFT)))
    #define Mid_Peak_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Mid_Peak__PC)
    /* Port Configuration */
    #define Mid_Peak_PC                 (* (reg32 *) Mid_Peak__PC)
#endif
/* Pin State */
#define Mid_Peak_PS                     (* (reg32 *) Mid_Peak__PS)
/* Data Register */
#define Mid_Peak_DR                     (* (reg32 *) Mid_Peak__DR)
/* Input Buffer Disable Override */
#define Mid_Peak_INP_DIS                (* (reg32 *) Mid_Peak__PC2)

/* Interrupt configuration Registers */
#define Mid_Peak_INTCFG                 (* (reg32 *) Mid_Peak__INTCFG)
#define Mid_Peak_INTSTAT                (* (reg32 *) Mid_Peak__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Mid_Peak_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Mid_Peak__SIO)
    #define Mid_Peak_SIO_REG            (* (reg32 *) Mid_Peak__SIO)
#endif /* (Mid_Peak__SIO_CFG) */

/* USBIO registers */
#if !defined(Mid_Peak__PC) && (CY_PSOC4_4200L)
    #define Mid_Peak_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Mid_Peak_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Mid_Peak_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Mid_Peak_DRIVE_MODE_SHIFT       (0x00u)
#define Mid_Peak_DRIVE_MODE_MASK        (0x07u << Mid_Peak_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Mid_Peak_H */


/* [] END OF FILE */
