#include "list.h"
#include <stdio.h>

ListNode* listSearch(List *l, char *k) {
    ListNode *x;
    x = l->head;
    while ( x!=NULL && strcmp(x->word,k)!=0 ) {
        x = x->next;
    }
    return x;
}

void listInsert(List *l, ListNode *x) {
    x->next = l->head;
    if (l->head != NULL) {
        l->head->prev = x;
    }
    l->head = x;
    x->prev = NULL;
}

void listRemove(List *l,ListNode *x) {
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

void printList(List l) {
    ListNode *n;
    n = l.head;
    printf("Elementele listei sunt : ");
    while (n != NULL) {
        printf("%s ",n->word);
        n = n->next;
    }
    printf("\n");
}
