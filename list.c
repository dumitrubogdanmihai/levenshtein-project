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
