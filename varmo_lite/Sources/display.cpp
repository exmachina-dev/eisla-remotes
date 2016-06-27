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

void menu_init(){
  sub_menu back = init_sub_menu((char *)"back",1, back_fct);

  sub_menu vel_velocity = init_sub_menu((char *)"velocity",1,velocity_fct);
  sub_menu vel_acc = init_sub_menu((char *)"acceleration",1,acceleration_fct);
  sub_menu vel_dec = init_sub_menu((char *)"deceleration",1,deceleration_fct);
  sub_menu vel_cue = init_sub_menu((char *)"cue",0, void_function);

  sub_menu menu_velocity[] = {vel_velocity, vel_acc, vel_dec, vel_cue, back};

  sub_menu pos_velocity = init_sub_menu((char *)"velocity",1,pos_velocity_fct);
  sub_menu pos_acc = init_sub_menu((char *)"acceleration",1,pos_acceleration_fct);
  sub_menu pos_dec = init_sub_menu((char *)"deceleration",1,pos_deceleration_fct);
  sub_menu pos_cue = init_sub_menu((char *)"cue",0, void_function);

  sub_menu menu_position[] = {pos_velocity, pos_acc, pos_dec, pos_cue, back};

  sub_menu tor_torque = init_sub_menu((char *)"velocity",1,torque_fct);
  sub_menu tor_torque_rise = init_sub_menu((char *)"acceleration",1,torque_rise_fct);
  sub_menu tor_torque_fall = init_sub_menu((char *)"deceleration",1,torque_fall_fct);
  sub_menu tor_cue = init_sub_menu((char *)"cue",0, void_function);

  sub_menu menu_torque[] = {tor_torque, tor_torque_rise, tor_torque_fall, tor_cue, back};


}

void velocity_fct(){

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




