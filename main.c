#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "list.h"
#include "menu.h"
#include"keys-distantance.h"

int main() {
    printf("\n\n\t Please wait!");

    load_dictionaries();
    build_menu();
    load_keyboard("keyboard.txt");

    print_menu();

//insert_word();

    while(1){

        if(GetAsyncKeyState( VK_UP )& 0x8000)
            menu_up();
        if(GetAsyncKeyState( VK_DOWN )& 0x8000)
            menu_down();
        if(GetAsyncKeyState( VK_RETURN)& 0x8000)
            menu_enter();
        Sleep(50);
    }
    return 0;
}

