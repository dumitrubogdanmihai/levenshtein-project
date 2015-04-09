#include "list.h"
#include <stdio.h>

List_Node* listSearch(List *l, char *k) {
    List_Node *x;
    x = l->head;
    while ( x!=NULL && strcmp(x->word,k)!=0 ) {
        x = x->next;
    }
    return x;
}

//sorteaza lexicografic lista cu insertion sort
void sort_list_lex( List *l ){
    List_Node *i;
    List_Node *key;
    List_Node *key_next, *key_prev;
    key = l->head;
    key_next = key->next;

    while( key != NULL){
        i = l->head;
        printf("%s - ", i->word);
        while( strcmp(key->word,i->word) > 0 || key_next!=NULL || i!=key){
            printf("%s !!!\n\n", i->word);
            i = i->next;
        }
        key->next= i;
        if(i->prev != NULL)
            i->prev->next=key;
        i->prev = key;

key_next = key->next;
key_prev = key->prev;

        key->next->prev = key_prev;
        key->prev->next = key_next;
    }
}

void list_insert(List *l, List_Node *x) {
    x->next = l->head;
    if (l->head != NULL) {
        l->head->prev = x;
    }
    l->head = x;
    x->prev = NULL;
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
}

void print_list(List l) {
    List_Node *n;
    n = l.head;
    printf("Elementele listei sunt : ");
    while (n != NULL) {
        printf("%s ",n->word);
        n = n->next;
    }
    printf("\n");
}
