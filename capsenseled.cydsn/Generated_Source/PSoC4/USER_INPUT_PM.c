/*******************************************************************************
* File Name: USER_INPUT.c  
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
#include "USER_INPUT.h"

static USER_INPUT_BACKUP_STRUCT  USER_INPUT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: USER_INPUT_Sleep
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
*  \snippet USER_INPUT_SUT.c usage_USER_INPUT_Sleep_Wakeup
*******************************************************************************/
void USER_INPUT_Sleep(void)
{
    #if defined(USER_INPUT__PC)
        USER_INPUT_backup.pcState = USER_INPUT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            USER_INPUT_backup.usbState = USER_INPUT_CR1_REG;
            USER_INPUT_USB_POWER_REG |= USER_INPUT_USBIO_ENTER_SLEEP;
            USER_INPUT_CR1_REG &= USER_INPUT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(USER_INPUT__SIO)
        USER_INPUT_backup.sioState = USER_INPUT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        USER_INPUT_SIO_REG &= (uint32)(~USER_INPUT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: USER_INPUT_Wakeup
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
*  Refer to USER_INPUT_Sleep() for an example usage.
*******************************************************************************/
void USER_INPUT_Wakeup(void)
{
    #if defined(USER_INPUT__PC)
        USER_INPUT_PC = USER_INPUT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            USER_INPUT_USB_POWER_REG &= USER_INPUT_USBIO_EXIT_SLEEP_PH1;
            USER_INPUT_CR1_REG = USER_INPUT_backup.usbState;
            USER_INPUT_USB_POWER_REG &= USER_INPUT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(USER_INPUT__SIO)
        USER_INPUT_SIO_REG = USER_INPUT_backup.sioState;
    #endif
}


/* [] END OF FILE */
