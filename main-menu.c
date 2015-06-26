
///\file main-menu.c
///\brief Biblioteca C pentru implementarea optiunilor menu-ului.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -functia de corectare a unui singur cuvant
* -corectarea unui text dintr-un fisier
* -corectarea cuvintelor in timp real
*/

#include"list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include"menu.h" ///> menu_up(),menu_down(),menu_enter(),print_menu(),build_menu()
#include<windows.h> ///> Sleep()
#include<stdio.h> ///> printf()
#include<string.h> ///> strcpy()
#include<conio.h> ///> getch()
#include"levenshtein.h" ///> find_sim_words()

bool is_letter(char c){

    ///\fn bool is_letter(char c)
    ///\brief Verificarea daca un caracter este litera
    ///\param c Variabila de tip char
    ///
    ///Implementarea verificarii unui caracter daca este litera


//    if(c<'A' || c>'z')
//        return false;
//    return true;

    int i;

    char separator[]=" ,./;'[]\<>?:\"{}|~!@#$%^&*()`_+-=\n";
    for(i=0;i<strlen(separator);i++)
        if(c==separator[i])
            return false;
    return true;
}


void one_word(){

    ///\fn void one_word()
    ///\brief Corectarea un cuvant introdus.
    ///
    ///Implementarea corectarii a unui cuvant introdus de la tastatura.


    char word[50]; // cuvantul care va fi verificat
    List sim_words ;  // lista cuvintelor asemanatoare cu cuvantul citit

// golirea bufferului
    fflush(stdin);
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        continue;

    system("cls");
    printf("\n\t\tOne word function: \n\n");

   while( 1 ){        //repeat while ESC isn't pressed

        tryAgain:
        system("cls");
        printf("\n\tPlease enter the word:  ");
        gets(word);
        if(word[strlen(word)-1]=='\n')
            word[strlen(word)-1]='\0';
        if(strlen(word)<=2)
            goto tryAgain;

            // if the word is incorrect
            if(list_search(&dict_lex, word)==NULL){

                Beep(20,200);

                find_sim_words(&sim_words, word, strlen(word), dict_lex.head, dict_lex.tail);

                if(sim_words.head==NULL){
                    ClearSelectAreea();
                    Beep(90,200);
                    GotoXY(3,3);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                    getchar();
                    return;
                }
                else{
                    Beep(70,200);
                    List_Node * newTail = malloc(sizeof(List_Node));
                    newTail->word = malloc(sizeof(char)*strlen(word)+1);
                    strcpy(newTail->word,word);
                    list_insert(&sim_words,newTail);
                    Select_correct_word(word, &sim_words);
                    free_list(&sim_words);
                    return;
                }
            }
            else{
                ClearSelectAreea();
                GotoXY(3,3);
                printf("The word \"%s\" is correct!\n",word);
                return;
            }
    }
}

