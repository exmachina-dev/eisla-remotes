/*
 * display.cpp
 *
 *  Created on: 2016-06-10
 *      Author: Adrian
 */

#include "display.h"


#ifdef __cplusplus
extern "C" {
#endif

sub_menu back_menu = init_sub_menu((char *)"Back",1, back_fct);

sub_menu vel_velocity = init_sub_menu((char *)"Velocity    ",1,velocity_fct);
sub_menu vel_acc = 		init_sub_menu((char *)"Acceleration",1,acceleration_fct);
sub_menu vel_dec = 		init_sub_menu((char *)"Deceleration",1,deceleration_fct);
sub_menu vel_cue = 		init_sub_menu((char *)"Cue         ",0, void_function);

sub_menu sub_menu_velocity[] = {vel_velocity, vel_acc, vel_dec, vel_cue, back_menu};
sub_menu_list menu_velocity = init_sub_menu_list(sub_menu_velocity, sizeof(sub_menu_velocity)/sizeof(sub_menu_velocity[0]), (char*)"Velocy Menu  ");

sub_menu pos_position = init_sub_menu((char *)"Postion     ",1,pos_position_fct);
sub_menu pos_velocity = init_sub_menu((char *)"Velocity    ",1,pos_velocity_fct);
sub_menu pos_acc = 		init_sub_menu((char *)"Acceleration",1,pos_acceleration_fct);
sub_menu pos_dec = 		init_sub_menu((char *)"Deceleration",1,pos_deceleration_fct);
sub_menu pos_cue = 		init_sub_menu((char *)"Cue         ",0, void_function);

sub_menu sub_menu_position[] = {pos_position, pos_velocity, pos_acc, pos_dec, pos_cue, back_menu};
sub_menu_list menu_position = init_sub_menu_list(sub_menu_position, sizeof(sub_menu_position)/sizeof(sub_menu_position[0]), (char*)"Postion Menu ");

sub_menu tor_torque = 		init_sub_menu((char *)"Torque        ",1,torque_fct);
sub_menu tor_torque_rise = 	init_sub_menu((char *)"Torque Rise   ",1,torque_rise_fct);
sub_menu tor_torque_fall = 	init_sub_menu((char *)"Torque Fall   ",1,torque_fall_fct);
sub_menu tor_cue = 			init_sub_menu((char *)"Cue           ",0, void_function);

sub_menu sub_menu_torque[] = {tor_torque, tor_torque_rise, tor_torque_fall, tor_cue, back_menu};
sub_menu_list menu_torque = init_sub_menu_list(sub_menu_torque, sizeof(sub_menu_torque)/sizeof(sub_menu_torque[0]), (char*)"Torque Menu  ");

menu velocity = init_menu((char *)"Velocity      ", menu_velocity,1);
menu position = init_menu((char *)"Position      ", menu_position,1);
menu torque = 	init_menu((char *)"Torque        ", menu_torque,1);
menu setting = 	init_menu((char *)"Setting       ", menu_velocity,0);

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


    if (res != 0){
    	int digits = (int) round(remainder * pow(10,res));
    	vspfunc((char*)"%4d.%02d", abs(int_part), digits);
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

void led_init(int counter){
	if ((counter%4) == 0){
		LED_STATUS_1_PutVal(1);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 1){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(1);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 2){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(1);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 3){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(1);
	}
}

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
  load_custom_char(1, row);
  uint8_t row_2[8] = {
		  0b00000,
		  0b00000,
		  0b00100,
		  0b00100,
		  0b00100,
		  0b10101,
		  0b01110,
		  0b00100};
  load_custom_char(2, row_2);

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
  load_custom_char(3, row_3);

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
  load_custom_char(4, row_4);

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
  load_custom_char(5, row_5);
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
  load_custom_char(6, row_6);

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
  load_custom_char(7, row_7);
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
	  else{
		  LCD_Write_At(' ',0,13);
	  }
}


void control_mode_fct(){
	if (root_menu.array[0].menu_selected == 1){
		Send_Control_Mode(vel.control_mode);
	}
	else if (root_menu.array[1].menu_selected  == 1){
		Send_Control_Mode(pos.control_mode);
	}
	else if(root_menu.array[3].menu_selected  == 1){
		Send_Control_Mode(tor.control_mode);
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
		case Torque_selected:
			torque_fct();
			break;
		case Torque_rise_selected:
			torque_rise_fct();
			break;
		case Torque_fall_selected:
			torque_fall_fct();
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
		LCD_Write_At(4,0,7);
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
		LCD_Write_At(4,3,7);

		print_int_at(vel.acceleration, 1, 1,0);
		print_int_at(vel.deceleration, 1,1,8);
		print_float_at(vel.velocity, 0,0,3,0);

		vel.velocity_ref = convert(vel.velocity_ref,vel.velocity_minimum, vel.velocity_maximum);

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
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			encoder = convert(abs(encoder), 0, vel.velocity_maximum);
			if (encoder < 0){
				encoder *= -1;
			}

			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			encoder = convert(abs(encoder), 0, abs(vel.velocity_minimum));
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(vel.acceleration,0,1,2, 0);
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(vel.deceleration,0,1,2, 0);
	}
}

void back_fct(){
	encoder = menu_back(root_menu);
	back_menu.select = 0;
}

void pos_position_fct(){
	if (FLAG_MENU == 1){
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
		print_float_at(pos.position, 0, 0,3,0);
		LCD_Write_Block((char*)"Pos", 2, 8);
		LCD_Write_At(4,0,7);
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
		LCD_Write_At(4,3,7);

		pos.position_ref = convert(pos.position_ref,pos.position_minimum, pos.position_maximum);
		encoder = abs(pos.position_ref);
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
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			encoder = convert(abs(encoder), 0, pos.position_maximum);
			if (encoder < 0){
				encoder *= -1;
			}

			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			encoder = convert(abs(encoder), 0, abs(pos.position_minimum));
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


void pos_velocity_fct(){
	if (FLAG_MENU == 1){
		FLAG_MENU = 0;
		LCD_Write_Block((char*)"             ",0,0);
		LCD_Write_Block((char*)"                ",1,0);
		LCD_Write_Block((char*)"                ",2,0);
		LCD_Write_Block((char*)"                ",3,0);

		menu_indicator = Position_vel_selected;
		LCD_Write_Block((char*)"Vel Act",1,0);
		print_float_at(pos.velocity,0,1,2, 0);
		LCD_Write_Block((char*)"Vel",1,8);
		encoder = convert(pos.velocity_ref, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(pos.acceleration,0,1,2, 0);
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(pos.deceleration,0,1,2, 0);
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

		LCD_Write_At(4,0,7);
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
		LCD_Write_At(4,3,7);

		tor.torque_ref = convert(tor.torque_ref,tor.torque_minimum, tor.torque_maximum);
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
		if (FLAG_SENS_1 == 1 && FLAG_SENS_2 == 0 ){
			encoder = convert(abs(encoder), 0, tor.torque_maximum);
			if (encoder < 0){
				encoder *= -1;
			}
			print_float_at(encoder,0,0,3,8);
		}
		else if(FLAG_SENS_1 == 0 && FLAG_SENS_2 == 1 ){
			encoder = convert(abs(encoder), 0, abs(tor.torque_minimum));
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(tor.torque_rise,0,1,2, 0);
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
		LCD_Write_At(4,1,7);
		LCD_Write_At(4,2,7);
	}
	else{
		encoder = convert(encoder, 0, 9999);
		print_float_at(encoder,0,1, 2, 8);
		print_float_at(tor.torque_fall,0,1,2, 0);
	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif




