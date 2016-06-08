#ifdef __cplusplus
extern "C" {
#endif

void LCD_Init(void);
void LCD_command(uint8_t);
void LCD_Clear(void);
void LCD_Cursor_On(void);
void LCD_Cursor_Off(void);
void LCD_Cursor_Hone(void);
void LCD_Set_Cursor(uint8_t, uint8_t);

#ifdef __cplusplus
}  /* extern "C" */
#endif
