#include"list.h"
#include<windows.h>
#include<stdio.h>
#include<string.h>
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

    if(list_search(&l_dict_lex, word)==NULL){
                Beep(20,200);
                find_similar_words(&sim_words, word, strlen(word)/2+1, l_dict_lex.head, l_dict_lex.tail);
                sort_list_lev_upgraded(&sim_words, word);
                if(sim_words.head==NULL){
                    Beep(30,200);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                }
                else{
                    Beep(10,200);
                    printf("The word \"%s\" is not correct!\n Suggestions: \n",word);
                    print_list(sim_words.head, sim_words.tail);
                }
            }
            else{
                    printf("The word \"%s\" is correct!\n",word);
            }

    printf("\n\tPress any key to come back to the main menu!");
    getch();
}
void from_file(){
    system("cls");
    printf("\n\t\tFrom file function \n");
    char buff[255];
    char separator[]=" ,.?!-\n";
    char *p;
    FILE *f = fopen("file.txt","r");
    List sim_words ;

    fflush(stdin);
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        continue;

    while(fgets(buff,255,f)){
        p=strlwr(strtok(buff,separator));
        while(p!=NULL){
            if(list_search(&l_dict_lex, p)==NULL){
                Beep(20,200);
                find_similar_words(&sim_words, p, strlen(p)/2+1, l_dict_lex.head, l_dict_lex.tail);
                sort_list_lev_upgraded(&sim_words, p);
                if(sim_words.head==NULL){
                    Beep(30,200);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",p);
                }
                else{
                    Beep(10,200);
                    printf("The word \"%s\" is not correct!\n Suggestions: \n",p);
                    print_list(sim_words.head, sim_words.tail);
                }
            }
            else{
                    printf("The word \"%s\" is correct!\n",p);
            }

            p=strlwr(strtok(NULL,separator));
        }
    }
    printf("\n\tPress any key to come back to the main menu!");
    getch();
}
void live_input(){
    char ch[2],word[50];
    ch[1]='\0';
    List sim_words ;

    // complex flush
    fflush(stdin);
    while ((ch[0] = getchar()) != '\n' && ch[0] != EOF)
        continue;

    Sleep(150);

    printf("\n\t\tLive_input function ");
    printf("\n\t\tPress ESC to exit\n");
    while(1){
        printf("\n Word:");
        word[0]='\0';
        ch[0]='\0';
        while(ch[0]!=' '){
            if(kbhit()){
                ch[0] = getch();
                printf("%c",ch[0]);
                if(ch[0]>'A'&&ch[0]<'z')
                    strcat(word,ch);
            }
            if(GetAsyncKeyState( VK_ESCAPE )& 0x8000)
                return;
            if(GetAsyncKeyState( VK_RETURN )& 0x8000){
                 break;
            }
        }
        if(word[0]!='\0'){
            if(word[strlen(word)-1]==' ')
                word[strlen(word)-1]='\0';

                 if(list_search(&l_dict_lex, word)==NULL){
                Beep(20,200);
                find_similar_words(&sim_words, word, strlen(word)/2+1, l_dict_lex.head, l_dict_lex.tail);
                sort_list_lev_upgraded(&sim_words, word);
                if(sim_words.head==NULL){
                    Beep(30,200);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                }
                else{
                    Beep(10,200);
                    printf("The word \"%s\" is not correct!\n Suggestions: \n",word);
                    print_list(sim_words.head, sim_words.tail);
                }
            }
            else{
                    printf("The word \"%s\" is correct!\n",word);
            }
        }
        Sleep(50);
    }
}