void from_file(){

    ///\fn void from_file()
    ///\brief Corectarea unui sir de caractere.
    ///
    ///Implementarea corectarii a unui sir de caractere citit din fisier.


    char fileName[100];
    char buff[2255];
    char *p;

    FILE * f_corected = fopen("from file corected.txt","w");
    FILE * file;
    char ch[2],word[150],wordINIT[150];
    ch[1]='\0';
    List sim_words ;
    POINT curs, cursBack;// cursor position


    tryAgain:
    system("cls");
    printf("\n\tPlease enter the name of the file (e.g. : file.txt):  ");
    gets(fileName);
    if(fileName[strlen(fileName)-1]=='\n')
        fileName[strlen(fileName)-1]='\0';
    if(strlen(fileName)<=2)
        goto tryAgain;

    file = fopen(fileName,"r");
    if( file == NULL ){
        printf("\n\t This file doesn't exist!");
        Sleep(2000);
        goto tryAgain;
    }


    GotoXY(3,3);
    printf(" Here you will see all the informations you need about your text!");

    GotoXY(3,9);
    printf("Your text:");

    // complex flush
    fflush(stdin);
    while ((ch[0] = getchar()) != '\n' && ch[0] != EOF)
        continue;

    GotoXY(3,10);// typing

     while(1){

        word[0]='\0';
        ch[0]='\0';
            if(kbhit()){
                ch[0] = getch();
                if(is_letter(ch[0]) == true){
                    strcat(word,ch );
                    printf("%c",ch[0]);
                }
            }
        save_curs(&curs);
        if(!fgets(ch,2,file)){
                getchar();
                fclose(f_corected);
                fclose(file);
                return;
            }
        //add a word
        while( is_letter(ch[0])==true  ){


            strcat(word,ch);
            printf("%c",ch[0]);

            if(GetAsyncKeyState( VK_ESCAPE )& 0x8000){
                fclose(f_corected);
                return;
            }
            if(!fgets(ch,2,file)){
                getchar();
                fclose(f_corected);
                return;
            }
        }

        strcpy(wordINIT,word);
        strcpy(word,strlwr(word));

        // if an word was typed
        if(word[0]>='A' && word[0]<='z' && strlen(word)>=2){
            if(word[strlen(word)-1]<'A' || word[strlen(word)-1]>'z')
                word[strlen(word)-1]='\0';

            // if the word is incorrect
            if(list_search(&dict_lex, strlwr(word))==NULL){

                Beep(20,200);
                    GotoXY(3,3);
                    printf("The word \"%s\" is incorrect!",word);

                sim_words.head=NULL;
                sim_words.tail=NULL;
                find_sim_words(&sim_words, word, strlen(word), dict_lex.head, dict_lex.tail);

                if(sim_words.head==NULL){
                    ClearSelectAreea();
                    Beep(90,200);
                    GotoXY(3,3);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                    Sleep(650);
                    getchar();
                }
                else{
                    Beep(70,200);
                    List_Node * newTail = malloc(sizeof(List_Node));
                    newTail->word = malloc(sizeof(char)*strlen(wordINIT)+1);
                    strcpy(newTail->word,wordINIT);
                    list_insert(&sim_words,newTail);
                    Select_correct_word(word, &sim_words);
                    ClearSelectAreea();
                    GotoXY(3,3);
                    printf("The correct word for \"%s\" is \"%s\"!",wordINIT,word);
                    strcpy(wordINIT,word);
                    free_list(&sim_words);
                }
            }
            else{
                ClearSelectAreea();
                GotoXY(3,3);
                printf("The word \"%s\" is correct!\n",word);
            }
        }

        ClearAfterPoint(curs);

        // back to the saved cursor
        GotoXY(curs.x, curs.y);

        // update the word to the cmd and go on
        printf("%s",wordINIT);
        printf("%c",ch[0]);

        fprintf(f_corected,"%s",wordINIT);
        fprintf(f_corected,"%c",ch[0]);

        Sleep(50);
    }
    getchar();
}

// functii necesare pentru live-input
void flush(){
    ///\fn void flush()
    ///\brief Functia ce goleste bufferul.
    ///

    char ch;
    fflush(stdin);
        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
}
void ClearSelectAreea(){

    ///\fn void ClearSelectAreea()
    ///\brief Sterge suprafata de sugestii.
    ///
    ///Implementarea stergerii DOAR a suprafetei rezervata sugestiilor pentru cuvintele gresite.


    int i;
    for(i=0;i<8;i++){
        GotoXY(0,i);
        printf("                                                                         ");
    }
}
void ClearAfterPoint(POINT p){

    ///\fn void ClearAfterPoint(POINT p)
    ///\brief Sterge caracaterele nedorite.
    ///\param p Variabila de tip POINT
    ///
    ///Implementarea functiei de stergere pentru caracterele nedorite aparute in urma selectarii sugestiilor cu ajutorul sagetilor.


    int i;
    GotoXY(p.x,p.y);
    for(i=0;i<9;i++){
        printf("                                           ");
    }
    GotoXY(p.x,p.y);
}
void Print_sel(char * word, List * l, List_Node * high_item){//print selection area

    ///\fn void Print_sel(char * word, List * l, List_Node * high_item)
    ///\brief Afisarea sugestiei.
    ///\param word Variabila de tip char
    ///\param l Variabila de tip List
    ///\param high_item Variabila de tip List_Node
    ///
    ///Implementarea afisarii sugestiei selectate.


    List_Node* i;
    i=l->head;
    int cnt=0;

    ClearSelectAreea();
    GotoXY(0,0);
    printf("\t\Sugestii pentru \"%s\":",word);
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


   ///\fn Select_correct_word(char * word, List * sugestions)
    ///\brief Selectarea sugestiei.
    ///\param word Variabila de tip char
    ///\param sugestions Variabila de tip List reprezentand sugestiile gasite
    ///
    ///Implementarea gasirii celor mai apropiate cuvinte de cuvantul considerat gresit


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
            Sleep(100);
        }

        if(GetAsyncKeyState( VK_DOWN )& 0x8000){
            if(high_item!=sugestions->tail)
                high_item = high_item->next;
            else
                high_item = sugestions->head;
            Print_sel(word,  sugestions, high_item );
            Sleep(100);
        }

        if(GetAsyncKeyState( VK_RETURN)& 0x8000){
            strcpy(word, high_item->word);
            Sleep(50);
            flush();
            return;
        }
    }flush();
}

