#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdbool.h>

typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    char *word;
    char *type;
    int code;
    char *restr;
} List_Node;

typedef struct list {
    struct list_node *head;
    struct list_node *tail;
} List;



List load_dictionary(char file_name[], bool eliminate_duplicates );
List_Node* listSearch(List *l, char *k);
void index_lex(List* l, List_Node* index[] );
void index_len(List* l, List_Node* index[], int* max_len );
//sorteaza dupa numarul de caractere cu insertion sort
void sort_list_len( List *l );
//sorteaza lexicografic lista cu insertion sort
void sort_list_lex( List *l );
void list_insert(List *l, List_Node *x);
void list_remove(List *l,List_Node *x);
void print_list(List l, char *ord);

#endif // LIST_H_INCLUDED
