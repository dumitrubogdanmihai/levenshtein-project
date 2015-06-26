///\file options-menu.c
///\brief Biblioteca C pentru implementarea functiilor regasite in "Options".
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.

#include"list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include<windows.h> ///> Sleep()
#include<stdio.h> ///> printf()
#include<string.h> ///> strlen(),strtok(),strlwr()


void update_app_words(){


    ///\fn void update_app_words()
    ///\brief Actualizeaza numarul aparitiilor cuvintelor dictionarului
    ///
    ///Implementarea actualizarii numarul aparitiilor cuvintelor dictionarului dintr-un fisier dat de utilizator

    char fileName[100];
    List_Node * n;
    system("cls");

    enterFileName:
    printf("\n\tPlease enter the name of the file (e.g. : fisier.txt):");
    fgets(fileName,99,stdin);
    fileName[strlen(fileName)-1]='\0';
    FILE *f = fopen(fileName,"r");
    if(f==NULL){
        printf("\nThe file \"%s\" doesn't exist!\n",fileName);
        goto enterFileName;
    }

    char buff[255];
    char separator[]=" ,./;'[]\<>?:\"{}|~!@#$%^&*()`";
    char *p;

    while(fgets(buff,255,f)){
        p=strlwr(strtok(buff,separator));
        while(p!=NULL){
            n = list_search(&dict_lex, p);
            if(n==NULL){
             //   printf("Do you want to add the word \"%s\" to your data-base ?\n1 Yes\n2 No\n\n",p);

            }
            else{
                n->app++;
                list_search(&dict_len, p)->app++;
            }

            p=strlwr(strtok(NULL,separator));
        }
    }

    save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
    save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");
}

void update_words(){

    ///\fn void update_words()
    ///\brief Actualizeaza cuvintele aflate in dictionar
    ///
    ///Implementarea actualizarii cuvintelor aflate in dictionar dintr-un fisier dat de utilizator

    char fileName[100];
    List_Node *search, *new_node;
    system("cls");

    enterFileName:
    printf("\n\tPlease enter the name of the file (e.g. : fisier.txt):");
    fgets(fileName,99,stdin);
    fileName[strlen(fileName)-1]='\0';
    FILE *f = fopen(fileName,"r");
    if(f==NULL){
        printf("\nThe file \"%s\" doesn't exist!\n",fileName);
        goto enterFileName;
    }

    char buff[255];
    char separator[]=" ,./;'[]\<>?:\"{}|~!@#$%^&*()`";
    char *word;

    while(fgets(buff,255,f)){
        word=strlwr(strtok(buff,separator));
        while(word!=NULL){
           search = list_search(&dict_lex, word);
            if(search==NULL){
                new_node = (List_Node*)malloc(sizeof(List_Node));
                new_node->app = 0;
                new_node->word = (char*)malloc(sizeof(char)*strlen(word)+1);
                strcpy(new_node->word,word);
                list_insert(&dict_len,new_node);

                new_node = (List_Node*)malloc(sizeof(List_Node));
                new_node->app = 0;
                new_node->word = (char*)malloc(sizeof(char)*strlen(word)+1);
                strcpy(new_node->word,word);
                list_insert(&dict_lex,new_node);
            }
            else{
                search->app++;
                list_search(&dict_len, word)->app++;
            }

            word=strlwr(strtok(NULL,separator));
        }
    }


    sort_list_len(&dict_len);
    sort_list_lex(&dict_lex);

    save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
    save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");
}

