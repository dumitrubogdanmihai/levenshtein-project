#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    char *word;
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

#endif // LIST_H_INCLUDED
