#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include<string.h>

int highlighted_item;// elementul activ, a carui functionalitate se activeaza la apasarea tastei enter
int menu_items[5];//    menu_items[menu_id] == numarul de elemente din meniul cu ID-ul menu_id
int current_menu;// meniul care este afisat pe ecran in prezent

typedef struct menu_strings{
    char item[10][30];  // stringurile elementelor meniului
};
struct menu_strings menu[10];   // meniurile

void menu_up();
void menu_down();
void menu_enter();
void print_menu();
void build_menu(); // doar "umple" variabilele

#endif // MENU_H_INCLUDED