void insert_word(){

    ///\fn void insert_word()
    ///\brief Inserarea unui cuvant nou.
    ///
    ///Implementarea inserarii unui cuvant nou in dictionar, Dupa inserare lista se reordoneaza si se salveaza

    char fileName[100];
    List_Node * new_node;
    List_Node * search;
    char word[50];

tryAgain:
    system("cls");
    printf("\n\tPlease enter the word");
    fgets(word,49,stdin);
    if(word[strlen(word)-1]='\n')
        word[strlen(word)-1]='\0';
    if(strlen(word)<=1)
        goto tryAgain;


    search=list_search(&dict_lex, word);
    if(search == NULL){
        new_node = (List_Node*)malloc(sizeof(List_Node));
        new_node->app = 0;
        new_node->word = (char*)malloc(sizeof(char)*strlen(word)+1);
        strcpy(new_node->word,word);
        list_insert(&dict_len,new_node);

        new_node = (List_Node*)malloc(sizeof(List_Node));
        new_node->app = 0;
        new_node->word = (char*)malloc(sizeof(char)*strlen(word)+1);
        strcpy(new_node->word,word);
        list_insert(&dict_lex,new_node);

        sort_list_len(&dict_len);
        sort_list_lex(&dict_lex);

        save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
        save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");


        printf("\nThis word is inserted to the disctionary");
        Sleep(1500);
    }
    else{
        printf("\nThis word is stored in the disctionary");
        Sleep(1500);
    }
}

void delete_word(){

    ///\fn void delete_word()
    ///\brief Stergerea unui cuvant din dictionar.
    ///
    ///Implementarea stergerii unui cuvant nou in dictionar, Dupa inserare lista se reordoneaza si se salveaza


    char fileName[100];
    List_Node * new_node;
    List_Node * search;
    char word[50];

    system("cls");

    printf("\n\tPlease enter the word");
    fgets(word,49,stdin);
    if(word[strlen(word)-1]=='\n')
        word[strlen(word)-1]='\0';


    search=list_search(&dict_lex, word);
    if(search == NULL){
        printf("\nThis word is not stored in the disctionary");
        Sleep(1500);
    }
    else{
        list_remove(&dict_len,search);
        list_remove(&dict_lex,search);

        save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
        save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");

        printf("\nThis word was deleted from the disctionary");
        Sleep(1500);
    }
}

void build_dict(){

    ///\fn void build_dict()
    ///\brief Construirea dictionarului.
    ///
    ///Implementarea construirii unui dictionar nou de cuvinte pornind de la un fisier ales de utilizator.


    char fileName[100];
    List_Node * new_node;
    List_Node * search;

    free_list(&dict_len);
    free_list(&dict_lex);

    system("cls");

    enterFileName:
    printf("\n\tPlease enter the name of the file (e.g. : file.txt):");
    fgets(fileName,99,stdin);
    fileName[strlen(fileName)-1]='\0';
    FILE *f = fopen(fileName,"r");
    if(f==NULL){
        printf("\nThe file \"%s\" doesn't exist!\n",fileName);
        goto enterFileName;
    }

    char buff[255];
    char separator[]=" ,./;'[]\<>?:\"{}|~!@#$%^&*()`";
    char *p;

    while(fgets(buff,255,f)){
        p=strlwr(strtok(buff,separator));
        while(p!=NULL){
            search=list_search(&dict_lex, p);
            if(search == NULL){
                new_node = (List_Node*)malloc(sizeof(List_Node));
                new_node->app = 0;
                new_node->word = (char*)malloc(sizeof(char)*strlen(p)+1);
                strcpy(new_node->word,p);
                list_insert(&dict_len,new_node);

                new_node = (List_Node*)malloc(sizeof(List_Node));
                new_node->app = 0;
                new_node->word = (char*)malloc(sizeof(char)*strlen(p)+1);
                strcpy(new_node->word,p);
                list_insert(&dict_lex,new_node);
            }
            else{
                search->app++;
                list_search(&dict_len, p)->app++;
            }

            p=strlwr(strtok(NULL,separator));
        }
    }

    sort_list_len(&dict_len);
    sort_list_lex(&dict_lex);

    save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
    save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");
}

void reset_dict(){

    ///\fn void reset_dict()
    ///\brief Resetarea dictionarului.
    ///
    ///Implementarea resetarii dictionarului prin intermediul eliberarii memoriei alocate listei ce il contine.


    free_list(&dict_len);
    free_list(&dict_lex);

    save_dictionary(&dict_lex,"dictionary/wordsEnLex.txt");
    save_dictionary(&dict_len,"dictionary/wordsEnLen.txt");
}
