/*******************************************************************************
* File Name: motor.h  
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

#if !defined(CY_PINS_motor_H) /* Pins motor_H */
#define CY_PINS_motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motor_aliases.h"


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
} motor_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   motor_Read(void);
void    motor_Write(uint8 value);
uint8   motor_ReadDataReg(void);
#if defined(motor__PC) || (CY_PSOC4_4200L) 
    void    motor_SetDriveMode(uint8 mode);
#endif
void    motor_SetInterruptMode(uint16 position, uint16 mode);
uint8   motor_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void motor_Sleep(void); 
void motor_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(motor__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define motor_DRIVE_MODE_BITS        (3)
    #define motor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motor_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the motor_SetDriveMode() function.
         *  @{
         */
        #define motor_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define motor_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define motor_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define motor_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define motor_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define motor_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define motor_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define motor_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define motor_MASK               motor__MASK
#define motor_SHIFT              motor__SHIFT
#define motor_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in motor_SetInterruptMode() function.
     *  @{
     */
        #define motor_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define motor_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define motor_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define motor_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(motor__SIO)
    #define motor_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(motor__PC) && (CY_PSOC4_4200L)
    #define motor_USBIO_ENABLE               ((uint32)0x80000000u)
    #define motor_USBIO_DISABLE              ((uint32)(~motor_USBIO_ENABLE))
    #define motor_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define motor_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define motor_USBIO_ENTER_SLEEP          ((uint32)((1u << motor_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << motor_USBIO_SUSPEND_DEL_SHIFT)))
    #define motor_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << motor_USBIO_SUSPEND_SHIFT)))
    #define motor_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << motor_USBIO_SUSPEND_DEL_SHIFT)))
    #define motor_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(motor__PC)
    /* Port Configuration */
    #define motor_PC                 (* (reg32 *) motor__PC)
#endif
/* Pin State */
#define motor_PS                     (* (reg32 *) motor__PS)
/* Data Register */
#define motor_DR                     (* (reg32 *) motor__DR)
/* Input Buffer Disable Override */
#define motor_INP_DIS                (* (reg32 *) motor__PC2)

/* Interrupt configuration Registers */
#define motor_INTCFG                 (* (reg32 *) motor__INTCFG)
#define motor_INTSTAT                (* (reg32 *) motor__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define motor_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(motor__SIO)
    #define motor_SIO_REG            (* (reg32 *) motor__SIO)
#endif /* (motor__SIO_CFG) */

/* USBIO registers */
#if !defined(motor__PC) && (CY_PSOC4_4200L)
    #define motor_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define motor_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define motor_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define motor_DRIVE_MODE_SHIFT       (0x00u)
#define motor_DRIVE_MODE_MASK        (0x07u << motor_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins motor_H */


/* [] END OF FILE */
