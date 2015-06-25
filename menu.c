<<<<<<< HEAD
#include"menu.h"
#include"levenshtein.h"
#include<stdio.h>
#include<conio.h>
#include<windows.h>
=======
#include"main-menu.h" ///> one_word(),from_file(),live_input()
#include"levenshtein.h"
#include"menu.h" ///> menu_up(),menu_down(),menu_enter(),print_menu(),build_menu()
#include"options-menu.h" ///> update_app_words()
#include<conio.h> ///> printf()
#include<windows.h> ///> printf()
>>>>>>> origin/master

void GotoXY( int x, int y){ // move the cursor to the line y and column x
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
int wherex(){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
            return -1;
        return csbi.dwCursorPosition.X;
    }
int wherey(){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi))
            return -1;
        return csbi.dwCursorPosition.Y;
    }
void save_curs(POINT * p){
    p->x = wherex();
    p->y = wherey();
}

void menu_up(){
    if(highlighted_item > 0)
        highlighted_item --;
    else
        highlighted_item =menu[current_menu].nr_items-1;
    print_menu();
    Sleep(50);
}
void menu_down(){
    if(highlighted_item < menu[current_menu].nr_items-1)
        highlighted_item ++;
    else
        highlighted_item = 0;
    print_menu();
    Sleep(50);
}
void menu_enter(){
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
                    printf("\n\tBye-Bye!");
                    Sleep(1000);
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
    int i,j;
    system("cls");
//    system("clear"); unix
    printf("\n\n\n\t");
    for(i=0; i<menu[current_menu].nr_items; i++, printf("\n\t")){
        if(highlighted_item == i)
                printf(" > ");
        for(j=0; j<strlen(menu[current_menu].item[i]); j++)
                printf("%c", menu[current_menu].item[i][j]);
    }
}
void build_menu(){
    // se atribuie variabilelor aferente meniului valorile si stringurile corespunzatoare
    current_menu=0; // primul meniu afisat este meniul principal care are ID-ul = 0
    highlighted_item = 0; // elementul din meniu subliniat este primul element al meniului

    // MAIN MENU - ID = 0
    menu[0].nr_items = 5; // numarul de elemente din meniul cu ID-ul = 0 este 5
    strcpy( menu[0].item[0] , "One word" );
    strcpy( menu[0].item[1] , "From file" );
    strcpy( menu[0].item[2] , "Live input" );
    strcpy( menu[0].item[3] , "Options menu" );
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
