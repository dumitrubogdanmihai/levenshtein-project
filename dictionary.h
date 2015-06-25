#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#include <stdbool.h>
#include "list.h"

void free_dict(List * dict);
void load_dictionaries();
List load_dictionary(char file_name[], bool eliminate_duplicates );
void save_dictionary(List* l, char file_name[]);

#endif // DICTIONARY_H_INCLUDED
