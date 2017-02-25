/*******************************************************************************
* File Name: High_Peak.h  
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

#if !defined(CY_PINS_High_Peak_ALIASES_H) /* Pins High_Peak_ALIASES_H */
#define CY_PINS_High_Peak_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define High_Peak_0			(High_Peak__0__PC)
#define High_Peak_0_PS		(High_Peak__0__PS)
#define High_Peak_0_PC		(High_Peak__0__PC)
#define High_Peak_0_DR		(High_Peak__0__DR)
#define High_Peak_0_SHIFT	(High_Peak__0__SHIFT)
#define High_Peak_0_INTR	((uint16)((uint16)0x0003u << (High_Peak__0__SHIFT*2u)))

#define High_Peak_INTR_ALL	 ((uint16)(High_Peak_0_INTR))


#endif /* End Pins High_Peak_ALIASES_H */


/* [] END OF FILE */
