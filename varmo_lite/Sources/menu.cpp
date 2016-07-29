#include "menu.h"

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
  LCD_Write_At(menu.name[0],0,13);
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
  LCD_Write_Block(list.name, 0, 0);
  LCD_Write_At(list.name[0],0,13);
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
		if (menu.array[i].sub.array[pointer].item== 1){

			menu.array[i].sub.array[pointer].function();
		}
		else{
			menu.array[i].sub.array[pointer].select = 1;
			pointer = 0;
		}
		menu.array[i].sub.array[pointer].select = 1;
		sub_menu_selected = false;
	}
	else{
		menu.array[pointer].menu_selected = 1;
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
		for (int i = 0; i < size; i++){
			if (menu.array[pointer].sub.array[i].select == 1){
				menu.array[pointer].sub.array[i].select = 0;
				sub_menu_selected = false;
				pointer = i;
				i=size;
			}
		}
		if (sub_menu_selected == true){
			menu.array[pointer].menu_selected = 0;
		}
	}
	refresh_menu(pointer, menu);
	/*
	for (int i =0; i < size; i++){
		if (menu.array[i].menu_selected == 1){
			pointer = i;
		}
	}
	menu.array[pointer].menu_selected = 0;
	LCD_Clear();
	print_menu(pointer, menu);*/
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
		size = menu.array[i].sub.size;
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
