///\file menu.c
///\brief Biblioteca C pentru implementarea menu-ului si a functiilor ce permit deplasarea in intermediul acestuia.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -functia de creare a menu-ului
* -afisarea acestuia
* -functiile ce permit deplasarea in intermediul menu-ului
* -functia de mutare a cursorului
*/

#include"main-menu.h" ///> one_word(),from_file(),live_input()
#include"levenshtein.h"
#include"menu.h" ///> menu_up(),menu_down(),menu_enter(),print_menu(),build_menu()
#include"options-menu.h" ///> update_app_words()
#include<conio.h> ///> getch()
#include<windows.h> ///> Sleep()


void GotoXY( int x, int y){ // move the cursor to the line y and column x

    ///\fn void GotoXY( int x, int y)
    ///\brief Deplasarea cursorului.
    ///\param x Variabila de tip intreg ce reprezinta linia la care se va deplasa cursorul.
    ///\param y Variabila de tip intreg ce reprezinta coloana la care se va deplasa cursorul.
    ///
    ///Implementarea deplasarii cursorului la coordonatele specificate prin parametrii.


   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
int wherex(){

    ///\fn int wherex()
    ///\brief Gasirea coordonatei x a cursorului.
    ///
    ///Implementarea gasirii liniei (coordonatei x) pe care se afla cursorul.

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
        return -1;
    return csbi.dwCursorPosition.X;
}
int wherey(){

     ///\fn int wherey()
    ///\brief Gasirea coordonatei y a cursorului.
    ///
    ///Implementarea gasirii coloanei (coordonatei y) pe care se afla cursorul.

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
        return -1;
    return csbi.dwCursorPosition.Y;
}
void save_curs(POINT * p){

    ///\fn void save_curs(POINT * p)
    ///\brief Salvarea pozitiei cursorului.
    ///\param p Variabila tip POINT care stocheaza pozitia cursorului
    ///
    ///Implementarea salvarii pozitiei cursorului.

    p->x = wherex();
    p->y = wherey();
}

void menu_up(){

    ///\fn void menu_up()
    ///\brief Deplasarea in sus in menu.
    ///
    ///Implementarea deplasarii in sus in cadrul menu-ului pentru selectarea optiunii dorite.

    if(highlighted_item > 0)
        highlighted_item --;
    else
        highlighted_item =menu[current_menu].nr_items-1;
    print_menu();
    Sleep(50);
}
void menu_down(){

    ///\fn void menu_down()
    ///\brief Deplasarea in jos in menu.
    ///
    ///Implementarea deplasarii in jos in cadrul menu-ului pentru selectarea optiunii dorite.


    if(highlighted_item < menu[current_menu].nr_items-1)
        highlighted_item ++;
    else
        highlighted_item = 0;
    print_menu();
    Sleep(50);
}
void menu_enter(){

    ///\fn void menu_enter()
    ///\brief Selectarea optiunii.
    ///
    ///Implementarea selectarii dorite in cadrul unei optiunilor din menu.


    system("cls");
    // se ia fiecare caz de meniu si fiecare caz de element de meniu in parte.

    switch(current_menu){
        // main menu
        case 0 : {
            switch (highlighted_item){
                case 0 : {//input one word
                    one_word();
                    break;
                }
                case 1 : {//From file
                    from_file();
                    break;
                }
                case 2 : {//Live
                    live_input();
                    break;
                }
                case 3 : {//options-menu
                    current_menu = 1;
                    highlighted_item = 0;
                    break;
                }
                case 4 : {//Exit
                    printf("\n\n\tGood bye!");
                    Sleep(750);
                    exit(0);
                    break;
                }
            }
            break;
        }

        //options-menu
        case 1 : {
            switch (highlighted_item){
                case 0 : {//Update words apparitions
                    update_app_words();
                    break;
                }
                case 1 : {//Insert an word to dictionary
                    insert_word();
                    break;
                }
                case 2 : {//Delete an word from dictionary
                    delete_word();
                    break;
                }
                case 3 : {//Reset dictionary
                    reset_dict();
                    break;
                }
                case 4 : {//Build dictionary from file
                    build_dict();
                    break;
                }
                case 5 : {//Add words to dictionary from file
                    update_words();
                    break;
                }
                case 6 : {//select_suggestions_funcition
                    current_menu = 2;
                    highlighted_item = sugg_funct;
                    break;
                }
                case 7 : {//back
                    current_menu = 0;
                    highlighted_item = 0;
                    break;
                }
            }
            break;
        }

        //select suggestion functions
        case 2 : {
            switch (highlighted_item){
                case 0 : {//leven
                    sugg_funct = 0;
                    break;
                }
                case 1 : {//leven 2.0
                    sugg_funct = 1;
                    break;
                }
                case 2 : {//back
                    current_menu = 1;
                    highlighted_item = 0;
                    break;
                }
            }
        }
    }
    print_menu();
    Sleep(50);
}
void print_menu(){

    ///\fn void print_menu()
    ///\brief Afisare menu.
    ///
    ///Implementarea functiei de afisare a menu-ului.

    int i,j;
    system("cls");
//    system("clear"); unix
    printf("\n\n\n\t");
    for(i=0; i<menu[current_menu].nr_items; i++, printf("\n\t")){
        if(highlighted_item == i)
            printf(" > ");
        for(j=0; j<strlen(menu[current_menu].item[i]); j++)
            printf("%c", menu[current_menu].item[i][j]);
        if(highlighted_item == i)
            printf(" < ");
    }
}
void build_menu(){

    ///\fn void build_menu()
    ///\brief Construirea menu-ului.
    ///
    ///Implementarea functiei de construire a menu-ului.

    // se atribuie variabilelor aferente meniului valorile si stringurile corespunzatoare
    current_menu=0; // primul meniu afisat este meniul principal care are ID-ul = 0
    highlighted_item = 0; // elementul din meniu subliniat este primul element al meniului

    // MAIN MENU - ID = 0
    menu[0].nr_items = 5; // numarul de elemente din meniul cu ID-ul = 0 este 5
    strcpy( menu[0].item[0] , "One word" );
    strcpy( menu[0].item[1] , "From file" );
    strcpy( menu[0].item[2] , "Live input" );
    strcpy( menu[0].item[3] , "Options" );
    strcpy( menu[0].item[4] , "Quit" );

    menu[1].nr_items = 8;
    strcpy( menu[1].item[0] , "Update words apparitions" );
    strcpy( menu[1].item[1] , "Insert an word to dictionary" );
    strcpy( menu[1].item[2] , "Delete an word from dictionary" );
    strcpy( menu[1].item[3] , "Reset dictionary" );
    strcpy( menu[1].item[4] , "Build dictionary from file" );
    strcpy( menu[1].item[5] , "Add words to dictionary from file" );
    strcpy( menu[1].item[6] , "Select suggestions function" );
    strcpy( menu[1].item[7] , "Back" );



    menu[2].nr_items = 3;
    strcpy( menu[2].item[0] , "Levenshtein" );
    strcpy( menu[2].item[1] , "Levenshtein 2.0" );
    strcpy( menu[2].item[2] , "Back" );
}
