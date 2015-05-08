#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // de folosit mai mult pe viitor
#include <windows.h>
// au mai fost scoase din headerele nefolosite in main
#include "list.h"
#include "menu.h"

int main() {
    build_dictionaries(); // aceasta linie a fost comentata pentru ca dura putin soratea dictionarului
    build_menu();
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

