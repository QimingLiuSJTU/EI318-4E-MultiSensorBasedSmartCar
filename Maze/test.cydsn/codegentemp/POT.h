/*******************************************************************************
* File Name: POT.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_POT_H) /* Pins POT_H */
#define CY_PINS_POT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    POT_Write(uint8 value) ;
void    POT_SetDriveMode(uint8 mode) ;
uint8   POT_ReadDataReg(void) ;
uint8   POT_Read(void) ;
uint8   POT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define POT_DRIVE_MODE_BITS        (3)
#define POT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POT_DRIVE_MODE_BITS))

#define POT_DM_ALG_HIZ         (0x00u)
#define POT_DM_DIG_HIZ         (0x01u)
#define POT_DM_RES_UP          (0x02u)
#define POT_DM_RES_DWN         (0x03u)
#define POT_DM_OD_LO           (0x04u)
#define POT_DM_OD_HI           (0x05u)
#define POT_DM_STRONG          (0x06u)
#define POT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define POT_MASK               POT__MASK
#define POT_SHIFT              POT__SHIFT
#define POT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POT_PS                     (* (reg32 *) POT__PS)
/* Port Configuration */
#define POT_PC                     (* (reg32 *) POT__PC)
/* Data Register */
#define POT_DR                     (* (reg32 *) POT__DR)
/* Input Buffer Disable Override */
#define POT_INP_DIS                (* (reg32 *) POT__PC2)


#if defined(POT__INTSTAT)  /* Interrupt Registers */

    #define POT_INTSTAT                (* (reg32 *) POT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define POT_DRIVE_MODE_SHIFT       (0x00u)
#define POT_DRIVE_MODE_MASK        (0x07u << POT_DRIVE_MODE_SHIFT)


#endif /* End Pins POT_H */


/* [] END OF FILE */
