/*******************************************************************************
* File Name: POT.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "POT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        POT_PC =   (POT_PC & \
                                (uint32)(~(uint32)(POT_DRIVE_MODE_IND_MASK << (POT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (POT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: POT_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void POT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(POT_DR & (uint8)(~POT_MASK));
    drVal = (drVal | ((uint8)(value << POT_SHIFT) & POT_MASK));
    POT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: POT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  POT_DM_STRONG     Strong Drive 
*  POT_DM_OD_HI      Open Drain, Drives High 
*  POT_DM_OD_LO      Open Drain, Drives Low 
*  POT_DM_RES_UP     Resistive Pull Up 
*  POT_DM_RES_DWN    Resistive Pull Down 
*  POT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  POT_DM_DIG_HIZ    High Impedance Digital 
*  POT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void POT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(POT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: POT_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro POT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 POT_Read(void) 
{
    return (uint8)((POT_PS & POT_MASK) >> POT_SHIFT);
}


/*******************************************************************************
* Function Name: POT_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 POT_ReadDataReg(void) 
{
    return (uint8)((POT_DR & POT_MASK) >> POT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(POT_INTSTAT) 

    /*******************************************************************************
    * Function Name: POT_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 POT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(POT_INTSTAT & POT_MASK);
		POT_INTSTAT = maskedStatus;
        return maskedStatus >> POT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
