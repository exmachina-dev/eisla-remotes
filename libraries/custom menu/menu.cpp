#include ".\menu.h"

menu init_menu(char *name, sub_menu array[]){
	menu temp;
	temp.name = name;	
	temp.sub = array;
	return temp;
}

sub_menu init_sub_menu(char *name, bool item){
	sub_menu temp;
	temp.name = name;

	return temp;
}

sub_menu init_sub_menu(char *name, bool item, void (*function)()){
	sub_menu temp;
	temp.name = name;
	if (item == 1){
		temp.function = function;
		temp.item = 1;
	}	
	return temp;
}

void print_menu(int pointer, int size_array, menu array[]){
	int temp = 0;
  if ((pointer+3) > size_array){
  	temp = size_array-3;
  }
  else {
  	temp = pointer;
  }
  for (int i = temp; i<(temp+3) ; i++){
  	if (i == pointer){
  		//Serial.print(array[i].name);
  		//Serial.println("<-");
  	}
  	else{
	  	//Serial.println(array[i].name);	
  	}
  }
}

void print_sub_menu(int pointer, int size_array, sub_menu array[]){
	int temp = 0;
  if ((pointer+3) > size_array){
  	temp = size_array-3;
  }
  else {
  	temp = pointer;
  }
  for (int i = temp; i<(temp+3) ; i++){
  	if (i == pointer){
  		//Serial.print(array[i].name);
  		//Serial.println("<-");
  	}
  	else{
	  	//Serial.println(array[i].name);	
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
