#include "menu.h"

#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_CONTROL_MODE;

menu init_menu(char *name, sub_menu_list list, bool control_mode){
	menu temp;
	temp.name = name;
	temp.sub = list;
	temp.control_mode = control_mode;
	return temp;
}

sub_menu init_sub_menu(char *name, bool item, void (*function)()){
	sub_menu temp;
	temp.name = name;
	if (item == 1){
		temp.function = function;
		temp.item = 1;
	}
	else{
		temp.function = void_function;
	}
	return temp;
}

menu_list init_menu_list(menu list[], int size, char* name){
	menu_list temp;
	temp.array = list;
	temp.size = size;
	temp.name = name;
	return temp;
}

sub_menu_list init_sub_menu_list(sub_menu list[], int size,char* name){
	sub_menu_list temp;
	temp.array = list;
	temp.size = size;
	temp.name = name;
	return temp;
}

void print_menu(int pointer, menu_list menu){
  int temp = 0;
  int line = 1;
  int size = menu.size;
  LCD_Write_Block(menu.name, 0, 0);
  if (pointer == 0){
	  temp = 0;
  }
  else if (pointer == (size-1)){
	  temp = size - 3;
  }
  else{
	  temp = pointer - 1;
  }

  for (int i = temp; i<temp+3; i++){
	if (i == pointer){
		LCD_Write_At(0x7E, line, 0);
		LCD_Write_Block(menu.array[i].name, line, 1);
	}
	else{
		LCD_Write_Block((char*)" ", line, 0);
 		LCD_Write_Block(menu.array[i].name, line, 1);
	}
	line += 1;
  }

  if (size > 3){
	   if (pointer <= 1){
		   LCD_Write_At(' ',1,15);
		   LCD_Write_At(arrow_down, 3, 15);
	   }
	   else if(pointer >= (size-2)){
		   LCD_Write_At(arrow_up, 1, 15);
		   LCD_Write_At(' ',3,15);

	   }
	   else{
		   LCD_Write_At(arrow_up, 1, 15);
		   LCD_Write_At(arrow_down, 3, 15);
	   }
  }

}

void print_sub_menu(int pointer, sub_menu_list list){
  int temp = 0;
  int line = 1;

  int size = list.size;
  LCD_Write_Block(list.name, 0, 0);

  if (pointer == 0){
	  temp = 0;
  }
  else if (pointer == (size-1)){
	  temp = size - 3;
  }
  else{
	  temp = pointer - 1;
  }

  for (int i = temp; i<temp+3; i++){
	if (i == pointer){
		LCD_Write_At(0x7E, line, 0);
		LCD_Write_Block(list.array[i].name, line, 1);
	}
	else{
		LCD_Write_Block((char*)" ", line, 0);
		LCD_Write_Block(list.array[i].name, line, 1);
	}
	line += 1;
	if (i == (size -1)){
		LCD_Write_Block((char*)" ",3,5);
		LCD_Write_At(arrow_back, 3,6);
		LCD_Write_Block((char*)"        ",3,7);
	}
  }

  if (size > 3){
	   if (pointer <= 1){
		   LCD_Write_At(' ',1,15);
		   LCD_Write_At(arrow_down, 3, 15);
	   }
	   else if(pointer >= (size-2)){
		   LCD_Write_At(arrow_back, 3,6);
		   LCD_Write_At(arrow_up, 1, 15);
		   LCD_Write_At(' ',3,15);

	   }
	   else{
		   LCD_Write_At(arrow_up, 1, 15);
		   LCD_Write_At(arrow_down, 3, 15);
	   }
  }
}

int menu_select(int pointer, menu_list menu){
	int i = 0;
	bool sub_menu_selected = false;

	int size = menu.size;


	while(i < size){
		if (menu.array[i].menu_selected == 1){
			sub_menu_selected = true;
			 break;
		}
		i++;
	}
	if (sub_menu_selected == true){

		size = menu.array[i].size;
		if (menu.array[i].sub.array[pointer].item== 1){
			//Enter on the sub menu item
			menu.array[i].sub.array[pointer].select = 1;
			menu.array[i].sub.array[pointer].function();
			if (strcmp(menu.array[i].sub.array[pointer].name,"Back") == 0){
				pointer = i;
			}
		}
		else{
			//enter on the sub menu
			menu.array[i].sub.array[pointer].select = 1;
			pointer = 0;
		}

		sub_menu_selected = false;
	}
	else{
		//Enter on a menu of the root menu
		if (pointer >= size){
			pointer = size -1;
		}
		else if (pointer <= 0){
			pointer = 0;
		}

		menu.array[pointer].menu_selected = 1;
		FLAG_CONTROL_MODE = 1;
		refresh_menu(0, menu);
		pointer = 0;
	}
	return pointer;
}

int menu_back(menu_list menu){
	int pointer = 0;
	int size = menu.size;
	bool sub_menu_selected = false;
	while(pointer < size){
		if (menu.array[pointer].menu_selected == 1){
			sub_menu_selected = true;
			break;
		}
		pointer++;
	}
	if (sub_menu_selected == true){
		size = menu.array[pointer].sub.size;
		for (int j = 0; j < size; j++){
			if (menu.array[pointer].sub.array[j].select == 1){
				menu.array[pointer].sub.array[j].select = 0;

				if (strcmp(menu.array[pointer].sub.array[j].name,"Back")== 0){
					menu.array[pointer].menu_selected = 0;
				}
				else{
					pointer = j;
					sub_menu_selected = false;
					pointer = refresh_menu(pointer, menu);
				}
				j=size;
			}
		}
		if (sub_menu_selected == true){
			menu.array[pointer].menu_selected = 0;
			pointer = refresh_menu(pointer, menu);
		}
	}


	return pointer;
}

int refresh_menu(int pointer, menu_list menu){
	int i = 0;
	bool sub_menu_selected = false;
	int size = menu.size;

	while(i < size){
		if (menu.array[i].menu_selected == 1){
			sub_menu_selected = true;
			break;
		}
		i++;
	}
	if (sub_menu_selected == true){
		size = menu.array[i].sub.size;
		if (pointer >= size){
			pointer = size -1;
		}
		else if (pointer <= 0){
			pointer = 0;
		}
		print_sub_menu(pointer, menu.array[i].sub);
		sub_menu_selected = false;
	}
	else{
		if (pointer >= size){
			pointer = size -1;
		}
		else if (pointer <= 0){
			pointer = 0;
		}
		print_menu(pointer, menu);
	}

	return pointer;
}

void void_function(){}


#ifdef __cplusplus
}  /* extern "C" */
#endif
