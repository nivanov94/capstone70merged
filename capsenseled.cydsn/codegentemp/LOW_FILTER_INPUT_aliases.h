/*******************************************************************************
* File Name: LOW_FILTER_INPUT.h  
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

#if !defined(CY_PINS_LOW_FILTER_INPUT_ALIASES_H) /* Pins LOW_FILTER_INPUT_ALIASES_H */
#define CY_PINS_LOW_FILTER_INPUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LOW_FILTER_INPUT_0			(LOW_FILTER_INPUT__0__PC)
#define LOW_FILTER_INPUT_0_PS		(LOW_FILTER_INPUT__0__PS)
#define LOW_FILTER_INPUT_0_PC		(LOW_FILTER_INPUT__0__PC)
#define LOW_FILTER_INPUT_0_DR		(LOW_FILTER_INPUT__0__DR)
#define LOW_FILTER_INPUT_0_SHIFT	(LOW_FILTER_INPUT__0__SHIFT)
#define LOW_FILTER_INPUT_0_INTR	((uint16)((uint16)0x0003u << (LOW_FILTER_INPUT__0__SHIFT*2u)))

#define LOW_FILTER_INPUT_INTR_ALL	 ((uint16)(LOW_FILTER_INPUT_0_INTR))


#endif /* End Pins LOW_FILTER_INPUT_ALIASES_H */


/* [] END OF FILE */
