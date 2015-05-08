#include "list.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

void build_dictionaries(){ // pe viitor functia aceasta ar fi bine sa o mutam in list.c
    l_dict_lex = load_words("dictionary/wordsEnLex.txt",false);
    index_lex(&l_dict_lex, ind_lex);

    l_dict_len = load_words("dictionary/wordsEnLen.txt",false);
    index_len(&l_dict_len, ind_len, &max_len);
}

List load_words(char file_name[], bool eliminate_duplicates ){
    List l;
    l.head =NULL;
    char buffer[255];
    FILE *f=fopen(file_name,"r");
    List_Node *n = NULL;          // n reprezinta noul nod al listei

    if(eliminate_duplicates){ // pentru rapiditatea citirii datelor am scos acest if in afara while-ului
        while(fgets(buffer,255,f)){
            if( listSearch(&l,buffer)==NULL ){
                if(buffer[strlen(buffer)-1]=='\n')
                    buffer[strlen(buffer)-1]='\0';
                n = (List_Node*) malloc(sizeof(List_Node));
                n->word = (char *)  malloc(sizeof(buffer));
                strcpy(n->word,buffer);
                list_insert(&l,n);
            }
        }
    }
    else{
         while(fgets(buffer,255,f)){
            if(buffer[strlen(buffer)-1]=='\n')
                buffer[strlen(buffer)-1]='\0';
            n = (List_Node*) malloc(sizeof(List_Node));
            n->word = (char *)  malloc(sizeof(buffer));
            strcpy(n->word,buffer);
            list_insert(&l,n);
        }
    }
    fclose(f);
    return l;
}
List load_dictionary(char file_name[], bool eliminate_duplicates ){ // doar pt limba romana
    List l;
    l.head =NULL;
    List_Node *n = NULL;

    char buffer[255]; //in buffer se va salva fiecare linie din fisier
    char* p;    // p va reprezenta un pointer la fiecare element din buffer

    FILE* f=fopen(file_name,"r");
    assert(f!=NULL);

    while(fgets(buffer,255,f)){
        if(buffer[ strlen(buffer)-1] == '\n')
           buffer[strlen(buffer)-1] = '\0';
//        puts("______________________________________________________");
//        puts("______________________________________________________");
//        printf("\tbuffer : \"%s\"\n",buffer);

        n = (List_Node*) malloc( sizeof(List_Node) );

        p=strtok(buffer," \t\n");
if(p!=NULL){
//        printf("p-word:   \"%s\"   len:%d\n", p,strlen(p));
        n->word = (char *) malloc( sizeof(char)*strlen(p)+1 );
        strcpy( n->word, p);
//        printf("n->word=\"%s\"   len:%d\n\n",n->word,strlen(n->word));
}

        p=strtok(NULL," \t\n");
if(p!=NULL){
//        printf("p-type:   \"%s\"   len:%d\n", p,strlen(p));
        n->type = (char *)  malloc( sizeof(char)*strlen(p)+1 );
        strcpy(n->type, p);
//        printf("n->type= \"%s\"   len:%d\n\n",n->type, strlen(n->type));
}

        p=strtok(NULL," \t\n");
if(p!=NULL){
        int aux=atoi(p);
//        printf("p-type:   \"%s\"   len:%d\n", p, strlen(p));
//        printf("atoi(p):   \"%d\" \n", aux);
        n->code = aux;
//        printf("n->code= \"%d\"\n\n",n->code);
}

        p=strtok(NULL," \t\n");

if(p!=NULL){
//        printf("p-type:   \"%s\"   len:%d\n", p, strlen(p));
            n->restr = (char *) malloc(sizeof(char)*strlen(p)+1 );
            strcpy(n->restr, p);
//            printf("n->restr= \"%s\"   len:%d\n",n->restr,strlen(n->restr));
        }
        else{
            n->restr = NULL;
        }

//        printf("\n");

        list_insert(&l,n);
    }
    fclose(f);
    return l;
}

void index_lex(List* l, List_Node* index[] ) {
    int k;
    char last_ch=NULL;
    List_Node *i = l->head;

    for(k=0;k<=25;k++){
        index[k]=NULL;
    }

    while ( i!=NULL ) {
        if(last_ch != i->word[0] ){
            last_ch = i->word[0];
            index[ (int)(tolower(last_ch))-97 ] = i;
        }
        i = i->next;
    }
}
void index_len(List* l, List_Node* index[], int* max_len ) {
    int len;
    int k;
    int last_len=0;
    List_Node *i = l->head;

    for(k=0;k<=39;k++){
        index[k]=NULL;
    }

    while ( i!=NULL ) {
        len = strlen(i->word);
        if(  len != last_len ){
            index[ len ] = i;
            *max_len = len;
            last_len = len;
        }
        i = i->next;
    }
}

