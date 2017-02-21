/*******************************************************************************
* File Name: motor.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "motor.h"

static motor_BACKUP_STRUCT  motor_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: motor_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet motor_SUT.c usage_motor_Sleep_Wakeup
*******************************************************************************/
void motor_Sleep(void)
{
    #if defined(motor__PC)
        motor_backup.pcState = motor_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            motor_backup.usbState = motor_CR1_REG;
            motor_USB_POWER_REG |= motor_USBIO_ENTER_SLEEP;
            motor_CR1_REG &= motor_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(motor__SIO)
        motor_backup.sioState = motor_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        motor_SIO_REG &= (uint32)(~motor_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: motor_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to motor_Sleep() for an example usage.
*******************************************************************************/
void motor_Wakeup(void)
{
    #if defined(motor__PC)
        motor_PC = motor_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            motor_USB_POWER_REG &= motor_USBIO_EXIT_SLEEP_PH1;
            motor_CR1_REG = motor_backup.usbState;
            motor_USB_POWER_REG &= motor_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(motor__SIO)
        motor_SIO_REG = motor_backup.sioState;
    #endif
}


/* [] END OF FILE */
