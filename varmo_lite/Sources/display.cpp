/*
0 * display.cpp
 *
 *  Created on: 2016-06-10
 *      Author: Adrian
 */

#include "display.h"


#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_SETTING = 0;

sub_menu2 back_sub_menu = init_sub_menu2((char *)"Back", 1, back_fct);

sub_menu2 vel_play_cue = init_sub_menu2((char *)"Play Cue       ", 1, vel_play_cue_fct);
sub_menu2 vel_rec_cue = init_sub_menu2((char *)"Record Cue     ", 1, vel_rec_cue_fct);
sub_menu2 vel_mod_cue = init_sub_menu2((char *)"Modify Cue     ", 1, vel_mod_cue_fct);
sub_menu2 vel_del_cue = init_sub_menu2((char *)"Delete Cue     ", 1, vel_del_cue_fct);

sub_menu2 sub_menu_velocity_cue[]= {vel_play_cue, vel_rec_cue, vel_mod_cue, vel_del_cue, back_sub_menu};
sub_menu2_list menu_velocity_cue = init_sub_menu2_list(sub_menu_velocity_cue, sizeof(sub_menu_velocity_cue)/sizeof(sub_menu_velocity_cue[0]), (char*)"Cue Menu     ");

sub_menu2 pos_play_cue = init_sub_menu2((char *)"Play Cue       ", 1, pos_play_cue_fct);
sub_menu2 pos_rec_cue = init_sub_menu2((char *)"Record Cue     ", 1, pos_rec_cue_fct);
sub_menu2 pos_mod_cue = init_sub_menu2((char *)"Modify Cue     ", 1, pos_mod_cue_fct);
sub_menu2 pos_del_cue = init_sub_menu2((char *)"Delete Cue     ", 1, pos_del_cue_fct);

sub_menu2 sub_menu_pos_cue[]= {pos_play_cue, pos_rec_cue, pos_mod_cue, pos_del_cue, back_sub_menu};
sub_menu2_list menu_pos_cue = init_sub_menu2_list(sub_menu_pos_cue, sizeof(sub_menu_pos_cue)/sizeof(sub_menu_pos_cue[0]), (char*)"Cue Menu     ");


sub_menu back_menu = init_sub_menu((char *)"Back",1,{0}, back_fct);

sub_menu vel_velocity = init_sub_menu((char *)"Velocity       ",1,{0}, velocity_fct);
sub_menu vel_acc = 		init_sub_menu((char *)"Acceleration   ",1,{0}, acceleration_fct);
sub_menu vel_dec = 		init_sub_menu((char *)"Deceleration   ",1,{0}, deceleration_fct);
sub_menu vel_cue = 		init_sub_menu((char *)"Cue            ",0, menu_velocity_cue, void_function);

sub_menu sub_menu_velocity[] = {vel_velocity, vel_acc, vel_dec, vel_cue, back_menu};
sub_menu_list menu_velocity = init_sub_menu_list(sub_menu_velocity, sizeof(sub_menu_velocity)/sizeof(sub_menu_velocity[0]), (char*)"Velocity Menu");

sub_menu pos_position = init_sub_menu((char *)"Position       ", 1, {0}, pos_position_fct);
sub_menu pos_velocity = init_sub_menu((char *)"Velocity       ", 1, {0}, pos_velocity_fct);
sub_menu pos_acc = 		init_sub_menu((char *)"Acceleration   ", 1, {0}, pos_acceleration_fct);
sub_menu pos_dec = 		init_sub_menu((char *)"Deceleration   ", 1, {0}, pos_deceleration_fct);
sub_menu pos_cue = 		init_sub_menu((char *)"Cue            ", 0, menu_pos_cue, void_function);
sub_menu pos_set_home = init_sub_menu((char *)"Set Home       ", 1, {0}, pos_set_home_fct);

sub_menu sub_menu_position[] = {pos_position, pos_velocity, pos_acc, pos_dec, pos_cue, pos_set_home,back_menu};
sub_menu_list menu_position = init_sub_menu_list(sub_menu_position, sizeof(sub_menu_position)/sizeof(sub_menu_position[0]), (char*)"Position Menu");

sub_menu tor_torque = 		init_sub_menu((char *)"Torque         ",1,{0}, torque_fct);
sub_menu tor_torque_rise = 	init_sub_menu((char *)"Torque Rise    ",1,{0}, torque_rise_fct);
sub_menu tor_torque_fall = 	init_sub_menu((char *)"Torque Fall    ",1,{0}, torque_fall_fct);

sub_menu sub_menu_torque[] = {tor_torque, tor_torque_rise, tor_torque_fall, back_menu};
sub_menu_list menu_torque = init_sub_menu_list(sub_menu_torque, sizeof(sub_menu_torque)/sizeof(sub_menu_torque[0]), (char*)"Torque Menu  ");

sub_menu setting_baud_rate = 	init_sub_menu((char *)"Baud Rate      ",1,{0}, select_baud_rate_fct);
sub_menu setting_update_val = 	init_sub_menu((char *)"Update Value   ",1,{0}, select_update_menu_fct);

sub_menu sub_menu_setting[] = {setting_baud_rate, setting_update_val, back_menu};
sub_menu_list menu_setting = init_sub_menu_list(sub_menu_setting, sizeof(sub_menu_setting)/sizeof(sub_menu_setting[0]), (char*)"Settings Menu");


menu velocity = init_menu((char *)"Velocity      ", menu_velocity,1);
menu position = init_menu((char *)"Position      ", menu_position,1);
menu torque = 	init_menu((char *)"Torque        ", menu_torque,1);
menu setting = 	init_menu((char *)"Settings       ", menu_setting,1);

