#include <stdio.h>
#include <stdio.h>
#include "LCD.h"



#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_

#ifdef __cplusplus
extern "C" {
#endif

#define arrow_up 0
#define arrow_down 1

#define arrow_back 2
#define vertical_bar 3
#define DIR_left 4
#define DIR_right 5
#define DIR_off 6
#define drive_enable 7
#define not_drive_enable 0x78
#define arrow_right 0x7E
#define arrow_left 0x7F


extern bool FLAG_CONTROL_MODE;

typedef struct sub_menu2{
  char *name;
  bool select;
  bool item;
  void (*function)();
}sub_menu2;

typedef struct sub_menu2_list{
	char *name;
	sub_menu2 *array;
	int size;
}sub_menu2_list;

typedef struct sub_menu{
  char *name;
  bool select;
  bool item;
  void (*function)();
  sub_menu2_list sub;
}sub_menu;

typedef struct sub_menu_list{
	char *name;
	sub_menu *array;
	int size;
}sub_menu_list;

typedef struct menu {
  char *name;
  bool menu_selected;
  sub_menu_list sub;
  int size;
  bool control_mode;
}menu;

typedef struct menu_list{
	char *name;
	menu *array;
	int size;
}menu_list;


menu init_menu(char *, const sub_menu_list, bool);
sub_menu init_sub_menu(char *, bool, sub_menu2_list, void (*)());
sub_menu2 init_sub_menu2(char *, bool, void (*)());
menu_list init_menu_list(menu [], int, char*);
sub_menu_list init_sub_menu_list(sub_menu [], int, char*);
sub_menu2_list init_sub_menu2_list(sub_menu2 [], int, char*);
void print_menu(int , menu_list);
void print_sub_menu(int, sub_menu_list);
void print_sub_menu2(int, sub_menu2_list);
int menu_select(int, menu_list);
int sub_menu_select(int , sub_menu []);
int menu_back(menu_list);
int refresh_menu(int, menu_list);
void void_function(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_MENU_H_ */

