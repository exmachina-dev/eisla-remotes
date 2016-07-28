#include <stdio.h>
#include ".\menu.h"
#include "LCD.h"
#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

menu init_menu(char *name, sub_menu_list list){
	menu temp;
	temp.name = name;
	temp.sub = list;
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

menu_list init_menu_list(menu list[], int size){
	menu_list temp;
	temp.array = list;
	temp.size = size;
	return temp;
}

sub_menu_list init_sub_menu_list(sub_menu list[], int size){
	sub_menu_list temp;
	temp.array = list;
	temp.size = size;
	return temp;
}

void print_menu(int pointer, menu_list menu){
  int temp = 0;
  int line = 1;
  int size = menu.size;
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
		   LCD_Write_At(2, 3, 15);
	   }
	   else if(pointer >= (size-2)){
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(' ',3,15);

	   }
	   else{
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(2, 3, 15);
	   }
  }

}

void print_sub_menu(int pointer, sub_menu_list list){
  int temp = 0;
  int line = 1;

  int size = list.size;
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
		LCD_Write_At(3, 3,6);
		LCD_Write_Block((char*)"       ",3,7);
	}
  }

  if (size > 3){
	   if (pointer <= 1){
		   LCD_Write_At(' ',1,15);
		   LCD_Write_At(2, 3, 15);
	   }
	   else if(pointer >= (size-2)){
		   LCD_Write_At(3, 3,6);
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(' ',3,15);

	   }
	   else{
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(2, 3, 15);
	   }
  }
}

int menu_select(int pointer, menu_list menu){
	int size = menu.size;
    menu.array[pointer].menu_selected = 1;
	print_sub_menu(0, menu.array[pointer].sub);
	LCD_Write_At(menu.array[pointer].name[0], 0, 13);
	return pointer = 0;
}

int sub_menu_select(int pointer, sub_menu array[]){
	int size = sizeof(*array)/sizeof(array[0]);
	if (array[pointer].item == 1){
		array[pointer].function();
		return pointer;
	}
	else{
		array[pointer].select = 1;
		return pointer = 0;
	}
}

int menu_back(menu_list menu){
	int pointer = 0;
	int size = menu.size;
	//LCD_Write_At(' ', 0, 13);
	for (int i =0; i < size; i++){
		if (menu.array[i].menu_selected == 1){
			pointer = i;
		}
	}
	menu.array[pointer].menu_selected = 0;
	LCD_Clear();
	print_menu(pointer, menu);
	return pointer;
}

int refresh_menu(int pointer, menu_list menu){
	int i = 0;
	bool sub_menu_selected = false;
	//int size = sizeof(array)/sizeof(array[0]);
	int size = menu.size;
	if (pointer >= size){
		pointer = size -1;
	}
	else if (pointer <= 0){
		pointer = 0;
	}

	while(i < size){
		if (menu.array[i].menu_selected == 1){
			sub_menu_selected = true;
			 break;
		}
		i++;
	}
	if (sub_menu_selected == true){
		size = sizeof(menu.array->sub);
		print_sub_menu(pointer, menu.array[i].sub);
		sub_menu_selected = false;
	}
	else{
		print_menu(pointer, menu);
	}
	return pointer;
}

void void_function(){}


#ifdef __cplusplus
}  /* extern "C" */
#endif
