/*******************************************************************************
* File Name: Mid_Peak.h  
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

#if !defined(CY_PINS_Mid_Peak_ALIASES_H) /* Pins Mid_Peak_ALIASES_H */
#define CY_PINS_Mid_Peak_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Mid_Peak_0			(Mid_Peak__0__PC)
#define Mid_Peak_0_PS		(Mid_Peak__0__PS)
#define Mid_Peak_0_PC		(Mid_Peak__0__PC)
#define Mid_Peak_0_DR		(Mid_Peak__0__DR)
#define Mid_Peak_0_SHIFT	(Mid_Peak__0__SHIFT)
#define Mid_Peak_0_INTR	((uint16)((uint16)0x0003u << (Mid_Peak__0__SHIFT*2u)))

#define Mid_Peak_INTR_ALL	 ((uint16)(Mid_Peak_0_INTR))


#endif /* End Pins Mid_Peak_ALIASES_H */


/* [] END OF FILE */