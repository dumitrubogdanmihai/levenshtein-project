#ifndef LEVENSHTEIN_H_INCLUDED
#define LEVENSHTEIN_H_INCLUDED
#include "list.h"

int sugg_funct;
void find_sim_words(List* l_sim, char word[], int changes, List_Node *start, List_Node *stop );

#endif // LEVENSHTEIN_H_INCLUDED
