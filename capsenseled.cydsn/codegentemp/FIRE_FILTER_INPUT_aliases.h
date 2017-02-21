/*******************************************************************************
* File Name: FIRE_FILTER_INPUT.h  
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

#if !defined(CY_PINS_FIRE_FILTER_INPUT_ALIASES_H) /* Pins FIRE_FILTER_INPUT_ALIASES_H */
#define CY_PINS_FIRE_FILTER_INPUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FIRE_FILTER_INPUT_0			(FIRE_FILTER_INPUT__0__PC)
#define FIRE_FILTER_INPUT_0_PS		(FIRE_FILTER_INPUT__0__PS)
#define FIRE_FILTER_INPUT_0_PC		(FIRE_FILTER_INPUT__0__PC)
#define FIRE_FILTER_INPUT_0_DR		(FIRE_FILTER_INPUT__0__DR)
#define FIRE_FILTER_INPUT_0_SHIFT	(FIRE_FILTER_INPUT__0__SHIFT)
#define FIRE_FILTER_INPUT_0_INTR	((uint16)((uint16)0x0003u << (FIRE_FILTER_INPUT__0__SHIFT*2u)))

#define FIRE_FILTER_INPUT_INTR_ALL	 ((uint16)(FIRE_FILTER_INPUT_0_INTR))


#endif /* End Pins FIRE_FILTER_INPUT_ALIASES_H */


/* [] END OF FILE */
