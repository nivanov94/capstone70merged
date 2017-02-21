/*******************************************************************************
* File Name: PGA_U_Db.c  
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
#include "PGA_U_Db.h"

static PGA_U_Db_BACKUP_STRUCT  PGA_U_Db_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PGA_U_Db_Sleep
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
*  \snippet PGA_U_Db_SUT.c usage_PGA_U_Db_Sleep_Wakeup
*******************************************************************************/
void PGA_U_Db_Sleep(void)
{
    #if defined(PGA_U_Db__PC)
        PGA_U_Db_backup.pcState = PGA_U_Db_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PGA_U_Db_backup.usbState = PGA_U_Db_CR1_REG;
            PGA_U_Db_USB_POWER_REG |= PGA_U_Db_USBIO_ENTER_SLEEP;
            PGA_U_Db_CR1_REG &= PGA_U_Db_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PGA_U_Db__SIO)
        PGA_U_Db_backup.sioState = PGA_U_Db_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PGA_U_Db_SIO_REG &= (uint32)(~PGA_U_Db_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PGA_U_Db_Wakeup
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
*  Refer to PGA_U_Db_Sleep() for an example usage.
*******************************************************************************/
void PGA_U_Db_Wakeup(void)
{
    #if defined(PGA_U_Db__PC)
        PGA_U_Db_PC = PGA_U_Db_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PGA_U_Db_USB_POWER_REG &= PGA_U_Db_USBIO_EXIT_SLEEP_PH1;
            PGA_U_Db_CR1_REG = PGA_U_Db_backup.usbState;
            PGA_U_Db_USB_POWER_REG &= PGA_U_Db_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PGA_U_Db__SIO)
        PGA_U_Db_SIO_REG = PGA_U_Db_backup.sioState;
    #endif
}


/* [] END OF FILE */
