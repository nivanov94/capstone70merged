/*******************************************************************************
* File Name: Low_Thresh_Feedback.h  
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

#if !defined(CY_PINS_Low_Thresh_Feedback_ALIASES_H) /* Pins Low_Thresh_Feedback_ALIASES_H */
#define CY_PINS_Low_Thresh_Feedback_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Low_Thresh_Feedback_0			(Low_Thresh_Feedback__0__PC)
#define Low_Thresh_Feedback_0_PS		(Low_Thresh_Feedback__0__PS)
#define Low_Thresh_Feedback_0_PC		(Low_Thresh_Feedback__0__PC)
#define Low_Thresh_Feedback_0_DR		(Low_Thresh_Feedback__0__DR)
#define Low_Thresh_Feedback_0_SHIFT	(Low_Thresh_Feedback__0__SHIFT)
#define Low_Thresh_Feedback_0_INTR	((uint16)((uint16)0x0003u << (Low_Thresh_Feedback__0__SHIFT*2u)))

#define Low_Thresh_Feedback_INTR_ALL	 ((uint16)(Low_Thresh_Feedback_0_INTR))


#endif /* End Pins Low_Thresh_Feedback_ALIASES_H */


/* [] END OF FILE */