// sorteaza !!!TOATA!!! lista, indiferent de ce parametrii primeste prin start si stop
void sort_list_len( List *l, List_Node* start, List_Node* stop ){//sorteaza dupa lungimea cuvintelor lista cu insertion sort
    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    key = start->next;

//    while( (key != NULL) && (key!= (stop->next)) ){
    while( key != NULL ){
        key_next = key->next;
        printf("%c\n",key->word[0]);
        i = key->prev;
        while( i!=NULL  &&  ( strlen(key->word) < strlen(i->word) )  ){
            i = i->prev;
        }
        if(key->prev != i){
            if(i==NULL){
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->prev != NULL)
                    key->prev->next = key->next;
                if(key->next != NULL)
                    key->next->prev = key->prev;
                key->next = l->head;
                key->prev = NULL;
                l->head->prev = key;
                l->head = key;
            }
            else{
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->next != NULL)
                    key->next->prev = key->prev;
                if(key->prev != NULL)
                    key->prev->next = key->next;
                key->next = i->next;
                if(i->next != NULL)
                    i->next->prev = key;
                i->next = key;
                key->prev = i;
            }
        }
    key = key_next;
    }
}
void sort_list_lex( List *l ){//sorteaza lexicografic lista cu insertion sort
    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = key->prev;
        while( i!=NULL  &&  ( strcmp(key->word, i->word) < 0 )  ){
            i = i->prev;
        }
        if(key->prev != i){
            if(i==NULL){
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->prev != NULL)
                    key->prev->next = key->next;
                if(key->next != NULL)
                    key->next->prev = key->prev;
                key->next = l->head;
                key->prev = NULL;
                l->head->prev = key;
                l->head = key;
            }
            else{
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->next != NULL)
                    key->next->prev = key->prev;
                if(key->prev != NULL)
                    key->prev->next = key->next;
                key->next = i->next;
                if(i->next != NULL)
                    i->next->prev = key;
                i->next = key;
                key->prev = i;
            }
        }

    key = key_next;
    }
}

List_Node* listSearch(List *l, char *k) {
    List_Node *x;
    x = l->head;
    while ( x!=NULL && strcmp(x->word,k)!=0 ) {
        x = x->next;
    }
    return x;
}
void list_insert(List *l, List_Node *x) {
    if(l->head==NULL){
        l->head = x;
        l->tail= x;
        l->head->next=NULL;
        l->tail->next=NULL;
        l->head->prev=NULL;
        l->tail->prev=NULL;
    }
    else{
        x->next = NULL;
        x->prev = l->tail;
        l->tail->next = x;
        l->tail = x;
    }
}
void list_remove(List *l, List_Node *x) {
    if (x->prev != NULL) {
        x->prev->next = x->next;
    }
    else {
        l->head = x->next;
    }
    if (x->next != NULL) {
        x->next->prev = x->prev;
    }
    else {
        l->tail = x->prev;
    }
    free(x);
}

void save_list(List* l, char file_name[]) {
    List_Node *i=l->head;

    char file_path[100]="\dictionary\\";
    strcat(file_path,file_name);
    FILE* f=fopen(file_path, "w");
    assert(f!=NULL);

    while (i != NULL) {
        fprintf(f,"%s\n",i->word);
        i = i->next;
    }
    fclose(f);
}
void save_dictionary(List* l, char file_name[]) {
    List_Node *i=l->head;

    char file_path[100]="\dictionary\\";
    strcat(file_path,file_name);
    FILE* f=fopen(file_path, "w");
    assert(f!=NULL);

    while (i != NULL) {
        fprintf(f,"%s\t %s\t %d\t %s\n", i->word, i->type, i->code, i->restr );
        i = i->next;
    }
    fclose(f);
}

void print_list( List_Node* start, List_Node* stop) {
    if(start == NULL){
        printf(" Lista este vida!\n");
    }
    else{
        List_Node *n;
        printf(" Elementele listei sunt : \n");

        n = start;
        while (n != stop->next) {
            printf("  %s\n",n->word);
            n = n->next;
        }
    }
}
void print_dictionary( List_Node* start, List_Node* stop) {
    if(start == NULL){
        printf(" Lista este vida!\n");
    }
    else{
        List_Node *n;
        printf(" Elementele listei sunt : \n");

        n = start;

        while (n != stop->next) {
            printf(" %s\t %s\t %d\t %s\n",n->word, n->type, n->code, n->restr );
            n = n->next;
        }
    }
}