menu menu_array[] = {velocity, position, torque, setting};

menu_list root_menu= init_menu_list (menu_array, sizeof(menu_array)/sizeof(menu_array[0]), (char*)"Root Menu    ");

int vspfunc(char *format, ...)
{
   va_list aptr;
   int ret;
   va_start(aptr, format);
   ret = vsprintf(buffer, format, aptr);
   va_end(aptr);
   return(ret);
}

void print_float_at(float f, int res,bool absolute, int y, int x){
    int int_part = int(f);
    float remainder = (f - (float)int_part);
	if(absolute == 1){
		f = fabs(f);
		LCD_Write_At(' ', y, x);
		x += 1;
	}
	else if (f<0){
		f = fabs(f);
		LCD_Write_At('-',y,x);
		x += 1;
	}
	else if (f > 0){
		LCD_Write_At('+',y,x);
		x+= 1;
	}
	else if(f == 0){
		LCD_Write_At(' ', y, x);
		x += 1;
	}


    if (res == 2){
    	int digits = (int) round(remainder * pow(10,res));
    	vspfunc((char*)"%4d.%02d", abs(int_part), digits);
    }
    else if(res == 1){
    	vspfunc((char*)"%5d", abs(int_part));
    }
    else{
    	vspfunc((char*)"%4d", abs(int_part));
    }
    LCD_Write_Block(buffer, y, x);
}

void print_int_at(int value,bool absolute, int y, int x){
	if (absolute == 1){
		value = abs(value);
	}
	else if (value<0){
		value = abs(value);
		LCD_Write_At('-',y,x);
		x += 1;
	}
	else if (value > 0){
		LCD_Write_At('+',y,x);
		x += 1;
	}
	else if(value == 0){
		x += 1;
	}
	vspfunc((char*)"%4d", value);
	LCD_Write_Block(buffer, y, x);
}

void print_cue_array(uint8_t pointer, uint8_t array[50], uint8_t length){
	uint8_t temp = pointer;
	uint8_t max = 2;
	uint8_t min = 2;
	uint8_t cursor = 1;
	if (length > 3){
		if(temp == 2){
			LCD_Write_Block((char*)"     ",1,0);
			min = 1;
			cursor = 4;
		}
		else if (temp == 1){
			LCD_Write_Block((char*)"      ",1,0);
			min = 0;
			cursor = 7;
		}
		else if (temp == length){
			LCD_Write_Block((char*)"     ",1,10);
			max = 0;
		}
		else if (temp == length -1){
			LCD_Write_Block((char*)"   ",1,13);
			max = 1;
		}
	}
	else if (length == 3){
		min = temp - 1;
		max = 3- temp;
		cursor = 7 -(temp -1) *3;
		LCD_Write_Block((char*)"      ",1,0);
		LCD_Write_Block((char*)"       ",1,9);
	}
	else if (length == 2){
		cursor = 7 -(temp -1) *3;
		min = temp -1;
		max = 2 - temp;
		LCD_Write_Block((char*)"      ",1,0);
		LCD_Write_Block((char*)"     ",1,9);
	}
	else if(length == 1){
		cursor = 7;
		min = 0;
		max = 0;
		LCD_Write_Block((char*)"     ",1,0);
		LCD_Write_Block((char*)"    ",1,9);
	}
	temp -= 1;
	for(uint8_t i = temp-min; i <= temp+ max; i++){
		vspfunc((char*)"%02d", array[i]);
		LCD_Write_Block(buffer, 1, cursor);
		cursor += 3;
	}

	if((temp + 3) < length){
		LCD_Write_At(arrow_right, 1, 15);
	}
	if ((temp - 2)>0){
		LCD_Write_At(arrow_left, 1, 0);
	}
	LCD_Write_At(vertical_bar,1, 6);
	LCD_Write_At(vertical_bar,1, 9);
}

void print_all_cue(uint8_t pointer, uint8_t length){
	uint8_t temp = pointer;
	uint8_t max = 2;
	uint8_t min = 2;
	uint8_t cursor = 1;
	if(temp == 2){
		LCD_Write_Block((char*)"     ",1,0);
		min = 1;
		cursor = 4;
	}
	else if (temp == 1){
		LCD_Write_Block((char*)"      ",1,0);
		min = 0;
		cursor = 7;
	}
	else if (temp == length){
		LCD_Write_Block((char*)"     ",1,10);
		max = 0;
	}
	else if (temp == length -1){
		LCD_Write_Block((char*)"   ",1,13);
		max = 1;
	}
	for(uint8_t i = temp-min; i <= temp+ max; i++){
		vspfunc((char*)"%02d", i);
		LCD_Write_Block(buffer, 1, cursor);
		cursor += 3;
	}

	if((temp + 2) < length){
		LCD_Write_At(arrow_right, 1, 15);
	}
	if ((temp - 2)>0){
		LCD_Write_At(arrow_left, 1, 0);
	}
	LCD_Write_At(vertical_bar,1, 6);
	LCD_Write_At(vertical_bar,1, 9);
}
/*
void led_init(int counter){
	if ((counter%4) == 0){
		LED_STATUS_1_SetVal();
		LED_STATUS_2_ClrVal();
		LED_STATUS_3_ClrVal();
		LED_STATUS_4_ClrVal();
	}
	else if ((counter%4) == 1){
		LED_STATUS_1_ClrVal();
		LED_STATUS_2_SetVal();
		LED_STATUS_3_ClrVal();
		LED_STATUS_4_ClrVal();
	}
	else if ((counter%4) == 2){
		LED_STATUS_1_ClrVal();
		LED_STATUS_2_ClrVal();
		LED_STATUS_3_SetVal();
		LED_STATUS_4_ClrVal();
	}
	else if ((counter%4) == 3){
		LED_STATUS_1_ClrVal();
		LED_STATUS_2_ClrVal();
		LED_STATUS_3_ClrVal();
		LED_STATUS_4_SetVal();
	}
}*/

