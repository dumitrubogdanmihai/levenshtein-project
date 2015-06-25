///\file list.h
///\brief Biblioteca C pentru realizarea menu-ului si functiilor de deplasare prin acesta.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -construirea si afisarea menu-ului
* -functiile ce ofera deplasarea utilizatorului prin intermediul acestuia
*/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include<string.h>

int highlighted_item;// elementul activ, a carui functionalitate se activeaza la apasarea tastei enter
int current_menu;// meniul care este afisat pe ecran in prezent

typedef struct one_menu{
    int nr_items;
    char item[10][40];  // stringurile elementelor meniului
};
struct one_menu menu[10];   // meniurile

void menu_up();
void menu_down();
void menu_enter();
void print_menu();
void build_menu(); // doar "umple" variabilele

#endif // MENU_H_INCLUDED
