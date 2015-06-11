#ifndef LEVENSHTEIN_H_INCLUDED
#define LEVENSHTEIN_H_INCLUDED
#include "list.h"
//List find_similar_words( char word[], int changes, List_Node *start, List_Node *stop );
void find_similar_words(List* l_sim, char word[], int changes, List_Node *start, List_Node *stop );

#endif // LEVENSHTEIN_H_INCLUDED
