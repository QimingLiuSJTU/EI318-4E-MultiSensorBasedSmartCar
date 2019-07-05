/*******************************************************************************
* File Name: LCD_Char_1_BarGraph.c
* Version 2.10
*
* Description:
*  This file provides the custom character data and API for creating and using
*  bar graphs with the Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_Char_1.h"


uint8 const CYCODE LCD_Char_1_customFonts[] = \
{
    /* Character LCD_Char_1_CUSTOM_0   */
    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u, \
    /* Character LCD_Char_1_CUSTOM_1   */
    0x10u,    0x10u,    0x10u,    0x10u,    0x10u,    0x10u,    0x10u,    0x10u, \
    /* Character LCD_Char_1_CUSTOM_2   */
    0x18u,    0x18u,    0x18u,    0x18u,    0x18u,    0x18u,    0x18u,    0x18u, \
    /* Character LCD_Char_1_CUSTOM_3   */
    0x1Cu,    0x1Cu,    0x1Cu,    0x1Cu,    0x1Cu,    0x1Cu,    0x1Cu,    0x1Cu, \
    /* Character LCD_Char_1_CUSTOM_4   */
    0x1Eu,    0x1Eu,    0x1Eu,    0x1Eu,    0x1Eu,    0x1Eu,    0x1Eu,    0x1Eu, \
    /* Character LCD_Char_1_CUSTOM_5   */
    0x1Fu,    0x1Fu,    0x1Fu,    0x1Fu,    0x1Fu,    0x1Fu,    0x1Fu,    0x1Fu, \
    /* Character LCD_Char_1_CUSTOM_6   */
    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u, \
    /* Character LCD_Char_1_CUSTOM_7   */
    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u,    0x00u \
};


/*******************************************************************************
* Function Name: LCD_Char_1_LoadCustomFonts
********************************************************************************
*
* Summary:
*  Loads 8 custom font characters into the LCD Module for use.  Cannot use
*  characters from two different font sets at once, but font sets can be
*  switched out during runtime.
*
* Parameters:
*  customData:  pointer to a constant array of 64 bytes representing 8 custom
*               font characters.
* Return:
*  None.
*
* Theory:
*  Prior to using this function user need to import the pointer to custom
*  font array to your project by writting the following in the source code file
*  where custom font will be used:
*       extern uint8 const CYCODE LCD_Char_customFonts[];
*  This function is not automatically called by the Start() routine and must be
*  called manually by the user.
*******************************************************************************/
void LCD_Char_1_LoadCustomFonts(uint8 const customData[]) 
{
    uint8 indexU8;

    LCD_Char_1_IsReady();
    /* Set starting address in the LCD Module */
    /* Optionally: Read the current address to restore at a later time */
    LCD_Char_1_WriteControl(LCD_Char_1_CGRAM_0);

    /* Load in the 64 bytes of CustomChar Data */
    for(indexU8 = 0u; indexU8 < LCD_Char_1_CUSTOM_CHAR_SET_LEN; indexU8++)
    {
        /* Delay between each write */
        LCD_Char_1_WriteData(customData[indexU8]);
    }

    LCD_Char_1_IsReady();
    LCD_Char_1_WriteControl(LCD_Char_1_DDRAM_0);
}


