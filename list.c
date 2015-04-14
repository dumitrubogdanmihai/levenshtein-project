#include "list.h"
#include <stdio.h>
#include <string.h>

List load_dictionary(char file_name[], bool eliminate_duplicates ){
    List l;
    l.head =NULL;
    char buffer[255];
    FILE *f=fopen(file_name,"r");
    List_Node *n = NULL;
    while(fgets(buffer,255,f)){
        if( buffer[strlen(buffer)-1] == '\n' )
            buffer[strlen(buffer)-1] ='\0';
        //next time use short-circuit property
        // pentru unica aparitie a fiecarui cuvant
        if(eliminate_duplicates){
            if( listSearch(&l,buffer)==NULL ){
                n = (List_Node*) malloc(sizeof(List_Node));
                n->word = (char *)  malloc(sizeof(buffer));
                strcpy(n->word,buffer);
                list_insert(&l,n);
            }
        }
        else{
                n = (List_Node*) malloc(sizeof(List_Node));
                n->word = (char *)  malloc(sizeof(buffer));
                strcpy(n->word,buffer);
                list_insert(&l,n);
        }
    }
    fclose(f);
    return l;
}

List_Node* listSearch(List *l, char *k) {
    List_Node *x;
    x = l->head;
    while ( x!=NULL && strcmp(x->word,k)!=0 ) {
        x = x->next;
    }
    return x;
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

//sorteaza dupa numarul de caractere cu insertion sort
void sort_list_len( List *l ){
    List_Node *i;
    List_Node *key;
    List_Node *key_next;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        // a se porni de la key->prev; pentru a avea o sortare rapida in situatia in care sunt majoritatea elementelor sortate
        i = l->head;
        while( ( strlen(key->word) > strlen(i->word) )  && i!=key){
       // while( strcmp(i->word,key->word) < 0  && i!=key){
            i = i->next;
        }

        //key porneste de la head.next deci este imposibil ca prev sa fie NULL deci nu are nevoie de if
        if(key!=i){

            if(key->next==l->tail){
                l->tail = key->prev;
            }

            if(i->prev!=NULL)
                i->prev->next = key;
            else
                l->head = key;

            if(key->next!=NULL)
                key->next->prev = key->prev;

            if(key->prev!=NULL)
                key->prev->next = key->next;

            key->prev = i->prev;
            key->next = i;
            i->prev = key;
        }

    key = key_next;
    }
}

//sorteaza lexicografic lista cu insertion sort
void sort_list_lex( List *l ){
    List_Node *i;
    List_Node *key;
    List_Node *key_next;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = l->head;
        while( strcmp(i->word,key->word) < 0  && i!=key){
            i = i->next;
        }

        //key porneste de la head.next deci este imposibil ca prev sa fie NULL deci nu are nevoie de if
        if(key!=i){

            if(key->next==l->tail){
                l->tail = key->prev;
            }

            if(i->prev!=NULL)
                i->prev->next = key;
            else
                l->head = key;

            if(key->next!=NULL)
                key->next->prev = key->prev;

            if(key->prev!=NULL)
                key->prev->next = key->next;

            key->prev = i->prev;
            key->next = i;
            i->prev = key;
        }

    key = key_next;
    }
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

void list_remove(List *l,List_Node *x) {
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
    while (i != NULL) {
        fprintf(f,"%s\n",i->word);
        i = i->next;
    }
    fclose(f);
}

void print_list(List l, char *ord) {
    if(l.head == NULL){
        printf(" Lista este vida!\n");
    }
    else{
        List_Node *n;
        if(ord=='a'){
                n = l.head;
                printf(" Elementele listei sunt : \n");
                while (n != NULL) {
                    printf("   %s\n",n->word);
                    n = n->next;
                }
        }
        else{
                n = l.tail;
                printf(" Elementele listei sunt : \n");
                while (n != NULL) {
                    printf("   %s\n",n->word);
                    n = n->prev;
                }
        }
    }
}
