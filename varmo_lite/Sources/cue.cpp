/*
 * cue_eeprom.cpp
 *
 *  Created on: 2016-07-01
 *      Author: Adrian
 */

#include "cue.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t cue_saved[50];
cue_parameter cue_value_saved[50];
bool FLAG_CUE_MODE = 0;
uint8_t cue_saved_size = 0;
bool FLAG_CUE_SELECTED = 0;
bool FLAG_UPDATE_CUE = 0;


void select_cue(uint8_t encoder, uint8_t flag){
	if (true){//CONTROL_MODE == 2 || CONTROL_MODE == 3){
		FLAG_CUE_SELECTED = 1;
		counter_2s = 0;
		switch(flag){
			case Vel_play_cue:
				load_cue(cue_saved[encoder-1] - 1, CONTROL_MODE);
				send_velocity_cue();
				break;
			case Vel_Rec_cue:
				write_cue(encoder -1, CONTROL_MODE);
				break;
			case Vel_Mod_cue:
				load_cue(cue_saved[encoder-1] - 1, CONTROL_MODE);
				break;
			case Vel_Del_cue:
				erase_cue(cue_saved[encoder-1] - 1, CONTROL_MODE);
				cue_saved_size = get_slot_saved(CONTROL_MODE, cue_saved);
				break;
			case Pos_play_cue:
				load_cue(cue_saved[encoder-1] - 1, 3);
				send_position_cue();
				break;
			case Pos_Rec_cue:
				write_cue(encoder -1, 3);
				break;
			case Pos_Mod_cue:
				load_cue(cue_saved[encoder-1] - 1, 3);
				break;
			case Pos_Del_cue:
				erase_cue(cue_saved[encoder-1] - 1, 3);
				cue_saved_size = get_slot_saved(3, cue_saved);
				get_cues_saved_values(3, cue_value_saved, cue_saved, cue_saved_size);
				break;
		}
	}
}



#ifdef __cplusplus
}  /* extern "C" */
#endif


