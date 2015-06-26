///\file dictionary.h
///\brief Biblioteca C pentru dictionarul de cuvinte.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -salvarea dictionarului intr-un fisier
* -eliberarea memoriei listei ce contine dictionarul
* -incarcarea dictionarului
*/


#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#include <stdbool.h> ///> printf()
#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()

void free_list(List * dict);
void load_dictionaries();
List load_dictionary(char file_name[], bool eliminate_duplicates );
void save_dictionary(List* l, char file_name[]);

#endif // DICTIONARY_H_INCLUDED
