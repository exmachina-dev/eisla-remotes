#include <stdio.h>
#include <stdio.h>
#include "LCD.h"


#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sub_menu2{
  char *name;
  bool select;
  bool item;
  void (*function)();
}sub_menu2;

typedef struct sub_menu{
  char *name;
  bool select;
  bool item;
  void (*function)();
  sub_menu2 *sub;
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
}menu;

typedef struct menu_list{
	char *name;
	menu *array;
	int size;
}menu_list;

menu init_menu(char *, const sub_menu_list);
sub_menu init_sub_menu(char *, bool, void (*)());
menu_list init_menu_list(menu [], int, char*);
sub_menu_list init_sub_menu_list(sub_menu [], int, char*);
void print_menu(int , menu_list);
void print_sub_menu(int ,  sub_menu_list);
int menu_select(int, menu_list);
int sub_menu_select(int , sub_menu []);
int menu_back(menu_list);
int refresh_menu(int, menu_list);
void void_function(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_MENU_H_ */

