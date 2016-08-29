/* ###################################################################
**     Filename    : main.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-03, 16:50, # CodeGen: 62
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED_DEBUG.h"
#include "BitIoLdd1.h"
#include "T_500ms.h"
#include "LED_STATUS_1.h"
#include "BitIoLdd2.h"
#include "LED_STATUS_2.h"
#include "BitIoLdd3.h"
#include "LED_STATUS_3.h"
#include "BitIoLdd4.h"
#include "LED_STATUS_4.h"
#include "BitIoLdd5.h"
#include "ENCODER.h"
#include "ENCODER_PUSH.h"
#include "ExtIntLdd1.h"
#include "LEVER_DIR1.h"
#include "ExtIntLdd2.h"
#include "LEVER_DIR2.h"
#include "ExtIntLdd3.h"
#include "T_100ms.h"
#include "I2C0.h"
#include "IntI2cLdd1.h"
#include "PUSH_BUTTON_SEND.h"
#include "ExtIntLdd4.h"
#include "PUSH_BUTTON_REC.h"
#include "ExtIntLdd5.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "LCD_CTR.h"
#include "BitIoLdd6.h"
#include "WAIT1.h"
#include "LCD_EN.h"
#include "BitIoLdd7.h"
#include "TU1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "KSDK1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "encoder_variable.h"
#include "display.h"
#include "protocol.h"
#include "LCD.h"
#include "PCA9670.h"
#include "parameters.h"
#include "send.h"
#include <stdio.h>
#include <stdlib.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  counter_100ms =0;
  FLAG_PUSH_LONG = 0;
  FLAG_PUSH_SHORT = 0;
  cnt = 0;
  FLAG_MSG_RCV = 0;
  FLAG_MSG_ERR = 0;
  FLAG_MSG_OK = 0;
  FLAG_MENU = 1;
  FLAG_DEBOUNCE = 1;

  FLAG_CONTROL_MODE = 0;

  FLAG_SENS = 0;
  FLAG_SENS_1 = 0;
  FLAG_SENS_2 = 0;

  nb_data = 0;
  drive_enable_st = 1;
  LED_STATUS_1_ClrVal();
  LED_STATUS_2_ClrVal();


  int cnt_err = 0;
  int cnt_ok = 0;
  WAIT1_Waitms(15);
  PCA9670_Init();
  T_100ms_Disable(T_100ms_DeviceData);
  TU1_Disable(TU1_DeviceData);
  LCD_Init();
  parameters_init();

  //LCD_Cursor_Blink_On();
  //LCD_Write_Block("Varmo V2.0", 1, 3);

  menu_init();
  bool DIR1 = LEVER_DIR1_GetVal();
  bool DIR2 = LEVER_DIR2_GetVal();

  if (DIR1 == 0 && DIR2 == 1){
	  FLAG_SENS = 1;
	  FLAG_SENS_1 = 1;
	  FLAG_SENS_2 = 0;
  }
  else if (DIR1 == 1 && DIR2 == 0){
	  FLAG_SENS = 1;
	  FLAG_SENS_1 = 0;
	  FLAG_SENS_2 = 1;
  }
  else {
	  FLAG_STOP = 1;
  }
  update_icon_dir(FLAG_SENS_1, FLAG_SENS_2);
  update_icon_drive_enable();

  for(;;){
	  char msg[cnt];
	  int nb_data = 0;

	  if (FLAG_ENCODER == 1){
		  if (FLAG_MENU == 1){
			  encoder = refresh((int)encoder);
		  }
		  else {
			  refresh_fct(menu_indicator);
		  }
		  FLAG_ENCODER = 0;
	  }

	  if (FLAG_PUSH_SHORT == 1 && FLAG_MENU == 1){
		  int temp = select((int)encoder);
		  if (FLAG_MENU == 1){
			  encoder = temp;
		  }
		  FLAG_PUSH_SHORT = 0;
	  }

	  if(FLAG_REC == 1 && FLAG_CUE_MODE == 1){
		  FLAG_REC = 0;
		  select_cue(encoder, menu_indicator);
		  refresh_fct(menu_indicator);
	  }

	  if (FLAG_PUSH_LONG == 1){
		  encoder = back((int) encoder);
		  FLAG_PUSH_LONG = 0;
	  }

	  if (FLAG_SEND == 1 && FLAG_MENU == 0 && !(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 0)){
		  send_fct(menu_indicator);
		  refresh_fct(menu_indicator);
		  FLAG_SEND = 0;
	  }
	  else if (FLAG_SEND == 1){
		  FLAG_SEND = 0;
	  }

	  if(FLAG_SENS == 1){
		  update_icon_dir(FLAG_SENS_1, FLAG_SENS_2);
	  }

	  if (FLAG_MENU == 0 && FLAG_SENS == 1){
		  FLAG_SENS = 0;
		  refresh_fct(menu_indicator);
	  }

	  if (FLAG_CONTROL_MODE == 1){
		  FLAG_CONTROL_MODE = 0;
		  control_mode_fct();
		  LED_STATUS_1_NegVal();
	  }

	  if (FLAG_CONTROL_MODE_CONFIRM == 1){
		  FLAG_CONTROL_MODE_CONFIRM = 0;
		  controle_mode_display(CONTROL_MODE);
		  get_update_value(CONTROL_MODE);
	  }

	  if (FLAG_UPDATE_CUE == 1){
		  FLAG_UPDATE_CUE = 0;
		  refresh_fct(menu_indicator);
	  }

	  if (FLAG_UPDATE_MENU == 1 && FLAG_MENU == 0 && FLAG_CUE_MODE == 0){
		  get_update_value(CONTROL_MODE);
		  FLAG_UPDATE_MENU = 0;
		  refresh_fct(menu_indicator);
	  }

	  if (FLAG_SHORT_CUT == 1){
		  FLAG_SHORT_CUT = 0;
		  short_cut_position_menu();
	  }

	  if (FLAG_SEND_STOP == 1){
		  FLAG_SEND_STOP = 0;
		  send_stop();
	  }

	  if (FLAG_UPDATE == 1){
		  FLAG_UPDATE = 0;
		  get_update_drive_en();
		  update_icon_drive_enable();
	  }

	  //Check message received
	  binaryRepr size;
	  if (FLAG_MSG_RCV == 1){
		  size.toUint_8.toUint_8_1 = in_buffer[8];
		  size.toUint_8.toUint_8_0 = in_buffer[9];
		  size.toInt.int0 = (size.toUint_8.toUint_8_1 && 0xFF00) + size.toUint_8.toUint_8_0;
		  if ( size.toInt.int0 == (cnt + 1)){
			  int temp = cnt;
			  cnt = 0;
			  for (int f =0; f<=temp; f++){
				  msg[f] = in_buffer[f];
				  if (msg[f] == ':' || msg[f]== '\r'){
					  nb_data += 1;
				  }
				  FLAG_MSG_OK =1;
			  }
		  }
		  else{
			  cnt = 0;
			  FLAG_MSG_ERR = 1;
		  }
		  FLAG_MSG_RCV = 0;
	  }

	  ///Processing msg received
	  if (FLAG_MSG_OK == 1){
		  FLAG_MSG_ERR = msg_parse(msg, size.toInt.int0);
		  FLAG_MSG_OK  = 0;
	  }
	  /*
	  //COMMUNICATION ERR
	  if (FLAG_MSG_ERR == 1){
		  cnt_err += 1;
		  LED_STATUS_2_SetVal();
		  LED_STATUS_1_SetVal();
		  FLAG_MSG_ERR = 0;
	  }
	  else if (FLAG_MSG_ERR == 0) {
		  cnt_ok += 1;
		  LED_STATUS_1_ClrVal();
		  LED_STATUS_2_ClrVal();
	  }*/
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
