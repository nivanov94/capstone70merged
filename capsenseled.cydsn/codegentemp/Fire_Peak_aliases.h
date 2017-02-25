/*******************************************************************************
* File Name: Fire_Peak.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Fire_Peak_ALIASES_H) /* Pins Fire_Peak_ALIASES_H */
#define CY_PINS_Fire_Peak_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Fire_Peak_0			(Fire_Peak__0__PC)
#define Fire_Peak_0_PS		(Fire_Peak__0__PS)
#define Fire_Peak_0_PC		(Fire_Peak__0__PC)
#define Fire_Peak_0_DR		(Fire_Peak__0__DR)
#define Fire_Peak_0_SHIFT	(Fire_Peak__0__SHIFT)
#define Fire_Peak_0_INTR	((uint16)((uint16)0x0003u << (Fire_Peak__0__SHIFT*2u)))

#define Fire_Peak_INTR_ALL	 ((uint16)(Fire_Peak_0_INTR))


#endif /* End Pins Fire_Peak_ALIASES_H */


/* [] END OF FILE */
