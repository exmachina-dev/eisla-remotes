/*
 * display.cpp
 *
 *  Created on: 2016-06-10
 *      Author: Adrian
 */

#include "display.h"
#include "LCD.h"
#include "WAIT1.h"


#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

sub_menu back = init_sub_menu((char *)"Back ",1, back_fct);

sub_menu vel_velocity = init_sub_menu((char *)"Velocity    ",1,velocity_fct);
sub_menu vel_acc = 		init_sub_menu((char *)"Acceleration",1,acceleration_fct);
sub_menu vel_dec = 		init_sub_menu((char *)"Deceleration",1,deceleration_fct);
sub_menu vel_cue = 		init_sub_menu((char *)"Cue         ",0, void_function);

sub_menu menu_velocity[] = {vel_velocity, vel_acc, vel_dec, vel_cue, back};

sub_menu pos_velocity = init_sub_menu((char *)"Velocity",1,pos_velocity_fct);
sub_menu pos_acc = 		init_sub_menu((char *)"Acceleration",1,pos_acceleration_fct);
sub_menu pos_dec = 		init_sub_menu((char *)"Deceleration",1,pos_deceleration_fct);
sub_menu pos_cue = 		init_sub_menu((char *)"Cue",0, void_function);

sub_menu menu_position[] = {pos_velocity, pos_acc, pos_dec, pos_cue, back};

sub_menu tor_torque = init_sub_menu((char *)"Velocity",1,torque_fct);
sub_menu tor_torque_rise = init_sub_menu((char *)"Acceleration",1,torque_rise_fct);
sub_menu tor_torque_fall = init_sub_menu((char *)"Deceleration",1,torque_fall_fct);
sub_menu tor_cue = init_sub_menu((char *)"cue",0, void_function);

sub_menu menu_torque[] = {tor_torque, tor_torque_rise, tor_torque_fall, tor_cue, back};

menu velocity = init_menu((char *)"Velocity      ", menu_velocity);
menu position = init_menu((char *)"Position      ", menu_velocity);
menu torque = 	init_menu((char *)"Torque        ", menu_velocity);
menu setting = 	init_menu((char *)"Setting       ", menu_velocity);

menu menu_array[] = {velocity, position, torque, setting};
int menu_array_size = 4;

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

menu menu_init(){
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

  print_sub_menu(0, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(1, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(2, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(3, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(4, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(3, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(2, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(1, 5, menu_velocity);
  WAIT1_Waitms(500);
  print_sub_menu(0, 5, menu_velocity);

}

void velocity_fct(){
	LCD_Clear();
	LCD_Write_Block("Acc", 0, 0);
	LCD_Write_Block("Dec", 0, 8);
	LCD_Write_Block("Vel Act", 2, 0);
	LCD_Write_Block("Vel", 2, 8);
	LCD_Write_Block("|",0,7);
	LCD_Write_Block("|",1,7);
	LCD_Write_Block("|",2,7);
	LCD_Write_Block("|",3,7);
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