void live_input(){

    ///\fn void live_input()
    ///\brief Corectare in timp real.
    ///
    ///Implementarea corectarii in timp real ale cuvintelor introduse de la tastatura.


    FILE * f_corected = fopen("live_input f_corected.txt","w");
    FILE * f_inserted = fopen("live_input f_inserted.txt","w");
    char ch[2],word[50],wordINIT[50];
    ch[1]='\0';
    List sim_words ;
    POINT curs, cursBack;// cursor position

    ClearSelectAreea();
    GotoXY(3,3);
    printf(" Here you will see all the informations you need about your text ");

    GotoXY(3,9);
    printf("Your text:");

    // complex flush
    fflush(stdin);
    while ((ch[0] = getchar()) != '\n' && ch[0] != EOF)
        continue;

    GotoXY(3,10);// typing
    while(1){

        word[0]='\0';
        ch[0]='\0';

        save_curs(&curs);
        //add a word
        while( is_letter(ch[0])==true ){
            if(kbhit()){
                ch[0] = getch();
                if(is_letter(ch[0]) == true){
                    strcat(word,ch);
                    printf("%c",ch[0]);
                }
            }

            if(GetAsyncKeyState( VK_BACK )& 0x8000){
                if( strlen(word) != 0){
                    save_curs(&cursBack);
                    GotoXY( cursBack.x-1, cursBack.y);
                    printf(" ");
                    word[strlen(word)-1]='\0';
                    GotoXY(curs.x,curs.y);
                    printf("%s",word);
                    GotoXY(cursBack.x-1, cursBack.y);
                    Sleep(100);
                }
            }
            if(GetAsyncKeyState( VK_ESCAPE )& 0x8000){
                return;
                fclose(f_inserted);
                fclose(f_corected);
            }
            if(GetAsyncKeyState( VK_RETURN )& 0x8000) break;
        }


        strcpy(wordINIT,word);
        strcpy(word,strlwr(word));

        // if an word was typed
        if(word[0]>='A' && word[0]<='z' && strlen(word)>=2){
            if(word[strlen(word)-1]<'A' || word[strlen(word)-1]>'z')
                word[strlen(word)-1]='\0';

            fprintf(f_inserted,"%s",word);
            fprintf(f_inserted,"%c",ch[0]);

            // if the word is incorrect
            if(list_search(&dict_lex, word)==NULL){

                Beep(20,200);
                find_sim_words(&sim_words, word, strlen(word), dict_lex.head, dict_lex.tail);

                if(sim_words.head==NULL){
                    ClearSelectAreea();
                    Beep(90,200);

                    ClearSelectAreea();
                    GotoXY(3,3);
                    printf("The word \"%s\" is incorrect and there are no word like him!\n",word);
                    Sleep(650);
                    getchar();
                }
                else{
                    Beep(70,200);
                    List_Node * newTail = malloc(sizeof(List_Node));
                    newTail->word = malloc(sizeof(char)*strlen(wordINIT)+1);
                    strcpy(newTail->word,wordINIT);
                    list_insert(&sim_words,newTail);
                    Select_correct_word(word, &sim_words);

                    ClearSelectAreea();
                    GotoXY(3,3);
                    printf("The correct word for \"%s\" is \"%s\"!",wordINIT,word);

                    free_list(&sim_words);
                    strcpy(wordINIT,word);
                }
            }
            else{
                ClearSelectAreea();
                GotoXY(3,3);
                printf("The word \"%s\" is correct!\n",word);
            }
        }

        ClearAfterPoint(curs);

        // back to the saved cursor
        GotoXY(curs.x, curs.y);

        // update the word to the cmd and go on
        printf("%s",wordINIT);
        printf("%c",ch[0]);

        fprintf(f_corected,"%s",wordINIT);
        fprintf(f_corected,"%c",ch[0]);

        Sleep(50);
    }
}