void load_char(){
  uint8_t row[8] = {
		  0b00100,
		  0b01110,
		  0b10101,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00000};
  load_custom_char(arrow_up, row);
  uint8_t row_2[8] = {
		  0b00000,
		  0b00000,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b10101,
		  0b01110,
		  0b00100};
  load_custom_char(arrow_down, row_2);

  uint8_t row_3[8] = {
		  0b00000,
		  0b00001,
		  0b00001,
		  0b00101,
		  0b01001,
		  0b11111,
		  0b01000,
		  0b00100
  };
  load_custom_char(arrow_back, row_3);

  uint8_t row_4[8] = {
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b00100
  };
  load_custom_char(vertical_bar, row_4);

  uint8_t row_5[8] = {
		  0b00000,
		  0b01110,
		  0b11101,
		  0b11001,
		  0b11011,
		  0b11111,
		  0b01110,
		  0b00000
  };
  load_custom_char(DIR_left, row_5);
  uint8_t row_6[8] = {
		  0b00000,
		  0b01110,
		  0b10111,
		  0b10011,
		  0b11011,
		  0b11111,
		  0b01110,
		  0b00000
  };
  load_custom_char(DIR_right, row_6);

  uint8_t row_7[8] = {
		  0b00000,
		  0b01110,
		  0b10101,
		  0b10101,
		  0b10001,
		  0b10001,
		  0b01110,
		  0b00000
  };
  load_custom_char(DIR_off , row_7);

  uint8_t row_8[8] = {
		  0b00000,
		  0b00100,
		  0b01110,
		  0b10101,
		  0b10001,
		  0b10001,
		  0b01110,
		  0b00000
  };
  load_custom_char(drive_enable , row_8);

 /* uint8_t row_9[8] = {
		  0b00000,
		  0b00000,
		  0b01110,
		  0b10011,
		  0b10101,
		  0b11001,
		  0b01110,
		  0b00000
  };
  load_custom_char(not_drive_enable , row_9);*/
}

menu menu_init(){
	load_char();
	refresh(0);
}

int refresh(int pointer){
	pointer = refresh_menu(pointer, root_menu);
	return pointer;
}

int select(int pointer){
	pointer = menu_select(pointer, root_menu);

	return pointer;
}

int back(int pointer){
	FLAG_MENU = 1;
	FLAG_SETTING = 0;
	FLAG_CUE_MODE = 0;
	pointer = menu_back(root_menu);
	return pointer;
}

void controle_mode_display(int mode){
	  if (CONTROL_MODE == 1){
		  LCD_Write_At('T',0,13);
	  }
	  else if (CONTROL_MODE == 2){
		  LCD_Write_At('V',0,13);
	  }
	  else if (CONTROL_MODE == 3){
		  LCD_Write_At('P',0,13);
	  }
}


void control_mode_fct(){
	if (root_menu.array[0].menu_selected == 1){
		Send_Control_Mode(vel.control_mode);
	}
	else if (root_menu.array[1].menu_selected  == 1){
		Send_Control_Mode(pos.control_mode);
	}
	else if(root_menu.array[2].menu_selected  == 1){
		Send_Control_Mode(tor.control_mode);
	}
}

void update_icon_dir(bool DIR1, bool DIR2){
	if (DIR1 == 0 && DIR2 == 1){
		LCD_Write_At(DIR_right, 0, 14);
	}
	else if (DIR1 == 1 && DIR2 == 0){
		LCD_Write_At(DIR_left, 0, 14);
	}
	else if (DIR1 == 0 && DIR2 == 0){
		LCD_Write_At(DIR_off, 0, 14);
	}
}

void update_icon_drive_enable(void){
	if (drive_enable_st == 1){
		LCD_Write_At(drive_enable, 0, 15);
	}
	else if (drive_enable_st == 0){
		LCD_Write_At(not_drive_enable, 0, 15);
	}
}

void select_setting(int flag){
	switch(flag){
		case Baud_rate_setting:
			FLAG_SETTING_SELECTED = 1;
			counter_2s = 0;
			select_baud_rate(encoder - 1);
			break;
		case Update_setting:
			FLAG_SETTING_SELECTED = 1;
			counter_2s = 0;
			FLAG_UPDATE_SETTING = encoder -1;
			break;
	}
}

void refresh_fct(int flag){
	switch (flag){
		case Velocity_selected:
			velocity_fct();
			break;
		case Velocity_acc_selected:
			acceleration_fct();
			break;
		case Velocity_dec_selected:
			deceleration_fct();
			break;
		case Vel_play_cue:
			vel_play_cue_fct();
			break;
		case Vel_Rec_cue:
			vel_rec_cue_fct();
			break;
		case Vel_Mod_cue:
			vel_mod_cue_fct();
			break;
		case Vel_Del_cue:
			vel_del_cue_fct();
			break;
		case Position_selected:
			pos_position_fct();
			break;
		case Position_vel_selected:
			pos_velocity_fct();
			break;
		case Position_acc_selected:
			pos_acceleration_fct();
			break;
		case Position_dec_selected:
			pos_deceleration_fct();
			break;
		case Position_set_home:
			pos_set_home_fct();
			break;
		case Pos_play_cue:
			pos_play_cue_fct();
			break;
		case Pos_Rec_cue:
			pos_rec_cue_fct();
			break;
		case Pos_Mod_cue:
			pos_mod_cue_fct();
			break;
		case Pos_Del_cue:
			pos_del_cue_fct();
			break;
		case Torque_selected:
			torque_fct();
			break;
		case Torque_rise_selected:
			torque_rise_fct();
			break;
		case Torque_fall_selected:
			torque_fall_fct();
			break;
		case Baud_rate_setting:
			select_baud_rate_fct();
			break;
		case Update_setting :
			select_update_menu_fct();
			break;
	}
}

