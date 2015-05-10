#include"list.h"
#include<windows.h>
#include<stdio.h>
void one_word(){
    char word[50]; // cuvantul care va fi verificat
    int error;      // eroarea maxima a cuvatului / diferenta maxima suportata dintre cuvinte
    List sim_words ;  // lista cuvintelor asemanatoare cu cuvantul citit

// golirea bufferului
    fflush(stdin);
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        continue;

    system("cls");
    printf("\n\t\tOne word function: \n\n");
    printf(" Enter the word: ");
    scanf("%s",word);
    printf(" Enter the maximum error accepted: ");
    scanf("%d",&error);
    printf("\n");

    find_similar_words(&sim_words, word, error, l_dict_lex.head, l_dict_lex.tail);
    print_list(sim_words.head, sim_words.tail);

    printf("\n\tPress any key to come back to the main menu!");
    getch();
    Sleep(100);
}
void from_file(){
    // aici va fi mai complicat pentru ca este necesara parsarea textului si trebuie sa gasim o modalitate prin care sa afisam si textul, cuvintele gresite si sugestiile cat mai logic si estetic
    printf("\n\t\tFrom file function ");
    Sleep(1500);
}
void live_input(){
    char ch[2],word[50];
    ch[1]='\0';
    List sim_words ;

    // complex flush
    fflush(stdin);
    while ((ch[0] = getchar()) != '\n' && ch[0] != EOF)
        continue;

    printf("\n\t\tLive_input function ");
    printf("\n\t\tPress ESC to exit\n");
    while(1){
        printf(" Word:");
        word[0]='\0';
        ch[0]='\0';
        while(ch[0]!=' '){
            if(kbhit()){
                ch[0] = getch();
                printf("%c",ch[0]);
                strcat(word,ch);
            }
            if(GetAsyncKeyState( VK_ESCAPE ))
                return;
        }
        if(word[strlen(word)-1]==' ')
            word[strlen(word)-1]='\0';
//        printf("\n Cuvantul format  este: \"%s\"\n",word);
        find_similar_words(&sim_words, word, 1, l_dict_lex.head, l_dict_lex.tail);
//        print_list(sim_words.head, sim_words.tail);
        sort_list_lev(&sim_words, word);
//printf("\"%s\"\n",)
        if(strcmp(sim_words.head->word,word)==0)
            printf(" - Cuvant Corect!\n");
        else
           print_list(sim_words.head, sim_words.tail);
    }
}
