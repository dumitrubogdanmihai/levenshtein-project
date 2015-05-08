#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // de folosit mai mult pe viitor
#include <windows.h>
// au mai fost scoase din headerele nefolosite in main
#include "list.h"
#include "menu.h"

void build_dictionaries();// pe viitor functia aceasta ar fi bine sa o mutam in list.c
int main() {
    bool enter=false; // semnaleaza apasarea tastei enter
//    build_dictionaries(); // aceasta linie a fost comentata pentru ca dura putin soratea dictionarului
//                              pe viitor trebuie sa tinem 2 fisiere: unul pentru soratea lexicografica si unul cu dictionarul sortat dupa numarul de litere
    build_menu();
    print_menu();
    while(1){
        if( enter == true){// atunci cand revine dintr-o functie din "functionalities.c" in bucla meniului trebuie sa se reafiseze meniul si pentru a nu se reafisa la fiecare ciclu se reafiseaza doar o singura data dupa ce s-a apasat enter
            enter=false;
            print_menu();
        }
        if(GetAsyncKeyState( VK_UP ))
            menu_up();// du-te la menu.c
        if(GetAsyncKeyState( VK_DOWN ))
            menu_down();
        if(GetAsyncKeyState( VK_RETURN)){
            enter=true;
            menu_enter();
        }
        Sleep(25); //kill the extra sensibility
    }
    return 0;
}

void build_dictionaries(){ // pe viitor functia aceasta ar fi bine sa o mutam in list.c
    List l_dict_lex = load_words("dictionary/rodex.txt",false);
    sort_list_lex(&l_dict_lex);
    List_Node* ind_lex[27];
    index_lex(&l_dict_lex, ind_lex);

    List l_dict_len = load_words("dictionary/rodex.txt",false);
    sort_list_len(&l_dict_len, l_dict_len.head, l_dict_len.tail);
    int max_len=0;
    List_Node* ind_len[40];
    index_len(&l_dict_len, ind_len, &max_len);
}

