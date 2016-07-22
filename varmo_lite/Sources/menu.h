#include <stdio.h>

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
  const sub_menu2 *sub;
}sub_menu;

typedef struct menu {
  char *name;
  bool menu_selected;
  const sub_menu *sub;
}menu;

menu init_menu(char *, const sub_menu []);
sub_menu init_sub_menu(char *, bool, void (*)());
void print_menu(int, int , menu []);
void print_sub_menu(int, int , const sub_menu []);
int menu_select(int , int, menu []);
int sub_menu_select(int , int , sub_menu []);
int menu_back(int, menu []);
void void_function(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_MENU_H_ */

