/*******************************************************************************
* File Name: Encoder_3.h  
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

#if !defined(CY_PINS_Encoder_3_H) /* Pins Encoder_3_H */
#define CY_PINS_Encoder_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Encoder_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Encoder_3_Write(uint8 value) ;
void    Encoder_3_SetDriveMode(uint8 mode) ;
uint8   Encoder_3_ReadDataReg(void) ;
uint8   Encoder_3_Read(void) ;
uint8   Encoder_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Encoder_3_DRIVE_MODE_BITS        (3)
#define Encoder_3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Encoder_3_DRIVE_MODE_BITS))

#define Encoder_3_DM_ALG_HIZ         (0x00u)
#define Encoder_3_DM_DIG_HIZ         (0x01u)
#define Encoder_3_DM_RES_UP          (0x02u)
#define Encoder_3_DM_RES_DWN         (0x03u)
#define Encoder_3_DM_OD_LO           (0x04u)
#define Encoder_3_DM_OD_HI           (0x05u)
#define Encoder_3_DM_STRONG          (0x06u)
#define Encoder_3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Encoder_3_MASK               Encoder_3__MASK
#define Encoder_3_SHIFT              Encoder_3__SHIFT
#define Encoder_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Encoder_3_PS                     (* (reg32 *) Encoder_3__PS)
/* Port Configuration */
#define Encoder_3_PC                     (* (reg32 *) Encoder_3__PC)
/* Data Register */
#define Encoder_3_DR                     (* (reg32 *) Encoder_3__DR)
/* Input Buffer Disable Override */
#define Encoder_3_INP_DIS                (* (reg32 *) Encoder_3__PC2)


#if defined(Encoder_3__INTSTAT)  /* Interrupt Registers */

    #define Encoder_3_INTSTAT                (* (reg32 *) Encoder_3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Encoder_3_DRIVE_MODE_SHIFT       (0x00u)
#define Encoder_3_DRIVE_MODE_MASK        (0x07u << Encoder_3_DRIVE_MODE_SHIFT)


#endif /* End Pins Encoder_3_H */


/* [] END OF FILE */
