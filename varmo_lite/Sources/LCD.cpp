#include "I2C0.h"
#include "LED_STATUS_3.h"
#include "WAIT1.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PCA9665_ADDR 0xE0
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
		I2C0_SendChar(PCA9665_ADDR);
		LED_STATUS_3_SetVal();
		ret = I2C0_SendChar(0);
		WAIT1_Waitms(10);
		ret = I2C0_SendChar(FunctionSetCmd|FunctionSet_8bit);
		WAIT1_Waitms(10);
		ret = I2C0_SendChar(FunctionSetCmd|FunctionSet_Font5x8|FunctionSet_8bit|FunctionSet_2Lines);
		WAIT1_Waitms(10);
		ret = I2C0_SendChar(DisplayOnOffControlCmd|DisplayOnOffControl_DisplayOn);
		ret = I2C0_SendChar(ClearDisplayCmd);
		ret = I2C0_SendChar(EntryModeSetCmd|EntryModeSet_IncrementOn);
	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
