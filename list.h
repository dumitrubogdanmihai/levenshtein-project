#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdbool.h>

typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    char *word;
    char *type;        //ce parte de vorbire este
    int code;          //codul flexionarii
    char *restr;       //reprezinta restrictiile de felexionare
} List_Node;
typedef struct list {
    struct list_node *head;
    struct list_node *tail;
} List;

List load_words(char file_name[], bool eliminate_duplicates );
List load_dictionary(char file_name[], bool eliminate_duplicates );
List_Node* listSearch(List *l, char *k);
void index_lex(List* l, List_Node* index[] );
void index_len(List* l, List_Node* index[], int* max_len ) ;
//void sort_list_len( List *l );
void sort_list_lex( List *l );

// limitele start si stop nu functioneaza corect in toate cazurile
void sort_list_len( List *l, List_Node* start, List_Node* stop );
void list_insert(List *l, List_Node *x) ;
void list_remove(List *l, List_Node *x) ;
void save_list(List* l, char file_name[]) ;
void save_dictionary(List* l, char file_name[]) ;
void print_list( List_Node* start, List_Node* stop) ;
void print_dictionary( List_Node* start, List_Node* stop);

#endif // LIST_H_INCLUDED
