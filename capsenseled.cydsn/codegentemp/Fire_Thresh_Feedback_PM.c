/*******************************************************************************
* File Name: Fire_Thresh_Feedback.c  
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
#include "Fire_Thresh_Feedback.h"

static Fire_Thresh_Feedback_BACKUP_STRUCT  Fire_Thresh_Feedback_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Fire_Thresh_Feedback_Sleep
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
*  \snippet Fire_Thresh_Feedback_SUT.c usage_Fire_Thresh_Feedback_Sleep_Wakeup
*******************************************************************************/
void Fire_Thresh_Feedback_Sleep(void)
{
    #if defined(Fire_Thresh_Feedback__PC)
        Fire_Thresh_Feedback_backup.pcState = Fire_Thresh_Feedback_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Fire_Thresh_Feedback_backup.usbState = Fire_Thresh_Feedback_CR1_REG;
            Fire_Thresh_Feedback_USB_POWER_REG |= Fire_Thresh_Feedback_USBIO_ENTER_SLEEP;
            Fire_Thresh_Feedback_CR1_REG &= Fire_Thresh_Feedback_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fire_Thresh_Feedback__SIO)
        Fire_Thresh_Feedback_backup.sioState = Fire_Thresh_Feedback_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Fire_Thresh_Feedback_SIO_REG &= (uint32)(~Fire_Thresh_Feedback_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Fire_Thresh_Feedback_Wakeup
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
*  Refer to Fire_Thresh_Feedback_Sleep() for an example usage.
*******************************************************************************/
void Fire_Thresh_Feedback_Wakeup(void)
{
    #if defined(Fire_Thresh_Feedback__PC)
        Fire_Thresh_Feedback_PC = Fire_Thresh_Feedback_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Fire_Thresh_Feedback_USB_POWER_REG &= Fire_Thresh_Feedback_USBIO_EXIT_SLEEP_PH1;
            Fire_Thresh_Feedback_CR1_REG = Fire_Thresh_Feedback_backup.usbState;
            Fire_Thresh_Feedback_USB_POWER_REG &= Fire_Thresh_Feedback_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fire_Thresh_Feedback__SIO)
        Fire_Thresh_Feedback_SIO_REG = Fire_Thresh_Feedback_backup.sioState;
    #endif
}


/* [] END OF FILE */
