///\file list.h
///\brief Biblioteca C pentru listele si operatiile cu liste.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -afisarea pe ecran si salvarea unei liste intr-un fisier
* -inserarea si stergerea unui element
* -sortarea unei liste lexicografic si dupa numarul de caractere al unui element
* -salvarea unor noduri speciale(ex: primul nod al nodurilor ce incep cu litera "d" sau au dimensiunea 3)
*/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdbool.h> ///> printf()


typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    char *word;
    int app;

} List_Node;
typedef struct list {
    struct list_node *head;
    struct list_node *tail;
} List;

List dict_lex;
List_Node * ind_lex[26];
List dict_len;
List_Node * ind_len[40];
int max_len;

void index_lex(List* l, List_Node* index[] );
void index_len(List* l, List_Node* index[], int* max_len );
void sort_list_len( List *l );
void sort_list_lex( List *l );
List_Node* list_search(List *l, char *k);
void list_insert(List *l, List_Node *x);
void list_remove(List *l, List_Node *x);
void save_list(List* l, char file_name[]);
void print_list( List_Node* start, List_Node* stop);

#endif // LIST_H_INCLUDED
