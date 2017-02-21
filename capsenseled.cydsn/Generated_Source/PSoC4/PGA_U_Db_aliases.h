/*******************************************************************************
* File Name: PGA_U_Db.h  
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

#if !defined(CY_PINS_PGA_U_Db_ALIASES_H) /* Pins PGA_U_Db_ALIASES_H */
#define CY_PINS_PGA_U_Db_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PGA_U_Db_0			(PGA_U_Db__0__PC)
#define PGA_U_Db_0_PS		(PGA_U_Db__0__PS)
#define PGA_U_Db_0_PC		(PGA_U_Db__0__PC)
#define PGA_U_Db_0_DR		(PGA_U_Db__0__DR)
#define PGA_U_Db_0_SHIFT	(PGA_U_Db__0__SHIFT)
#define PGA_U_Db_0_INTR	((uint16)((uint16)0x0003u << (PGA_U_Db__0__SHIFT*2u)))

#define PGA_U_Db_INTR_ALL	 ((uint16)(PGA_U_Db_0_INTR))


#endif /* End Pins PGA_U_Db_ALIASES_H */


/* [] END OF FILE */
