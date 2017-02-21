/*******************************************************************************
* File Name: Mid_Thresh_Feedback.h  
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

#if !defined(CY_PINS_Mid_Thresh_Feedback_ALIASES_H) /* Pins Mid_Thresh_Feedback_ALIASES_H */
#define CY_PINS_Mid_Thresh_Feedback_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Mid_Thresh_Feedback_0			(Mid_Thresh_Feedback__0__PC)
#define Mid_Thresh_Feedback_0_PS		(Mid_Thresh_Feedback__0__PS)
#define Mid_Thresh_Feedback_0_PC		(Mid_Thresh_Feedback__0__PC)
#define Mid_Thresh_Feedback_0_DR		(Mid_Thresh_Feedback__0__DR)
#define Mid_Thresh_Feedback_0_SHIFT	(Mid_Thresh_Feedback__0__SHIFT)
#define Mid_Thresh_Feedback_0_INTR	((uint16)((uint16)0x0003u << (Mid_Thresh_Feedback__0__SHIFT*2u)))

#define Mid_Thresh_Feedback_INTR_ALL	 ((uint16)(Mid_Thresh_Feedback_0_INTR))


#endif /* End Pins Mid_Thresh_Feedback_ALIASES_H */


/* [] END OF FILE */