#if (LCD_Char_1_CUSTOM_CHAR_SET == LCD_Char_1_HORIZONTAL_BG)

    /*******************************************************************************
    * Function Name: LCD_Char_1_DrawHorizontalBG
    ********************************************************************************
    *
    * Summary:
    *  Draws the horizontal bargraph.
    *
    * Parameters:
    *  row:            The row in which the bar graph starts.
    *  column:         The column in which the bar graph starts.
    *  maxCharacters:  The max length of the graph in whole characters.
    *  value:          The current length or height of the graph in pixels.
    *
    * Return:
    *  void.
    *
    *******************************************************************************/
    void LCD_Char_1_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value) \
                                                            
    {
        /* 8-bit Counter */
        uint8 count8;
        uint8 fullChars;
        uint8 remainingPixels;

        /* Number of full characters to draw */
        fullChars = value / LCD_Char_1_CHARACTER_WIDTH;

        /* Number of remaining pixels to draw */
        remainingPixels = value % LCD_Char_1_CHARACTER_WIDTH;

        /* Ensure that the maximum character limit is followed. */
        if(fullChars >= maxCharacters)
        {
            fullChars = maxCharacters;
        }

        /* Put Cursor at start position */
        LCD_Char_1_Position(row, column);

        /* Write full characters */
        for(count8 = 0u; count8 < fullChars; count8++)
        {
            LCD_Char_1_WriteData(LCD_Char_1_CUSTOM_5);
        }

        if(fullChars < maxCharacters)
        {
            /* Write remaining pixels */
            LCD_Char_1_WriteData(remainingPixels);

            if(fullChars < (maxCharacters - 1u))
            {
                /* Fill with whitespace to end of bar graph */
                for(count8 = 0u; count8 < (maxCharacters - fullChars - 1u); count8++)
                {
                    LCD_Char_1_WriteData(LCD_Char_1_CUSTOM_0);
                }
            }
        }
    }

#endif /* LCD_Char_1_CUSTOM_CHAR_SET == LCD_Char_1_HORIZONTAL_BG */


#if (LCD_Char_1_CUSTOM_CHAR_SET == LCD_Char_1_VERTICAL_BG)

    /*******************************************************************************
    *  Function Name: LCD_Char_1_DrawVerticalBG
    ********************************************************************************
    *
    * Summary:
    *  Draws the vertical bargraph.
    *
    * Parameters:
    *  row:            The row in which the bar graph starts.
    *  column:         The column in which the bar graph starts.
    *  maxCharacters:  The max height of the graph in whole characters.
    *  value:          The current length or height of the graph in pixels.
    *
    * Return:
    *  void.
    *
    *******************************************************************************/
    void LCD_Char_1_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value) \
                                                            
    {
        /* 8-bit Counter */
        uint8 count8 = 0u;
        /* Current Row Tracker */
        int8 currentRow;
        uint8 fullChars;
        uint8 remainingPixels;

        /* Number of full characters to draw */
        fullChars = value / LCD_Char_1_CHARACTER_HEIGHT;

        /* Number of remaining pixels to draw */
        remainingPixels = value % LCD_Char_1_CHARACTER_HEIGHT;

        /* Put Cursor at start position */
        LCD_Char_1_Position(row, column);

        /* Make sure the bar graph fits inside the space allotted */
        if(fullChars >= maxCharacters)
        {
            fullChars = maxCharacters;
        }

        /*  Write full characters */
        while(count8 < fullChars)
        {
            LCD_Char_1_WriteData(LCD_Char_1_CUSTOM_7);

            count8++;

            /* Each pass through, move one row higher */
            if((((int8) row) - ((int8) count8)) >= 0)
            {
                LCD_Char_1_Position(row - count8, column);
            }
            else
            {
                break;
            }
        }

        if(((((int8) row) - ((int8) count8)) >= 0) && (fullChars < maxCharacters))
        {
            /* Write remaining pixels */
            if(remainingPixels == 0u)
            {
                LCD_Char_1_WriteData((uint8) ' ');
            }
            else
            {
                LCD_Char_1_WriteData(remainingPixels - 1u);
            }

            currentRow = ((int8) row) - ((int8) count8) - 1;

            if(currentRow >= 0)
            {
                /* Move up one row and fill with whitespace till top of bar graph */
                for(count8 = 0u; count8 < (maxCharacters - fullChars - 1u); count8++)
                {
                    LCD_Char_1_Position((uint8)currentRow, column);
                    LCD_Char_1_WriteData((uint8) ' ');
                    currentRow --;
                }
            }
        }
    }

#endif /* LCD_Char_1_CUSTOM_CHAR_SET == LCD_Char_1_VERTICAL_BG */


/* [] END OF FILE */
