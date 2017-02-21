/*******************************************************************************
* File Name: USER_INPUT.h  
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

#if !defined(CY_PINS_USER_INPUT_ALIASES_H) /* Pins USER_INPUT_ALIASES_H */
#define CY_PINS_USER_INPUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define USER_INPUT_0			(USER_INPUT__0__PC)
#define USER_INPUT_0_PS		(USER_INPUT__0__PS)
#define USER_INPUT_0_PC		(USER_INPUT__0__PC)
#define USER_INPUT_0_DR		(USER_INPUT__0__DR)
#define USER_INPUT_0_SHIFT	(USER_INPUT__0__SHIFT)
#define USER_INPUT_0_INTR	((uint16)((uint16)0x0003u << (USER_INPUT__0__SHIFT*2u)))

#define USER_INPUT_INTR_ALL	 ((uint16)(USER_INPUT_0_INTR))


#endif /* End Pins USER_INPUT_ALIASES_H */


/* [] END OF FILE */
