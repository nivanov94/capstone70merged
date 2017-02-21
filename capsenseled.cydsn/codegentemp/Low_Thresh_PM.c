/*******************************************************************************
* File Name: Low_Thresh.c  
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
#include "Low_Thresh.h"

static Low_Thresh_BACKUP_STRUCT  Low_Thresh_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Low_Thresh_Sleep
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
*  \snippet Low_Thresh_SUT.c usage_Low_Thresh_Sleep_Wakeup
*******************************************************************************/
void Low_Thresh_Sleep(void)
{
    #if defined(Low_Thresh__PC)
        Low_Thresh_backup.pcState = Low_Thresh_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Low_Thresh_backup.usbState = Low_Thresh_CR1_REG;
            Low_Thresh_USB_POWER_REG |= Low_Thresh_USBIO_ENTER_SLEEP;
            Low_Thresh_CR1_REG &= Low_Thresh_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Low_Thresh__SIO)
        Low_Thresh_backup.sioState = Low_Thresh_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Low_Thresh_SIO_REG &= (uint32)(~Low_Thresh_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Low_Thresh_Wakeup
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
*  Refer to Low_Thresh_Sleep() for an example usage.
*******************************************************************************/
void Low_Thresh_Wakeup(void)
{
    #if defined(Low_Thresh__PC)
        Low_Thresh_PC = Low_Thresh_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Low_Thresh_USB_POWER_REG &= Low_Thresh_USBIO_EXIT_SLEEP_PH1;
            Low_Thresh_CR1_REG = Low_Thresh_backup.usbState;
            Low_Thresh_USB_POWER_REG &= Low_Thresh_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Low_Thresh__SIO)
        Low_Thresh_SIO_REG = Low_Thresh_backup.sioState;
    #endif
}


/* [] END OF FILE */
