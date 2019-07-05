/*******************************************************************************
* File Name: PWM_OUT1.h  
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

#if !defined(CY_PINS_PWM_OUT1_H) /* Pins PWM_OUT1_H */
#define CY_PINS_PWM_OUT1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWM_OUT1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWM_OUT1_Write(uint8 value) ;
void    PWM_OUT1_SetDriveMode(uint8 mode) ;
uint8   PWM_OUT1_ReadDataReg(void) ;
uint8   PWM_OUT1_Read(void) ;
uint8   PWM_OUT1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWM_OUT1_DRIVE_MODE_BITS        (3)
#define PWM_OUT1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWM_OUT1_DRIVE_MODE_BITS))

#define PWM_OUT1_DM_ALG_HIZ         (0x00u)
#define PWM_OUT1_DM_DIG_HIZ         (0x01u)
#define PWM_OUT1_DM_RES_UP          (0x02u)
#define PWM_OUT1_DM_RES_DWN         (0x03u)
#define PWM_OUT1_DM_OD_LO           (0x04u)
#define PWM_OUT1_DM_OD_HI           (0x05u)
#define PWM_OUT1_DM_STRONG          (0x06u)
#define PWM_OUT1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PWM_OUT1_MASK               PWM_OUT1__MASK
#define PWM_OUT1_SHIFT              PWM_OUT1__SHIFT
#define PWM_OUT1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWM_OUT1_PS                     (* (reg32 *) PWM_OUT1__PS)
/* Port Configuration */
#define PWM_OUT1_PC                     (* (reg32 *) PWM_OUT1__PC)
/* Data Register */
#define PWM_OUT1_DR                     (* (reg32 *) PWM_OUT1__DR)
/* Input Buffer Disable Override */
#define PWM_OUT1_INP_DIS                (* (reg32 *) PWM_OUT1__PC2)


#if defined(PWM_OUT1__INTSTAT)  /* Interrupt Registers */

    #define PWM_OUT1_INTSTAT                (* (reg32 *) PWM_OUT1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PWM_OUT1_DRIVE_MODE_SHIFT       (0x00u)
#define PWM_OUT1_DRIVE_MODE_MASK        (0x07u << PWM_OUT1_DRIVE_MODE_SHIFT)


#endif /* End Pins PWM_OUT1_H */


/* [] END OF FILE */
