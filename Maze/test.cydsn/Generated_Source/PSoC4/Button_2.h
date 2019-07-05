/*******************************************************************************
* File Name: Button_2.h  
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

#if !defined(CY_PINS_Button_2_H) /* Pins Button_2_H */
#define CY_PINS_Button_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Button_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_2_Write(uint8 value) ;
void    Button_2_SetDriveMode(uint8 mode) ;
uint8   Button_2_ReadDataReg(void) ;
uint8   Button_2_Read(void) ;
uint8   Button_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_2_DRIVE_MODE_BITS        (3)
#define Button_2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Button_2_DRIVE_MODE_BITS))

#define Button_2_DM_ALG_HIZ         (0x00u)
#define Button_2_DM_DIG_HIZ         (0x01u)
#define Button_2_DM_RES_UP          (0x02u)
#define Button_2_DM_RES_DWN         (0x03u)
#define Button_2_DM_OD_LO           (0x04u)
#define Button_2_DM_OD_HI           (0x05u)
#define Button_2_DM_STRONG          (0x06u)
#define Button_2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Button_2_MASK               Button_2__MASK
#define Button_2_SHIFT              Button_2__SHIFT
#define Button_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_2_PS                     (* (reg32 *) Button_2__PS)
/* Port Configuration */
#define Button_2_PC                     (* (reg32 *) Button_2__PC)
/* Data Register */
#define Button_2_DR                     (* (reg32 *) Button_2__DR)
/* Input Buffer Disable Override */
#define Button_2_INP_DIS                (* (reg32 *) Button_2__PC2)


#if defined(Button_2__INTSTAT)  /* Interrupt Registers */

    #define Button_2_INTSTAT                (* (reg32 *) Button_2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Button_2_DRIVE_MODE_SHIFT       (0x00u)
#define Button_2_DRIVE_MODE_MASK        (0x07u << Button_2_DRIVE_MODE_SHIFT)


#endif /* End Pins Button_2_H */


/* [] END OF FILE */
