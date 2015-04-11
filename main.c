#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "levenshtein.h"
#include <stdbool.h>
#include <windows.h>

// la fiecare declarare de varibial tip List a se atribui nume_var.head=NULL!!!

int main() {
    char word[]="PASTA";
    char dict_path[]="dictionary/text.txt";
    int changes = 1;

    List l_dict;
    l_dict.head=NULL;

    List sim_words;
    sim_words.head=NULL;

    l_dict = load_dictionary(dict_path,false);
    printf("\tLista cuvinte originala:\n");
    print_list(l_dict,(char*)'a');

    sort_list_len(&l_dict);
    printf("\n\n\tLista cuvinte ordonata:\n");
    print_list(l_dict,(char*)'a');

    sim_words = find_similar_words(word, changes, l_dict.head, l_dict.tail);
    printf("\n\n\tLista cuvintelor asemanatoare cu \"%s\" cu maxim %d modificari:\n", word, changes);
    print_list(sim_words,(char*)'a');

    getchar();
    return 0;
}

