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
    char word[]="CAFEA";
    char dict_path[]="dictionary/text.txt";
    int changes = 1;

    List l_dict;
    l_dict.head=NULL;

    List sim_words;
    sim_words.head=NULL;


    l_dict = load_dictionary(dict_path,false);
    printf(" Lista cuvinte originala:\n");
    print_list(l_dict,(char*)'a');


    List_Node* ind_lex[27];
    index_lex(&l_dict, ind_lex);
    printf("\n\n Lista indexarilor lexicografice:\n");
    int i;
    for(i=0;i<26;i++){
        printf(" %c - ",(char)(i+97));
        if( ind_lex[i] != NULL )
            printf(" %s \n", ind_lex[i]->word );
        else
            printf("Nu exista nici un cuvant care sa inceapa cu %c\n",(char)(i+97));
    }


    sort_list_len(&l_dict);
    printf("\n\n Lista cuvinte ordonata:\n");
    print_list(l_dict,(char*)'a');

    save_list(&l_dict, "list_sort_len.txt");


    int max_len=0;
    List_Node* ind_len[40];
    index_len(&l_dict, ind_len, &max_len);
    printf("\n\n Lista indexarilor dupa lungimea cuvintelor:\n");
    for(i=1;i<=max_len;i++){
        printf(" %d - ", i );
        if(ind_len[i]!=NULL)
            printf("%s\n", ind_len[i]->word);
        else
            printf("  NULL\n");
    }


    sim_words = find_similar_words(word, changes, l_dict.head, l_dict.tail);
    printf("\n\n Lista cuvintelor asemanatoare cu cuvantul \"%s\" cu maxim %d modificare/i:\n", word, changes);
    print_list(sim_words,(char*)'a');


    getchar();
    return 0;
}

