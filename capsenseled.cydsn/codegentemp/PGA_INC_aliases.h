/*******************************************************************************
* File Name: PGA_INC.h  
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

#if !defined(CY_PINS_PGA_INC_ALIASES_H) /* Pins PGA_INC_ALIASES_H */
#define CY_PINS_PGA_INC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PGA_INC_0			(PGA_INC__0__PC)
#define PGA_INC_0_PS		(PGA_INC__0__PS)
#define PGA_INC_0_PC		(PGA_INC__0__PC)
#define PGA_INC_0_DR		(PGA_INC__0__DR)
#define PGA_INC_0_SHIFT	(PGA_INC__0__SHIFT)
#define PGA_INC_0_INTR	((uint16)((uint16)0x0003u << (PGA_INC__0__SHIFT*2u)))

#define PGA_INC_INTR_ALL	 ((uint16)(PGA_INC_0_INTR))


#endif /* End Pins PGA_INC_ALIASES_H */


/* [] END OF FILE */
