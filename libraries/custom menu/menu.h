
struct sub_menu{
  char *name;
  bool select;
  bool item;
  void (*function)();
};

struct menu {
  char *name;
  bool menu_select = 0;
  sub_menu *sub;
  int size;/*
  float parameter_1;
  float parameter_2;
  float parameter_3;
  float parameter_4;*/
};


menu init_menu(char *, sub_menu []);
sub_menu init_sub_menu(char *, bool, void (*)());
sub_menu init_sub_menu(char *, bool);
void print_menu(int, int , menu []);
void print_sub_menu(int, int , sub_menu []);
int menu_select(int, int, menu []);
int sub_menu_select(int , int , sub_menu []);
int menu_back(int, menu []);
