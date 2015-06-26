
///\file main.c
///\brief Corector de cuvinte
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.

#include <stdio.h> ///> printf()
#include <stdlib.h> ///> malloc()
#include <assert.h> ///> assert()
#include <windows.h> ///> Sleep()
#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include "menu.h" ///> menu_up(),menu_down(),menu_enter(),print_menu(),build_menu()
#include"keys-distantance.h" ///> getNeighbors(),dist_lit(),distanta_cuvinte(),load_keyboard()
#include"levenshtein.h" ///> find_sim_words()


int main() {

   ///\fn int main()
    ///\brief Functia main
    /**
        * Aici se apeleaza functia de incarcare a dictionarului, construirea menu-ului si functia ce construieste o matrice ce reproduce partial tastatura.
        * Tot in cadrul acste functii se realizeaza apelarea functiilor ce ne permit deplasarea prin menu.
    */


    printf("\n\n\t Please wait!");

    sugg_funct = 1;

    load_dictionaries();
    build_menu();
    load_keyboard("keyboard.txt");

    print_menu();
    while(1){
        if(GetAsyncKeyState( VK_UP )& 0x8000)
            menu_up();
        if(GetAsyncKeyState( VK_DOWN )& 0x8000)
            menu_down();
        if(GetAsyncKeyState( VK_RETURN)& 0x8000)
            menu_enter();

    }
    return 0;
}

