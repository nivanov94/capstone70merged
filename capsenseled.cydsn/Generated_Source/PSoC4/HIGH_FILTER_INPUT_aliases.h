/*******************************************************************************
* File Name: HIGH_FILTER_INPUT.h  
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

#if !defined(CY_PINS_HIGH_FILTER_INPUT_ALIASES_H) /* Pins HIGH_FILTER_INPUT_ALIASES_H */
#define CY_PINS_HIGH_FILTER_INPUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HIGH_FILTER_INPUT_0			(HIGH_FILTER_INPUT__0__PC)
#define HIGH_FILTER_INPUT_0_PS		(HIGH_FILTER_INPUT__0__PS)
#define HIGH_FILTER_INPUT_0_PC		(HIGH_FILTER_INPUT__0__PC)
#define HIGH_FILTER_INPUT_0_DR		(HIGH_FILTER_INPUT__0__DR)
#define HIGH_FILTER_INPUT_0_SHIFT	(HIGH_FILTER_INPUT__0__SHIFT)
#define HIGH_FILTER_INPUT_0_INTR	((uint16)((uint16)0x0003u << (HIGH_FILTER_INPUT__0__SHIFT*2u)))

#define HIGH_FILTER_INPUT_INTR_ALL	 ((uint16)(HIGH_FILTER_INPUT_0_INTR))


#endif /* End Pins HIGH_FILTER_INPUT_ALIASES_H */


/* [] END OF FILE */
