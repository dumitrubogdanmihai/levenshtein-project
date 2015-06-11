
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "list.h"
#include "menu.h"
#include"keys-distantance.h"

int main() {
    build_dictionaries();
    build_menu();
    load_keyboard("keyboard.txt");
    print_menu();
    while(1){
        if(GetAsyncKeyState( VK_UP )& 0x8000)
            menu_up();// du-te la menu.c
        if(GetAsyncKeyState( VK_DOWN )& 0x8000)
            menu_down();
        if(GetAsyncKeyState( VK_RETURN)& 0x8000)
            menu_enter();
        Sleep(50); //kill the extra sensibility
    }
    return 0;
}
