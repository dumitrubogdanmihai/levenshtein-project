#include"functionalities.h"
#include"menu.h"
#include<conio.h>
#include<windows.h>
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
    Beep(5,50);
    if(highlighted_item > 0)
        highlighted_item --;
    else
        highlighted_item =menu[current_menu].nr_items-1;
    print_menu();
}
void menu_down(){
    Beep(5,50);
    if(highlighted_item < menu[current_menu].nr_items-1)
        highlighted_item ++;
    else
        highlighted_item = 0;
    print_menu();
}
void menu_enter(){
    Beep(5,50);
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
                case 3 : {//Options
                    printf("\n\tOptions");// dupa ce se va contrui meniul de optiuni se va afisa acesta pe ecran
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

        //options
        case 1 : {
            break;
        }
    }
    print_menu();
}
void print_menu(){
    int i,j;
    system("cls");
//    system("clear"); unix
    printf("\n\n\n\t");
    for(i=0; i<menu[current_menu].nr_items; i++, printf("\n\t"))
        for(j=0; j<strlen(menu[current_menu].item[i]); j++)
            if(highlighted_item == i)
                printf(" %c", menu[current_menu].item[i][j]);
            else
                printf("%c", menu[current_menu].item[i][j]);
            // daca elementul din meniu pe care doresc sa-l afisez este egal cu elementul subliniat atunci se evidentiaza cu cate un spatiu intre literele sale
            // pe viitor am putea sa-l evidentiem colorandu-l intr-o culoare aparte
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
    strcpy( menu[0].item[3] , "Options" );
    strcpy( menu[0].item[4] , "Quit" );
}
