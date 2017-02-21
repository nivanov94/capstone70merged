/*******************************************************************************
* File Name: PGA_U_Db.h  
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

#if !defined(CY_PINS_PGA_U_Db_H) /* Pins PGA_U_Db_H */
#define CY_PINS_PGA_U_Db_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PGA_U_Db_aliases.h"


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
} PGA_U_Db_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PGA_U_Db_Read(void);
void    PGA_U_Db_Write(uint8 value);
uint8   PGA_U_Db_ReadDataReg(void);
#if defined(PGA_U_Db__PC) || (CY_PSOC4_4200L) 
    void    PGA_U_Db_SetDriveMode(uint8 mode);
#endif
void    PGA_U_Db_SetInterruptMode(uint16 position, uint16 mode);
uint8   PGA_U_Db_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PGA_U_Db_Sleep(void); 
void PGA_U_Db_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PGA_U_Db__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PGA_U_Db_DRIVE_MODE_BITS        (3)
    #define PGA_U_Db_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PGA_U_Db_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PGA_U_Db_SetDriveMode() function.
         *  @{
         */
        #define PGA_U_Db_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PGA_U_Db_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PGA_U_Db_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PGA_U_Db_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PGA_U_Db_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PGA_U_Db_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PGA_U_Db_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PGA_U_Db_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PGA_U_Db_MASK               PGA_U_Db__MASK
#define PGA_U_Db_SHIFT              PGA_U_Db__SHIFT
#define PGA_U_Db_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PGA_U_Db_SetInterruptMode() function.
     *  @{
     */
        #define PGA_U_Db_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PGA_U_Db_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PGA_U_Db_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PGA_U_Db_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PGA_U_Db__SIO)
    #define PGA_U_Db_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PGA_U_Db__PC) && (CY_PSOC4_4200L)
    #define PGA_U_Db_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PGA_U_Db_USBIO_DISABLE              ((uint32)(~PGA_U_Db_USBIO_ENABLE))
    #define PGA_U_Db_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PGA_U_Db_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PGA_U_Db_USBIO_ENTER_SLEEP          ((uint32)((1u << PGA_U_Db_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PGA_U_Db_USBIO_SUSPEND_DEL_SHIFT)))
    #define PGA_U_Db_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PGA_U_Db_USBIO_SUSPEND_SHIFT)))
    #define PGA_U_Db_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PGA_U_Db_USBIO_SUSPEND_DEL_SHIFT)))
    #define PGA_U_Db_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PGA_U_Db__PC)
    /* Port Configuration */
    #define PGA_U_Db_PC                 (* (reg32 *) PGA_U_Db__PC)
#endif
/* Pin State */
#define PGA_U_Db_PS                     (* (reg32 *) PGA_U_Db__PS)
/* Data Register */
#define PGA_U_Db_DR                     (* (reg32 *) PGA_U_Db__DR)
/* Input Buffer Disable Override */
#define PGA_U_Db_INP_DIS                (* (reg32 *) PGA_U_Db__PC2)

/* Interrupt configuration Registers */
#define PGA_U_Db_INTCFG                 (* (reg32 *) PGA_U_Db__INTCFG)
#define PGA_U_Db_INTSTAT                (* (reg32 *) PGA_U_Db__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PGA_U_Db_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PGA_U_Db__SIO)
    #define PGA_U_Db_SIO_REG            (* (reg32 *) PGA_U_Db__SIO)
#endif /* (PGA_U_Db__SIO_CFG) */

/* USBIO registers */
#if !defined(PGA_U_Db__PC) && (CY_PSOC4_4200L)
    #define PGA_U_Db_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PGA_U_Db_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PGA_U_Db_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PGA_U_Db_DRIVE_MODE_SHIFT       (0x00u)
#define PGA_U_Db_DRIVE_MODE_MASK        (0x07u << PGA_U_Db_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PGA_U_Db_H */


/* [] END OF FILE */
