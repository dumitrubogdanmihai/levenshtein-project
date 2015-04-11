#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdbool.h>

typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    const char *word;
} List_Node;
// *** litere mari pt a semnala ca este un tip de date

typedef struct list {
    struct list_node *head;
    struct list_node *tail;
} List;

List_Node* listSearch(List *l,char *k);
void list_insert(List *l, List_Node *x);
void list_remove(List *l, List_Node *x);
void print_list(List l, char *ord);
void sort_list_lex( List *l );
void sort_list_len( List *l );
List load_dictionary(char file_name[], bool eliminate_duplicates );

#endif // LIST_H_INCLUDED
