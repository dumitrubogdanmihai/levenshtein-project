#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "levenshtein.h"
#include <stdbool.h>

int main() {
    char word[80]="cafea";
    char dict_path[]="dictionary/text.txt";
    int changes = 2;
    List l_dict;
    List sim_words;
    l_dict.head = NULL;
    l_dict.tail = NULL;
    sim_words.head = NULL;
    sim_words.tail = NULL;

    l_dict = load_dictionary(dict_path,false);

    printf("\tLista cuvinte originala:\n");
    print_list(l_dict,'a');

    sort_list_len(&l_dict);
    printf("\n\n\tLista cuvinte ordonata:\n");
    print_list(l_dict,'a');

    sim_words = find_similar_words(&l_dict, word, changes);
    printf("\n\n\tLista cuvintelor asemanatoare cu \"%s\" cu maxim %d modificari:\n", word, changes);
    print_list(sim_words,'a');

    getchar();
    return 0;
}

