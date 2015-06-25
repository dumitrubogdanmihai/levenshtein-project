///\file levenshtein.h
///\brief Biblioteca C pentru  .
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
*/


#ifndef LEVENSHTEIN_H_INCLUDED
#define LEVENSHTEIN_H_INCLUDED
#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()

int sugg_funct;
void find_sim_words(List* l_sim, char word[], int changes, List_Node *start, List_Node *stop );

#endif // LEVENSHTEIN_H_INCLUDED
