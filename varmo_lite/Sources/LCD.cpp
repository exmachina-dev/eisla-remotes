#include "I2C0.h"
#include "LED_STATUS_1.h"
#include "WAIT1.h"

#include "LCD_CTR.h"
#include "BitIoLdd6.h"

#include "PCA9670.h"

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PCA9665_ADDR 0x20
byte err;
word ret;
byte LCD_flag;

/* DEFINES for display commands.
   See
   - www.freescale.com/files/microcontrollers/doc/app_note/AN1745.pdf
   - http://www.mikrocontroller.net/articles/HD44780
   for additional details.
*/


#define ClearDisplayCmd                 0x01 /* clears the display */

#define ReturnHomeCmd                   0x02 /* moves the cursor to the beginning of the first line */

#define EntryModeSetCmd                 0x04
  #define EntryModeSet_ShiftOn             1 /* S flag: shift display */
  #define EntryModeSet_IncrementOn         2 /* I/D flag: increment cursor */

#define DisplayOnOffControlCmd          0x08 /* Display on/off control command. There are 3 bits D, C and B as well */
  #define DisplayOnOffControl_BlinkOn      1 /* B flag: blinking cursor on/off; B=1 blinking, B=0 not blinking */
  #define DisplayOnOffControl_CursorOn     2 /* C flag: cursor on/off, C=1 cursor on, C=0 cursor off */
  #define DisplayOnOffControl_DisplayOn    4 /* D flag: display on/off, D=1 display on, D=0 display off */

#define FunctionSetCmd                  0x20
  #define FunctionSet_8bit              0x10 /* DL flag: DL=1: 8bit, DL=0: 4bit */
  #define FunctionSet_4bit                 0 /* DL flag: DL=1: 8bit, DL=0: 4bit */
  #define FunctionSet_2Lines            0x08 /* N flag: number of display lines: N=1 2 or 4 lines, N=0 1 line */
  #define FunctionSet_1Line                0 /* N flag: number of display lines: N=1 2 or 4 lines, N=0 1 line */
  #define FunctionSet_Font5x10          0x04 /* F flag: character font, F=1 5x10 dots, F=0 5x8 dots */
  #define FunctionSet_Font5x8              0 /* F flag: character font, F=1 5x10 dots, F=0 5x8 dots */

#define CursorOnCmd    (DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn|DisplayOnOffControl_CursorOn)
#define CursorOffCmd   (DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn)
#define CursorBlinkOnCmd    (DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn|DisplayOnOffControl_BlinkOn)
#define CursorBlinkOffCmd   (DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn)
#define GotoXYCmd      0x80  /* 0x80 | Display RAM address */
#define Line1Offset    0x00 /* Display RAM address of first line, usually 0x00 */
#define Line2Offset    0x40 /* Display RAM address of second line, usually 0x40 */
#define Line3Offset    0x10 /* Display RAM address of third line, usually 0x10 */
#define Line4Offset    0x50 /* Display RAM address of fourth line, usually 0x50 */
#define FirstLineCmd   (GotoXYCmd|Line1Offset)
#define SecondLineCmd  (GotoXYCmd|Line2Offset)
#define ThirdLineCmd   (GotoXYCmd|Line3Offset)
#define FourthLineCmd  (GotoXYCmd|Line4Offset)

#define RightShiftCmd      0x1C
#define LeftShiftCmd       0x18
#define RightShiftCursor   0x14
#define LeftShiftCursor    0x10

#define BusyFlag       0x80 /* BF Flag */

