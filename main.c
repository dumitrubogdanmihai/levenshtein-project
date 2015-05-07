#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "list.h"
#include "menu.h"

// la fiecare declarare de variabile de tip List a se va atribui nume_var.head=NULL!!!
void build_dictionaries();
int main() {
    bool enter=false;
//    build_dictionaries();
    build_menu();
    print_menu();
    while(1){
        if( enter == true){// atunci cand revine dintr-o functie din "functionalities.c" in bucla meniului trebuie sa se reafiseze meniul si pentru a nu se reafisa la fiecare ciclu se reafiseaza doar o singura data dupa ce s-a apasat enter
            print_menu();
            enter=false;
        }
        if(GetAsyncKeyState( VK_UP ))
            menu_up();
        if(GetAsyncKeyState( VK_DOWN ))
            menu_down();
        if(GetAsyncKeyState( VK_RETURN)){
            enter=true;
            menu_enter();
        }
        Sleep(50); //kill the extra sensibility
    }

    return 0;
}

void build_dictionaries(){
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

