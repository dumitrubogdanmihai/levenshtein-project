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


// functii necesare pentru live-input
void flush(){
    char ch;
    fflush(stdin);
        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
}
void ClearSelectAreea(){
    int i;
    for(i=0;i<9;i++){
        GotoXY(0,i);
        printf("                                           ");
    }
}
void Print_sel(char * word, List * l, List_Node * high_item){//print selection area
    List_Node* i;
    i=l->head;
    int cnt=0;

    ClearSelectAreea();
    GotoXY(0,0);
    printf("\t\Sugestii pentru %s",word);
    GotoXY(0,2);

    if(high_item->prev != NULL){
        i = high_item->prev ;
        if(high_item->prev->prev != NULL ){
            i = high_item->prev->prev;
        }
    }

    GotoXY(0,2);
    while( cnt <=4 && i!=NULL ){
        if(i==high_item)
            printf(" > ");
        printf(" %s\n",i->word);
        i=i->next;
        cnt++;
    }

}
void Select_correct_word(char * word, List * sugestions){
    //printf("\n\t SELECT\n");Sleep(300);
    List_Node * high_item;
    high_item = sugestions->head;

    Print_sel(word, sugestions, high_item );

    while(1){
        if(GetAsyncKeyState( VK_UP )& 0x8000){
            if(high_item!=sugestions->head)
                high_item = high_item->prev;
            else
                high_item = sugestions->tail;
            Print_sel(word,  sugestions, high_item );
        }

        if(GetAsyncKeyState( VK_DOWN )& 0x8000){
            if(high_item!=sugestions->tail)
                high_item = high_item->next;
            else
                high_item = sugestions->head;
            Print_sel(word,  sugestions, high_item );
        }

        if(GetAsyncKeyState( VK_RETURN)& 0x8000){
            strcpy(word, high_item->word);
            ClearSelectAreea();flush();
            return;
        }
        Sleep(50); //kill the extra sensibility
    }flush();
}

void live_input(){

    FILE * f = fopen("live_input.txt","w");
    char ch[2],word[50];
    ch[1]='\0';
    List sim_words ;
    POINT curs;// cursor position

    // complex flush
    fflush(stdin);
    while ((ch[0] = getchar()) != '\n' && ch[0] != EOF)
        continue;

    Sleep(150);


    GotoXY(0,10);// typing
    while(1){
        word[0]='\0';
        ch[0]='\0';
        save_curs(&curs);

        //add a word
        while(ch[0]!=' '){
            if(kbhit()){
                ch[0] = getch();
                if(ch[0]>'A'&&ch[0]<'z'){
                    strcat(word,ch);
                    printf("%c",ch[0]);
                }
            }
            if(GetAsyncKeyState( VK_ESCAPE )& 0x8000)
                return;
            if(GetAsyncKeyState( VK_RETURN )& 0x8000)
                break;
        }


        // if an word was typed
        if(word[0]!='\0'){
            if(word[strlen(word)-1]==' ')
                word[strlen(word)-1]='\0';

            // if the word is incorrect
            if(list_search(&l_dict_lex, word)==NULL){

                Beep(20,200);

                find_similar_words(&sim_words, word, strlen(word)/2+1, l_dict_lex.head, l_dict_lex.tail);
                sort_list_lev_upgraded(&sim_words, word);

                if(sim_words.head==NULL){
                    Beep(30,200);
                   // printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                }
                else{
                    Beep(10,200);

                    Select_correct_word(word, &sim_words);
                }
            }
        }
    Sleep(50);
    GotoXY(curs.x, curs.y);
    printf("%s ",word);
    //Sleep(550);
    fprintf(f,"%s ",word);
    //Sleep(550);


        // back to the saved cursor
        // update the word to the cmd and go on
        Sleep(50);
    }
}