void velocity_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Velocity_selected;

		LCD_Write_Block((char*)"Acc", 0, 0);
		LCD_Write_Block((char*)"Dec", 0, 8);
		LCD_Write_Block((char*)"Vel Act", 2, 0);
		LCD_Write_Block((char*)"Vel", 2, 8);
		LCD_Write_At(vertical_bar,0,7);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		LCD_Write_At(vertical_bar,3,7);

		print_int_at(vel.acceleration, 1, 1,0);
		print_int_at(vel.deceleration, 1,1,8);
		print_float_at(vel.velocity, 0,0,3,0);

		vel.velocity_ref = convert(vel.velocity_ref,-9999, 9999);

		encoder = abs(vel.velocity_ref);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else{
			print_float_at(encoder,0,1,3,8);
		}
	}
	else if (FLAG_UPDATE_VALUE == 1){
		vel.velocity_ref = convert(vel.velocity_ref, -9999, 9999);

		encoder = abs(vel.velocity_ref);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else{
			print_float_at(encoder,0,1,3,8);
		}
	}
	else {
		print_float_at(vel.velocity, 0,0,3,0);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0 && FLAG_SENS == 0){
				encoder = 0;
			}
			encoder = convert(abs(encoder), 0, 9999);
			if (encoder < 0){
				encoder *= -1;
			}

  			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0 && FLAG_SENS == 0){
				encoder = 0;
			}
			encoder = convert(abs(encoder), 0, 9999);
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else{
			print_float_at(encoder,0,1,3,8);
		}
	}

}