void LCD_Init() {
	(void)I2C0_SelectSlave(PCA9665_ADDR);

	LCD_flag = 0;
	if (I2C0_GetMode()) { // Check for master mode
		//I2C0_SendChar(PCA9665_ADDR);
		LED_STATUS_1_SetVal();

		LCD_CTR_ClrVal();

		/*Datatsheet screen*/

		PCA9670_SendByte(FunctionSetCmd|FunctionSet_Font5x8|FunctionSet_8bit|FunctionSet_2Lines, 1); //0x20|0x10|0x08 = 0x38;

		//PCA9670_SendByte(CursorOnCmd, 1);
		PCA9670_SendByte(DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn, 1);

		PCA9670_SendByte(ClearDisplayCmd, 1); //0X01

		PCA9670_SendByte(EntryModeSetCmd|EntryModeSet_IncrementOn, 10); //0x04|0x02 = 0x06)
	}
}

void LCD_command(uint8_t value){
	(void)I2C0_SelectSlave(PCA9665_ADDR);
	LCD_CTR_ClrVal();
	if (I2C0_GetMode()) { // Check for master mode
		PCA9670_SendByte(value, 1);
	}
}

/* Clear the display*/
void LCD_Clear() {
	LCD_command(ClearDisplayCmd);
}

/*LCD Cursor On */
void LCD_Cursor_On(){
	LCD_command(CursorOnCmd);
}

/*LCD Cursor Off*/
void LCD_Cursor_Off(){
	LCD_command(CursorOffCmd);
}

/*LCD Cursor Blink On*/
void LCD_Cursor_Blink_On(){
	LCD_command(CursorBlinkOnCmd);
}

/*LCD Cursor Blink Off*/
void LCD_Cursor_Blink_Off(){
	LCD_command(CursorBlinkOffCmd);
}

/*LCD return cursor home*/
void LCD_Cursor_Home(){
	LCD_command(ReturnHomeCmd);
}

/*LCD Set Cursor*/
void LCD_Set_Cursor(uint8_t line, uint8_t x){
	uint8_t RAM_Adr;
	if (line == 0){
		RAM_Adr = (Line1Offset + x);
	}
	else if (line == 1){
		RAM_Adr = (Line2Offset + x);
	}
	else if (line == 2){
		RAM_Adr = (Line3Offset + x);
	}
	else if (line == 3){
		RAM_Adr = (Line4Offset + x);
	}
	LCD_command(GotoXYCmd|RAM_Adr);
}

void LCD_Cursor_Blink_On_At(uint8_t line, uint8_t x){
	LCD_Set_Cursor(line, x);
	LCD_Cursor_Blink_On();
}

void LCD_Cursor_On_At(uint8_t line, uint8_t x){
	LCD_Set_Cursor(line, x);
	LCD_Cursor_On();
}

void LCD_Write(uint8_t value){
 	LCD_CTR_SetVal();
	PCA9670_SendByte(value, 1);
}

void load_custom_char(uint8_t value, uint8_t *rows){
	PCA9670_SendByte(FunctionSetCmd|FunctionSet_Font5x8|FunctionSet_8bit|FunctionSet_2Lines, 1); //0x20|0x10|0x08 = 0x38;
	LCD_command(0x40 +(value * 8));
	for (int i = 0; i< 8;i++){
		LCD_Write(rows[i]);
	}
	LCD_command(0x39);
}

void LCD_Write_At(uint8_t value, uint8_t line, uint8_t x){
	LCD_Set_Cursor(line, x);
 	LCD_CTR_SetVal();
	LCD_Write(value);
}

void LCD_Write_Block(char* buffer, uint8_t line, uint8_t x ){
	int length = strlen(buffer);
	int x_cnt = x;
	int y_cnt = line;
	LCD_Set_Cursor(y_cnt, x_cnt);
	for (int i = 0; i < length; i++){
		if (x_cnt > 15){
			// End Of the line
			if (y_cnt == 3){
				// Last Line, go to the first line
				y_cnt = 0;
			}
			else{
				y_cnt += 1;
			}
			x_cnt = 0;
			LCD_Set_Cursor(y_cnt, x_cnt);
		}
		if(buffer[i] != '\0'){
			LCD_Write(buffer[i]);
			x_cnt += 1;
		}
		else{
			x_cnt = length;
		}

	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
