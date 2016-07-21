#include <stdio.h>
#include ".\menu.h"
#include "LCD.h"

#ifdef __cplusplus
extern "C" {
#endif

menu init_menu(char *name, const sub_menu array[]){
	menu temp;
	temp.name = name;
	temp.sub = array;
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

void print_menu(int pointer, int size_array, menu array[]){
  int temp = 0;
  int line = 1;
  if (pointer == 0){
	  temp = 0;
  }
  else if (pointer == (size_array-1)){
	  temp = size_array - 3;
  }
  else{
	  temp = pointer - 1;
  }

  for (int i = temp; i<temp+3; i++){
	if (i == pointer){
		LCD_Write_At(0x7E, line, 0);
		LCD_Write_Block(array[i].name, line, 1);
	}
	else{
		LCD_Write_Block(" ", line, 0);
 		LCD_Write_Block(array[i].name, line, 1);
	}
	line += 1;
  }

  if (size_array > 3){
	   if (pointer == 0){
		   LCD_Write_At(' ',1,15);
		   LCD_Write_At(2, 3, 15);
	   }
	   else if(pointer == (size_array-1)){
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(' ',3,15);
	   }
	   else{
		   LCD_Write_At(1, 1, 15);
		   LCD_Write_At(2, 3, 15);
	   }
  }

}

void print_sub_menu(int pointer, int size_array, const sub_menu array[]){
  int temp = 0;
  int line = 1;
  if (pointer == 0){
	  temp = 0;
  }
  else if (pointer == (size_array-1)){
	  temp = size_array - 3;
  }
  else{
	  temp = pointer - 1;

  }

  for (int i = temp; i<temp+3; i++){
	if (i == pointer){
		LCD_Write_At(0x7E, line, 0);
		LCD_Write_Block(array[i].name, line, 1);
	}
	else{
		LCD_Write_Block(" ", line, 0);
		LCD_Write_Block(array[i].name, line, 1);
	}
	line += 1;
	if (i == (size_array -1)){
		LCD_Write_At(3, 3,6);
		LCD_Write_Block("       ",3,7);
	}
  }

  if (size_array > 3){
	   if (pointer == 0){
		   LCD_Write_At(' ',1,15);
		   LCD_Write_At(2, 3, 15);
	   }
	   else if(pointer == (size_array-1)){
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

int menu_select(int pointer, int size_array, menu array[]){
	array[pointer].menu_select = 1;
	print_sub_menu(pointer, size_array, array[pointer].sub);
	return pointer = 0;
}

int sub_menu_select(int pointer, int size_array, sub_menu array[]){
	if (array[pointer].item == 1){
		array[pointer].function();
		return pointer;
	}
	else{
		array[pointer].select = 1;
		return pointer = 0;
	}
}

int menu_back(int size_array, menu array[]){
	int pointer = 0;
	for (int i =0; i < size_array; i++){
		if (array[i].menu_select == 1){
			pointer = i;
		}
	}
	array[pointer].menu_select = 0;
	print_menu(pointer, size_array, array);
	return pointer;
}

void void_function(){}


#ifdef __cplusplus
}  /* extern "C" */
#endif
