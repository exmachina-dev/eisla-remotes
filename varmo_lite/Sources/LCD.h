#include <string.h>
#include <stdio.h>
#include "stdint.h"

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

void LCD_Init(void);
void LCD_command(uint8_t);
void LCD_Clear(void);
void LCD_Cursor_On(void);
void LCD_Cursor_Off(void);
void LCD_Cursor_Blink_On(void);
void LCD_Cursor_Blink_Off(void);
void LCD_Cursor_Home(void);
void LCD_Set_Cursor(uint8_t, uint8_t);
void LCD_Cursor_On_At(uint8_t, uint8_t);
void LCD_Write(uint8_t);
void load_custom_char(uint8_t, uint8_t* );
void LCD_Write_At(uint8_t, uint8_t, uint8_t);
void LCD_Write_Block(char*, uint8_t, uint8_t );

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_LCD_H_ */
