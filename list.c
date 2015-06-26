///\file list.c
///\brief Biblioteca C pentru implementarea listelor si operatiilor cu liste.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -afisarea pe ecran si salvarea unei liste intr-un fisier
* -inserarea si stergerea unui element
* -sortarea unei liste lexicografic si dupa numarul de caractere al unui element
* -salvarea unor noduri speciale(ex: primul nod al nodurilor ce incep cu litera "d" sau au dimensiunea 3)
*/

#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include <stdio.h> ///> printf()
#include <stdlib.h> ///> malloc()
#include <string.h> ///> strlen(),tolower()
#include <assert.h> ///> assert()
#include <windows.h> ///> printf()

void index_lex(List* l, List_Node* index[] ) {

    ///\fn void index_lex(List* l, List_Node* index[] )
    ///\brief Memoreaza cate un pointer la fiecare schimbare a literei.
    ///\param l Variabila de tip List ce reprezinta lista
    ///\param index Variabila de tip List_Node
    ///
    ///Implementarea memorarii unui pointer la fiecare schimbare a literei de inceput a cuvintelor.


    int k,j;
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


    ///\fn void index_len(List* l, List_Node* index[], int* max_len )
    ///\brief Memoreaza cate un pointer la fiecare schimbare dimensiunii unui nod al listei.
    ///\param l Variabila de tip List ce reprezinta lista
    ///\param index Variabila de tip List_Node
    ///\param max_len Variabila de tip intreg
    ///
    ///Implementarea memorarii unui pointer la fiecare schimbare a dimensiunii unui cuvant.


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

void sort_list_len( List *l ){//sorteaza dupa lungimea cuvintelor lista cu insertion sort

    ///\fn void sort_list_len( List *l )
    ///\brief Sorteaza lista dupa dimensiunea elementelor.
    ///\param l Variabila de tip List ce reprezinta lista
    ///
    ///Implementarea sortarii unei liste dupa dimensiunea elementelor folosind "Insertion Sort".


    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    key = l->head;

//    while( (key != NULL) && (key!= (stop->next)) ){
    while( key != NULL ){
        key_next = key->next;
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

    ///\fn void sort_list_lex( List *l )
    ///\brief Sorteaza lista lexicografic.
    ///\param l Variabila de tip List ce reprezinta lista
    ///
    ///Implementarea sortarii unei liste lexicografic folosind "Insertion Sort".


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

List_Node* list_search(List *l, char *k) {

    ///\fn List_Node* list_search(List *l, char *k)
    ///\brief Cautarea unui element intr-o lista.
    ///\param l Variabila de tip List
    ///\param k Variabila de tip char ce reprezinta nodul cautat in lista
    ///
    ///Implementarea cautarii unui element intr-o lista.


    register List_Node *x;
    x = l->head;
    while ( x!=NULL && strcmp(x->word,k)!=0 ) {
        x = x->next;
    }
    return x;
}

void list_insert(List *l, List_Node *x) {

    ///\fn void list_insert(List *l, List_Node *x)
    ///\brief Inserarea unui element intr-o lista.
    ///\param l Variabila de tip List
    ///\param x Variabila de tip List_Node ce reprezinta nodul ce trebuie introdus in lista
    ///
    ///Implementarea inserarii unui element intr-o lista.


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

    ///\fn void list_remove(List *l, List_Node *x)
    ///\brief Stergerea unui element intr-o lista.
    ///\param l Variabila de tip List
    ///\param x Variabila de tip List_Node ce reprezinta nodul pe care doril sa il stergem din lista
    ///
    ///Implementarea stergerii unui element intr-o lista.


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
    free(x->word);
    free(x);
}

void save_list(List* l, char file_name[]) {

     ///\fn void save_list(List* l, char file_name[])
    ///\brief Salvarea listei.
    ///\param l Variabila de tip List
    ///\param file_name Variabila de tip char
    ///
    ///Implementarea salvarii unei liste intr-un fisier.


    register List_Node *i=l->head;

    FILE* f=fopen(file_name, "w");
    assert(f!=NULL);

    while (i != NULL) {
        fprintf(f,"%s\n",i->word);
        i = i->next;
    }
    fclose(f);
}

void print_list( List_Node* start, List_Node* stop) {

    ///\fn void print_list( List_Node* start, List_Node* stop)
    ///\brief Afisarea unui interval al unei liste.
    ///\param start Variabila de tip List_Node ce reprezinta nodul de start al afisarii
    ///\param stop Variabila de tip List_Node ce reprezinta nodul de sfarsit al afisarii
    ///
    ///Implementarea afisarii unui interval al unei liste specificat prin parametrii.

    if(start == NULL){
        printf(" Vid list!\n");
    }
    else{
        register List_Node *n;

        n = start;
        while (n!=NULL && n != stop->next ) {
            printf("      %s \n",n->word);
            n = n->next;
        }

    }
}