void acceleration_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Velocity_acc_selected;
		LCD_Write_Block((char*)"Acc Act",1,0);
		print_float_at(vel.acceleration,0,1,2, 0);
		LCD_Write_Block((char*)"Acc",1,8);
		encoder = convert(vel.acceleration, 0, 9999);

		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		if (encoder == 0){
			LCD_Write_Block((char*)"Acc must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(vel.acceleration,0,1,2, 0);
		if (encoder == 0){
			LCD_Write_Block((char*)"Acc must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void deceleration_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);
		menu_indicator = Velocity_dec_selected;
		LCD_Write_Block((char*)"Dec Act",1,0);
		print_float_at(vel.deceleration,0,1,2, 0);
		LCD_Write_Block((char*)"Dec",1,8);
		encoder = convert(vel.deceleration, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		if (encoder == 0){
			LCD_Write_Block((char*)"Dec must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(vel.deceleration,0,1,2, 0);
		if (encoder == 0){
			LCD_Write_Block((char*)"Dec must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void back_fct(){
	encoder = menu_back(root_menu);
	back_menu.select = 0;
}

void pos_position_fct(){
	if (FLAG_MENU == 1 && pos.velocity_ref == 0){
		menu_indicator = Position_selected;
		FLAG_SHORT_CUT = 1;
	}
	else if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		menu_indicator = Position_selected;

		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		LCD_Write_Block((char*)"Vel Act", 0, 0);
		print_float_at(pos.velocity,0, 0, 1,0);
		LCD_Write_Block((char*)"Vel", 0, 8);
		print_float_at(pos.velocity_ref, 0, 0,1,8);
		LCD_Write_Block((char*)"Pos Act", 2, 0);
		print_float_at(pos.position, 1, 1,3,0);
		LCD_Write_Block((char*)"Pos", 2, 8);
		LCD_Write_At(vertical_bar,0,7);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		LCD_Write_At(vertical_bar,3,7);

		pos.position_ref = convert(pos.position_ref, -99999, 99999);
		encoder = abs(pos.position_ref);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,1,0,3,9);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,1,0,3,8);
		}
		else{
			print_float_at(encoder,1,1,3,8);
		}
	}
	else {
		print_float_at(pos.velocity,0, 0, 1,0);
		print_float_at(pos.position, 1, 1,3,0);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0){
				encoder = 0;
			}
			encoder = convert(abs(encoder), 0, 99999);
			if (encoder < 0 && FLAG_SENS_2 == 0 ){
				encoder *= -1;
			}

			print_float_at(encoder,1,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			encoder = convert(abs(encoder), 0, 99999);
			if (encoder > 0 && FLAG_SENS_2 == 0 ){
				encoder = 0;
			}
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,1,0,3,8);
		}
		else{
			print_float_at(encoder,1,1,3,8);
		}
	}
}

void pos_velocity_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Position_vel_selected;
		LCD_Write_Block((char*)"Vel Act",1,0);
		print_float_at(pos.velocity_ref,0,1,2, 0);
		LCD_Write_Block((char*)"Vel",1,8);

		encoder = convert(pos.velocity_ref, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(pos.velocity_ref,0,1,2, 0);
	}
}

void pos_acceleration_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Position_acc_selected;
		LCD_Write_Block((char*)"Acc Act",1,0);
		print_float_at(pos.acceleration,0,1,2, 0);
		LCD_Write_Block((char*)"Acc",1,8);
		encoder = convert(pos.acceleration, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		if (encoder == 0){
			LCD_Write_Block((char*)"Acc must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(pos.acceleration,0,1,2, 0);
		if (encoder == 0){
			LCD_Write_Block((char*)"Acc must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void pos_deceleration_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Position_dec_selected;
		LCD_Write_Block((char*)"Dec Act",1,0);
		print_float_at(pos.deceleration,0,1,2, 0);
		LCD_Write_Block((char*)"Dec",1,8);
		encoder = convert(pos.deceleration, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);

		if (encoder == 0){
			LCD_Write_Block((char*)"Dec must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(pos.deceleration,0,1,2, 0);

		if (encoder == 0){
			LCD_Write_Block((char*)"Dec must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void pos_set_home_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Position_set_home;
		LCD_Write_Block((char*)"Set Home",1,0);
	}
	else if (FLAG_SET_HOME == 1){
		LCD_Write_Block((char*)"Position settle",2,0);
	}
	else {
		LCD_Write_Block((char*)"               ",2,0);
	}

}

void torque_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;

		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Torque_selected;
		LCD_Write_Block((char*)"Tq R",0, 0);
		print_float_at(tor.torque_rise, 0, 0,1,0);
		LCD_Write_Block((char*)"Tq F", 0, 8);
		print_float_at(tor.torque_fall, 0, 0,1,8);
		LCD_Write_Block((char*)"Tq Act", 2, 0);
		print_float_at(tor.torque, 0, 0,3,0);
		LCD_Write_Block((char*)"Torque", 2, 8);

		LCD_Write_At(vertical_bar,0,7);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		LCD_Write_At(vertical_bar,3,7);

		tor.torque_ref = convert(tor.torque_ref, -9999, 9999);
		encoder = abs(tor.torque_ref);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else{
			print_float_at(encoder,0,1,3,8);
		}
	}
	else {
		print_float_at(tor.torque, 0, 0,3,0);
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			if (encoder < 0 && FLAG_SENS_2 == 0 ){
				encoder = 0;
			}
			encoder = convert(abs(encoder), 0, 9999);
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			if (encoder > 0 && FLAG_SENS_2 == 0 ){
				encoder = 0;
			}
			encoder = convert(abs(encoder), 0, 9999);
			if (encoder > 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else{
			print_float_at(encoder,0,1,3,8);
		}
	}
}

void torque_rise_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Torque_rise_selected;
		LCD_Write_Block((char*)"Tq R",1,0);
		print_float_at(tor.torque_rise,0, 1, 2,0);
		LCD_Write_Block((char*)"Tq R",1,8);
		encoder = convert(tor.torque_rise, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		if (encoder == 0){
			LCD_Write_Block((char*)"Tq R must be set",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(tor.torque_rise,0,1,2, 0);
		if (encoder == 0){
			LCD_Write_Block((char*)"Tq R must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void torque_fall_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Torque_fall_selected;
		LCD_Write_Block((char*)"Tq F",1,0);
		print_float_at(tor.torque_fall,0,1,2, 0);
		LCD_Write_Block((char*)"Tq F",1,8);
		encoder = convert(tor.torque_fall, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(vertical_bar,1,7);
		LCD_Write_At(vertical_bar,2,7);
		if (encoder == 0){
			LCD_Write_Block((char*)"Tq F must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(tor.torque_fall,0,1,2, 0);
		if (encoder == 0){
			LCD_Write_Block((char*)"Tq F must be set ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}
	}
}

void pos_play_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;
		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		encoder = 1;
		menu_indicator = Pos_play_cue;
		LCD_Write_Block((char*)"Play cue",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

		if (cue_saved_size == 0){
			//No cue saved
			LCD_Write_Block((char*)"No cue saved", 2, 0);
		}
		else{
			if (encoder < 1){
				encoder == 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			print_cue_array(encoder, cue_saved, cue_saved_size);
			parameters = get_cue_values(CONTROL_MODE, encoder -1);
			if(parameters.data == 0){
				LCD_Write_Block((char*)"Slot Free       ",2,0);
			}
			else if (parameters.data == 1){
				LCD_Write_Block((char*)"Pos : ",2,0);
				LCD_Write_Block((char*)"Vel : ",2,8);
				LCD_Write_Block((char*)"                ",3,0);
				print_float_at(parameters.position,1,0, 3, 0);
				print_float_at(parameters.velocity,0,1, 3, 8);
				LCD_Write_At(vertical_bar,2,7);
				LCD_Write_At(vertical_bar,3,7);
			}
		}

	}
	else{
		if (cue_saved_size != 0){
			if (FLAG_CUE_SELECTED == 1){
				LCD_Write_Block((char*)"                ",2,0);
				LCD_Write_Block((char*)"Cue loaded      ",3,0);
			}
			else{

				if(encoder < 1){
					encoder = 1;
				}
				else if (encoder > cue_saved_size){
					encoder = cue_saved_size;
				}
				else{
					cue_parameter parameters;
					print_cue_array(encoder, cue_saved, cue_saved_size);
					parameters = get_cue_values(CONTROL_MODE, encoder -1);
						if(parameters.data == 0){
						LCD_Write_Block((char*)"Slot Free       ",2,0);
						LCD_Write_Block((char*)"                ",3,0);
					}
					else if (parameters.data == 1){
						LCD_Write_Block((char*)"Pos : ",2,0);
						LCD_Write_Block((char*)"Vel : ",2,8);
						LCD_Write_Block((char*)"                ",3,0);
						print_float_at(parameters.position,1,0, 3, 0);
						print_float_at(parameters.velocity,0,1, 3, 8);
						LCD_Write_At(vertical_bar,2,7);
						LCD_Write_At(vertical_bar,3,7);
					}
				}

			}
		}
	}
}

void pos_rec_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;
		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		//encoder = 1;
		menu_indicator = Pos_Rec_cue;
		uint8_t temp = get_next_slot_free(CONTROL_MODE);
		if (temp < 50){
			encoder = temp + 1;
		}
		else{
			encoder = 1;
		}
		LCD_Write_Block((char*)"Record cue   ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);
		print_all_cue(encoder, cue_max);
		parameters = get_cue_values(CONTROL_MODE, encoder -1);
		if(parameters.data == 0){
			LCD_Write_Block((char*)"Slot Free       ",2,0);
			LCD_Write_Block((char*)"                ",3,0);
		}
		else if (parameters.data == 1){
			LCD_Write_Block((char*)"Pos : ",2,0);
			LCD_Write_Block((char*)"Vel : ",2,8);
			LCD_Write_Block((char*)"                ",3,0);
			print_float_at(parameters.position,1,0, 3, 0);
			print_float_at(parameters.velocity,0,1, 3, 8);
			LCD_Write_At(vertical_bar,2,7);
			LCD_Write_At(vertical_bar,3,7);
		}
	}
	else{
		if (FLAG_CUE_SELECTED == 1){
			LCD_Write_Block((char*)"                ",2,0);
			LCD_Write_Block((char*)"Cue saved       ",3,0);
		}
		else{
			if(encoder < 1){
				encoder = 1;
			}
			else if (encoder > cue_max){
				encoder = cue_max;
			}
			else{
				cue_parameter parameters;
				print_all_cue(encoder, cue_max);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
					LCD_Write_Block((char*)"                ",3,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Pos : ",2,0);
					LCD_Write_Block((char*)"Vel : ",2,8);
					LCD_Write_Block((char*)"                ",3,0);
					print_float_at(parameters.position,1,0, 3, 0);
					print_float_at(parameters.velocity,0,1, 3, 8);
					LCD_Write_At(vertical_bar,2,7);
					LCD_Write_At(vertical_bar,3,7);
				}
			}

		}
	}
}

void pos_mod_cue_fct(void){
	if (FLAG_MENU == 1){
			cue_parameter parameters;
			FLAG_MENU = 0;
			FLAG_CUE_MODE = 1;
			encoder = 1;
			menu_indicator = Pos_Mod_cue;
			LCD_Write_Block((char*)"Load cue",0,0);
			LCD_Write_Block((char*)"                ",1,0);
			LCD_Write_Block((char*)"                ",2,0);
			LCD_Write_Block((char*)"                ",3,0);

			cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

			if (cue_saved_size == 0){
				//No cue saved
				LCD_Write_Block((char*)"No cue saved", 2, 0);
			}
			else{
				if (encoder < 1){
					encoder == 1;
				}
				else if (encoder > cue_saved_size){
					encoder = cue_saved_size;
				}
				print_cue_array(encoder, cue_saved, cue_saved_size);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
					LCD_Write_Block((char*)"                ",3,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Pos : ",2,0);
					LCD_Write_Block((char*)"Vel : ",2,8);
					LCD_Write_Block((char*)"                ",3,0);
					print_float_at(parameters.position,1,0, 3, 0);
					print_float_at(parameters.velocity,0,1, 3, 8);
					LCD_Write_At(vertical_bar,2,7);
					LCD_Write_At(vertical_bar,3,7);
				}
			}

		}
		else{
			if (cue_saved_size != 0){
				if (FLAG_CUE_SELECTED == 1){
					LCD_Write_Block((char*)"                ",2,0);
					LCD_Write_Block((char*)"Cue loaded      ",3,0);
				}
				else{
					if(encoder < 1){
						encoder = 1;
					}
					else if (encoder > cue_saved_size){
						encoder = cue_saved_size;
					}
					else{
						cue_parameter parameters;
						print_cue_array(encoder, cue_saved, cue_saved_size);
						parameters = get_cue_values(CONTROL_MODE, encoder -1);
						if(parameters.data == 0){
							LCD_Write_Block((char*)"Slot Free       ",2,0);
							LCD_Write_Block((char*)"                ",3,0);
						}
						else if (parameters.data == 1){
							LCD_Write_Block((char*)"Pos : ",2,0);
							LCD_Write_Block((char*)"Vel : ",2,8);
							LCD_Write_Block((char*)"                ",3,0);
							print_float_at(parameters.position,1,0, 3, 0);
							print_float_at(parameters.velocity,0,1, 3, 8);
							LCD_Write_At(vertical_bar,2,7);
							LCD_Write_At(vertical_bar,3,7);
						}
					}
				}
			}
		}
}

void pos_del_cue_fct(void){
	if (FLAG_MENU == 1){
			cue_parameter parameters;
			FLAG_MENU = 0;
			FLAG_CUE_MODE = 1;
			encoder = 1;
			menu_indicator = Pos_Del_cue;
			LCD_Write_Block((char*)"Delete cue",0,0);
			LCD_Write_Block((char*)"                ",1,0);
			LCD_Write_Block((char*)"                ",2,0);
			LCD_Write_Block((char*)"                ",3,0);

			cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

			if (cue_saved_size == 0){
				//No cue saved
				LCD_Write_Block((char*)"No cue saved    ", 2, 0);
			}
			else{
				if (encoder < 1){
					encoder == 1;
				}
				else if (encoder > cue_saved_size){
					encoder = cue_saved_size;
				}
				print_cue_array(encoder, cue_saved, cue_saved_size);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Pos : ",2,0);
					LCD_Write_Block((char*)"Vel : ",2,8);
					LCD_Write_Block((char*)"                ",3,0);
					print_float_at(parameters.position,1,0, 3, 0);
					print_float_at(parameters.velocity,1,1, 3, 8);
					LCD_Write_At(vertical_bar,2,7);
					LCD_Write_At(vertical_bar,3,7);
				}
			}
	}
	else{
		if (FLAG_CUE_SELECTED == 1){
			LCD_Write_Block((char*)"                ",2,0);
			LCD_Write_Block((char*)"Cue deleted     ",3,0);
		}
		else{
			if (cue_saved_size == 0){
				//No cue saved
				LCD_Write_Block((char*)"                ", 1, 0);
				LCD_Write_Block((char*)"No cue saved    ", 2, 0);
				LCD_Write_Block((char*)"                ", 3, 0);

			}
			else if(encoder < 1){
				encoder = 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			else{
				cue_parameter parameters;
				print_cue_array(encoder, cue_saved, cue_saved_size);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Pos : ",2,0);
					LCD_Write_Block((char*)"Vel : ",2,8);
					LCD_Write_Block((char*)"                ",3,0);
					print_float_at(parameters.position,1,0, 3, 0);
					print_float_at(parameters.velocity,1,1, 3, 9);
					LCD_Write_At(vertical_bar,2,8);
					LCD_Write_At(vertical_bar,3,8);
				}
			}
		}
	}
}

void vel_play_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;
		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		encoder = 1;
		menu_indicator = Vel_play_cue;
		LCD_Write_Block((char*)"Play cue",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

		if (cue_saved_size == 0){
			//No cue saved
			LCD_Write_Block((char*)"No cue saved", 2, 0);
		}
		else{
			if (encoder < 1){
				encoder == 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			print_cue_array(encoder, cue_saved, cue_saved_size);
			parameters = get_cue_values(CONTROL_MODE, encoder -1);
			if(parameters.data == 0){
				LCD_Write_Block((char*)"Slot Free       ",2,0);
				LCD_Write_Block((char*)"                ",3,0);
			}
			else if (parameters.data == 1){
				LCD_Write_Block((char*)"Velocity :      ",2,0);
				LCD_Write_Block((char*)"                ",3,0);
				print_float_at(parameters.velocity,2,0, 3, 0);
			}
		}

	}
	else{
		if (cue_saved_size != 0){
			if (FLAG_CUE_SELECTED == 1){
				LCD_Write_Block((char*)"                ",2,0);
				LCD_Write_Block((char*)"Cue loaded      ",3,0);
			}
			else{

				if(encoder < 1){
					encoder = 1;
				}
				else if (encoder > cue_saved_size){
					encoder = cue_saved_size;
				}
				else{
					cue_parameter parameters;
					print_cue_array(encoder, cue_saved, cue_saved_size);
					parameters = get_cue_values(CONTROL_MODE, encoder -1);
					if(parameters.data == 0){
						LCD_Write_Block((char*)"Slot Free       ",2,0);
						LCD_Write_Block((char*)"                ",3,0);
					}
					else if (parameters.data == 1){
						LCD_Write_Block((char*)"Velocity :      ",2,0);
						LCD_Write_Block((char*)"                ",3,0);
						print_float_at(parameters.velocity,2,0, 3, 0);
					}
				}

			}
		}
	}
}

void vel_rec_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;
		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		//encoder = 1;
		menu_indicator = Vel_Rec_cue;
		uint8_t temp = get_next_slot_free(CONTROL_MODE);
		if (temp < 50){
			encoder = temp + 1;
		}
		else{
			encoder = 1;
		}
		LCD_Write_Block((char*)"Record cue   ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);
		print_all_cue(encoder, cue_max);
		parameters = get_cue_values(CONTROL_MODE, encoder -1);
		if(parameters.data == 0){
			LCD_Write_Block((char*)"Slot Free       ",2,0);
			LCD_Write_Block((char*)"                ",3,0);
		}
		else if (parameters.data == 1){
			LCD_Write_Block((char*)"Velocity :      ",2,0);
			LCD_Write_Block((char*)"                ",3,0);
			print_float_at(parameters.velocity,2,0, 3, 0);
		}
	}
	else{
		if (FLAG_CUE_SELECTED == 1){
			LCD_Write_Block((char*)"                ",2,0);
			LCD_Write_Block((char*)"Cue saved       ",3,0);
		}
		else{
			if(encoder < 1){
				encoder = 1;
			}
			else if (encoder > cue_max){
				encoder = cue_max;
			}
			else{
				cue_parameter parameters;
				print_all_cue(encoder, cue_max);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
					LCD_Write_Block((char*)"                ",3,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Velocity :      ",2,0);
					LCD_Write_Block((char*)"                ",3,0);
					print_float_at(parameters.velocity,2,0, 3, 0);
				}
			}

		}
	}
}

void vel_mod_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;

		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		encoder = 1;
		menu_indicator = Vel_Mod_cue;
		LCD_Write_Block((char*)"Load cue",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

		if (cue_saved_size == 0){
			//No cue saved
			LCD_Write_Block((char*)"No cue saved", 2, 0);
		}
		else{
			if (encoder < 1){
				encoder == 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			print_cue_array(encoder, cue_saved, cue_saved_size);
			parameters = get_cue_values(CONTROL_MODE, encoder -1);
			if(parameters.data == 0){
				LCD_Write_Block((char*)"Slot Free       ",2,0);
				LCD_Write_Block((char*)"                ",3,0);
			}
			else if (parameters.data == 1){
				LCD_Write_Block((char*)"Velocity :      ",2,0);
				LCD_Write_Block((char*)"                ",3,0);
				print_float_at(parameters.velocity,2,0, 3, 0);
			}
		}

	}
	else{
		if (cue_saved_size != 0){
			if (FLAG_CUE_SELECTED == 1){
				LCD_Write_Block((char*)"                ",2,0);
				LCD_Write_Block((char*)"Cue loaded      ",3,0);
			}
			else{
				if(encoder < 1){
					encoder = 1;
				}
				else if (encoder > cue_saved_size){
					encoder = cue_saved_size;
				}
				else{
					cue_parameter parameters;
					print_cue_array(encoder, cue_saved, cue_saved_size);
					parameters = get_cue_values(CONTROL_MODE, encoder -1);
					if(parameters.data == 0){
						LCD_Write_Block((char*)"Slot Free       ",2,0);
						LCD_Write_Block((char*)"                ",3,0);
					}
					else if (parameters.data == 1){
						LCD_Write_Block((char*)"Velocity :      ",2,0);
						LCD_Write_Block((char*)"                ",3,0);
						print_float_at(parameters.velocity,2,0, 3, 0);
					}
				}
			}
		}
	}
}

void vel_del_cue_fct(void){
	if (FLAG_MENU == 1){
		cue_parameter parameters;
		FLAG_MENU = 0;
		FLAG_CUE_MODE = 1;
		encoder = 1;
		menu_indicator = Vel_Del_cue;
		LCD_Write_Block((char*)"Delete cue", 0, 0);
		LCD_Write_Block((char*)"                ", 1, 0);
		LCD_Write_Block((char*)"                ", 2, 0);
		LCD_Write_Block((char*)"                ", 3, 0);

		cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);

		if (cue_saved_size == 0){
			//No cue saved
			LCD_Write_Block((char*)"No cue saved", 2, 0);
		}
		else{
			if (encoder < 1){
				encoder == 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			print_cue_array(encoder, cue_saved, cue_saved_size);
			parameters = get_cue_values(CONTROL_MODE, encoder -1);
			if(parameters.data == 0){
				LCD_Write_Block((char*)"Slot Free       ", 2, 0);
			}
			else if (parameters.data == 1){
				LCD_Write_Block((char*)"Velocity :      ", 2, 0);
				LCD_Write_Block((char*)"                ", 3, 0);
				print_float_at(parameters.velocity, 2, 0, 3, 0);
			}
		}

	}
	else{
		if (FLAG_CUE_SELECTED == 1){
			LCD_Write_Block((char*)"                ", 2, 0);
			LCD_Write_Block((char*)"Cue deleted     ", 3, 0);
		}
		else{
			if (cue_saved_size == 0){
				//No cue saved
				LCD_Write_Block((char*)"                ", 1, 0);
				LCD_Write_Block((char*)"No cue saved    ", 2, 0);
				LCD_Write_Block((char*)"                ", 3, 0);
			}
			else if(encoder < 1){
				encoder = 1;
			}
			else if (encoder > cue_saved_size){
				encoder = cue_saved_size;
			}
			else{
				cue_parameter parameters;
				print_cue_array(encoder, cue_saved, cue_saved_size);
				parameters = get_cue_values(CONTROL_MODE, encoder -1);
				if(parameters.data == 0){
					LCD_Write_Block((char*)"Slot Free       ",2,0);
				}
				else if (parameters.data == 1){
					LCD_Write_Block((char*)"Velocity :      ", 2, 0);
					LCD_Write_Block((char*)"                ", 3, 0);
					print_float_at(parameters.velocity, 2, 0, 3, 0);
				}
			}
		}
	}
}

void select_baud_rate_fct(void){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		FLAG_SETTING = 1;
		encoder = 1;
		menu_indicator = Baud_rate_setting;
		LCD_Write_Block((char*)"                ", 1, 0);
		LCD_Write_Block((char*)"                ", 2, 0);
		LCD_Write_Block((char*)"                ", 3, 0);
		LCD_Write_Block((char*)"57600          ", 1, 1);
		LCD_Write_Block((char*)"152000         ", 2, 1);
		LCD_Write_At(arrow_right,encoder,0);
	}
	else{
		if (FLAG_SETTING_SELECTED == 1){
			LCD_Write_Block((char*)"Setting updated ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}

		if(encoder<1){
			encoder = 1;
		}
		else if(encoder > 2){
			encoder = 2;
		}
		else{
			LCD_Write_At(' ',1,0);
			LCD_Write_At(' ',2,0);
			LCD_Write_At(arrow_right, encoder, 0);
		}
	}
}
void select_update_menu_fct(void){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		FLAG_SETTING = 1;
		encoder = 1;
		menu_indicator = Update_setting;
		LCD_Write_Block((char*)"                ", 1, 0);
		LCD_Write_Block((char*)"                ", 2, 0);
		LCD_Write_Block((char*)"                ", 3, 0);
		LCD_Write_Block((char*)"Yes            ", 1, 1);
		LCD_Write_Block((char*)"No             ", 2, 1);
		LCD_Write_At(arrow_right,encoder,0);
	}
	else{
		if (FLAG_SETTING_SELECTED == 1){
			LCD_Write_Block((char*)"Setting updated ",3,0);
		}
		else{
			LCD_Write_Block((char*)"                ",3,0);
		}

		if(encoder<1){
			encoder = 1;
		}
		else if(encoder > 2){
			encoder = 2;
		}
		else{
			LCD_Write_At(' ',1,0);
			LCD_Write_At(' ',2,0);
			LCD_Write_At(arrow_right, encoder, 0);

		}
	}
}

void short_cut_position_menu(){
	FLAG_MENU = 1;

	if (menu_indicator == Position_vel_selected){
		//Disable position velocity ref
		root_menu.array[1].sub.array[1].select = 0;
		//Activate position position menu
		root_menu.array[1].sub.array[0].select = 1;
		pos_position_fct();
	}
	else if(menu_indicator == Position_selected){
		//Disable position position menu
		root_menu.array[1].sub.array[0].select = 0;
		//Activate position velocity ref
		root_menu.array[1].sub.array[1].select = 1;
		pos_velocity_fct();
	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif




