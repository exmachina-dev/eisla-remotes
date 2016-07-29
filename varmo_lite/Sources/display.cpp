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

sub_menu back_menu = init_sub_menu((char *)"Back ",1, back_fct);

sub_menu vel_velocity = init_sub_menu((char *)"Velocity    ",1,velocity_fct);
sub_menu vel_acc = 		init_sub_menu((char *)"Acceleration",1,acceleration_fct);
sub_menu vel_dec = 		init_sub_menu((char *)"Deceleration",1,deceleration_fct);
sub_menu vel_cue = 		init_sub_menu((char *)"Cue         ",0, void_function);

sub_menu sub_menu_velocity[] = {vel_velocity, vel_acc, vel_dec, vel_cue, back_menu};
sub_menu_list menu_velocity = init_sub_menu_list(sub_menu_velocity, sizeof(sub_menu_velocity)/sizeof(sub_menu_velocity[0]));


sub_menu pos_velocity = init_sub_menu((char *)"Postion    ",1,pos_velocity_fct);
sub_menu pos_acc = 		init_sub_menu((char *)"Acceleration",1,pos_acceleration_fct);
sub_menu pos_dec = 		init_sub_menu((char *)"Deceleration",1,pos_deceleration_fct);
sub_menu pos_cue = 		init_sub_menu((char *)"Cue         ",0, void_function);

sub_menu sub_menu_position[] = {pos_velocity, pos_acc, pos_dec, pos_cue, back_menu};
sub_menu_list menu_position = init_sub_menu_list(sub_menu_position, sizeof(sub_menu_position)/sizeof(sub_menu_position[0]));

sub_menu tor_torque = 		init_sub_menu((char *)"Torque        ",1,torque_fct);
sub_menu tor_torque_rise = 	init_sub_menu((char *)"Torque Rise   ",1,torque_rise_fct);
sub_menu tor_torque_fall = 	init_sub_menu((char *)"Torque Fall   ",1,torque_fall_fct);
sub_menu tor_cue = 			init_sub_menu((char *)"Cue           ",0, void_function);

sub_menu sub_menu_torque[] = {tor_torque, tor_torque_rise, tor_torque_fall, tor_cue, back_menu};
sub_menu_list menu_torque = init_sub_menu_list(sub_menu_torque, sizeof(sub_menu_torque)/sizeof(sub_menu_torque[0]));

menu velocity = init_menu((char *)"Velocity      ", menu_velocity);
menu position = init_menu((char *)"Position      ", menu_position);
menu torque = 	init_menu((char *)"Torque        ", menu_torque);
menu setting = 	init_menu((char *)"Setting       ", menu_velocity);
menu test = init_menu((char*)"Test", menu_velocity);

static menu menu_array[] = {velocity, position, torque, setting, test};

menu_list root_menu= init_menu_list (menu_array, sizeof(menu_array)/sizeof(menu_array[0]));

char buffer[80];

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
	if(absolute == 1){
		f = fabs(f);
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
		x += 1;
	}

    int int_part = int(f);
    float remainder = (f - (float)int_part);

    if (res != 0){
    	int digits = (int) round(remainder * pow(10,res));
    	vspfunc((char*)"%04d.%02d", int_part, digits);
    }
    else{
    	vspfunc((char*)"%04d", int_part);
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
	vspfunc((char*)"%04d", value);
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
		  0b10000,
		  0b10000,
		  0b10100,
		  0b10010,
		  0b11111,
		  0b00010,
		  0b00100
  };
  load_custom_char(3, row_3);

  uint8_t row_4[8] = {
		  0b01010,
		  0b01010,
		  0b01010,
		  0b01010,
		  0b01010,
		  0b01010,
		  0b01010,
		  0b01010
  };
  load_custom_char(4, row_4);
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

void velocity_fct(){
	FLAG_MENU = 0;
 	LCD_Clear();
	LCD_Write_Block((char*)"Acc", 0, 0);
	LCD_Write_Block((char*)"Dec", 0, 8);
	LCD_Write_Block((char*)"Vel Act", 2, 0);
	LCD_Write_Block((char*)"Vel", 2, 8);
	LCD_Write_At(4,0,7);
	LCD_Write_At(4,1,7);
	LCD_Write_At(4,2,7);
	LCD_Write_At(4,3,7);
	LCD_Write_Block((char*)"0000",1,0);
	LCD_Write_Block((char*)"0000",1,8);
	LCD_Write_Block((char*)"+0000",3,0);
	LCD_Write_Block((char*)"+0000",3,8);
}

void acceleration_fct(){

}

void deceleration_fct(){

}

void back_fct(){

}

void pos_velocity_fct(){

}

void pos_acceleration_fct(){

}

void pos_deceleration_fct(){

}

void torque_fct(){

}

void torque_rise_fct(){

}

void torque_fall_fct(){

}

#ifdef __cplusplus
}  /* extern "C" */
#endif




