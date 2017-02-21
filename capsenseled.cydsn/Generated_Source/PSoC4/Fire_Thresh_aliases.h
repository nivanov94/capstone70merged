/*******************************************************************************
* File Name: Fire_Thresh.h  
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

#if !defined(CY_PINS_Fire_Thresh_ALIASES_H) /* Pins Fire_Thresh_ALIASES_H */
#define CY_PINS_Fire_Thresh_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Fire_Thresh_0			(Fire_Thresh__0__PC)
#define Fire_Thresh_0_PS		(Fire_Thresh__0__PS)
#define Fire_Thresh_0_PC		(Fire_Thresh__0__PC)
#define Fire_Thresh_0_DR		(Fire_Thresh__0__DR)
#define Fire_Thresh_0_SHIFT	(Fire_Thresh__0__SHIFT)
#define Fire_Thresh_0_INTR	((uint16)((uint16)0x0003u << (Fire_Thresh__0__SHIFT*2u)))

#define Fire_Thresh_INTR_ALL	 ((uint16)(Fire_Thresh_0_INTR))


#endif /* End Pins Fire_Thresh_ALIASES_H */


/* [] END OF FILE */
