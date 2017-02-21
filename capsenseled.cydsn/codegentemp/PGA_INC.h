/*******************************************************************************
* File Name: PGA_INC.h  
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

#if !defined(CY_PINS_PGA_INC_H) /* Pins PGA_INC_H */
#define CY_PINS_PGA_INC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PGA_INC_aliases.h"


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
} PGA_INC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PGA_INC_Read(void);
void    PGA_INC_Write(uint8 value);
uint8   PGA_INC_ReadDataReg(void);
#if defined(PGA_INC__PC) || (CY_PSOC4_4200L) 
    void    PGA_INC_SetDriveMode(uint8 mode);
#endif
void    PGA_INC_SetInterruptMode(uint16 position, uint16 mode);
uint8   PGA_INC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PGA_INC_Sleep(void); 
void PGA_INC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PGA_INC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PGA_INC_DRIVE_MODE_BITS        (3)
    #define PGA_INC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PGA_INC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PGA_INC_SetDriveMode() function.
         *  @{
         */
        #define PGA_INC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PGA_INC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PGA_INC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PGA_INC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PGA_INC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PGA_INC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PGA_INC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PGA_INC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PGA_INC_MASK               PGA_INC__MASK
#define PGA_INC_SHIFT              PGA_INC__SHIFT
#define PGA_INC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PGA_INC_SetInterruptMode() function.
     *  @{
     */
        #define PGA_INC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PGA_INC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PGA_INC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PGA_INC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PGA_INC__SIO)
    #define PGA_INC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PGA_INC__PC) && (CY_PSOC4_4200L)
    #define PGA_INC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PGA_INC_USBIO_DISABLE              ((uint32)(~PGA_INC_USBIO_ENABLE))
    #define PGA_INC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PGA_INC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PGA_INC_USBIO_ENTER_SLEEP          ((uint32)((1u << PGA_INC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PGA_INC_USBIO_SUSPEND_DEL_SHIFT)))
    #define PGA_INC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PGA_INC_USBIO_SUSPEND_SHIFT)))
    #define PGA_INC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PGA_INC_USBIO_SUSPEND_DEL_SHIFT)))
    #define PGA_INC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PGA_INC__PC)
    /* Port Configuration */
    #define PGA_INC_PC                 (* (reg32 *) PGA_INC__PC)
#endif
/* Pin State */
#define PGA_INC_PS                     (* (reg32 *) PGA_INC__PS)
/* Data Register */
#define PGA_INC_DR                     (* (reg32 *) PGA_INC__DR)
/* Input Buffer Disable Override */
#define PGA_INC_INP_DIS                (* (reg32 *) PGA_INC__PC2)

/* Interrupt configuration Registers */
#define PGA_INC_INTCFG                 (* (reg32 *) PGA_INC__INTCFG)
#define PGA_INC_INTSTAT                (* (reg32 *) PGA_INC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PGA_INC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PGA_INC__SIO)
    #define PGA_INC_SIO_REG            (* (reg32 *) PGA_INC__SIO)
#endif /* (PGA_INC__SIO_CFG) */

/* USBIO registers */
#if !defined(PGA_INC__PC) && (CY_PSOC4_4200L)
    #define PGA_INC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PGA_INC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PGA_INC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PGA_INC_DRIVE_MODE_SHIFT       (0x00u)
#define PGA_INC_DRIVE_MODE_MASK        (0x07u << PGA_INC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PGA_INC_H */


/* [] END OF FILE */
