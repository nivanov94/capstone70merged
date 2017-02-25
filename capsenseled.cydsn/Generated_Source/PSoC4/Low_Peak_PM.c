/*******************************************************************************
* File Name: Low_Peak.c  
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
#include "Low_Peak.h"

static Low_Peak_BACKUP_STRUCT  Low_Peak_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Low_Peak_Sleep
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
*  \snippet Low_Peak_SUT.c usage_Low_Peak_Sleep_Wakeup
*******************************************************************************/
void Low_Peak_Sleep(void)
{
    #if defined(Low_Peak__PC)
        Low_Peak_backup.pcState = Low_Peak_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Low_Peak_backup.usbState = Low_Peak_CR1_REG;
            Low_Peak_USB_POWER_REG |= Low_Peak_USBIO_ENTER_SLEEP;
            Low_Peak_CR1_REG &= Low_Peak_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Low_Peak__SIO)
        Low_Peak_backup.sioState = Low_Peak_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Low_Peak_SIO_REG &= (uint32)(~Low_Peak_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Low_Peak_Wakeup
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
*  Refer to Low_Peak_Sleep() for an example usage.
*******************************************************************************/
void Low_Peak_Wakeup(void)
{
    #if defined(Low_Peak__PC)
        Low_Peak_PC = Low_Peak_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Low_Peak_USB_POWER_REG &= Low_Peak_USBIO_EXIT_SLEEP_PH1;
            Low_Peak_CR1_REG = Low_Peak_backup.usbState;
            Low_Peak_USB_POWER_REG &= Low_Peak_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Low_Peak__SIO)
        Low_Peak_SIO_REG = Low_Peak_backup.sioState;
    #endif
}


/* [] END OF FILE */
