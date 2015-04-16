#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "levenshtein.h"
#include <stdbool.h>
#include <windows.h>

// la fiecare declarare de variabile de tip List a se va atribui nume_var.head=NULL!!!

int main() {
    char word[]="CAFEA";
    int changes = 1;

    printf(" Lista originala de cuvinte :\n");
    List l_dict = load_dictionary("dictionary/text3.txt",false);
    print_dictionary( l_dict.head, l_dict.tail );
    getchar();

    printf("\n\n Lista cuvinte ordonata dupa lungimea cuvintelor:\n");
    sort_list_len(&l_dict);
    print_dictionary( l_dict.head, l_dict.tail );
    getchar();

    printf("\n\n Lista indexarilor dupa lungimea cuvintelor:\n");
    int i, max_len=0;
    List_Node* ind_len[40];
    index_len(&l_dict, ind_len, &max_len);
    for(i=1;i<=max_len;i++){
        printf(" %d - ", i );
        if(ind_len[i]!=NULL)
            printf("%s\n", ind_len[i]->word);
        else
            printf("  NULL\n");
    }
    getchar();

    printf("lista cuvintelor a fost salvata in fisierul list_sort_len.txt\n\n");
    save_list(&l_dict, "list_sort_len.txt");
    getchar();

    printf("\n\n Lista cuvinte ordonata lexicografic:\n");
    sort_list_lex(&l_dict);
    print_dictionary( l_dict.head, l_dict.tail );
    getchar();

    printf("\n\n Lista indexarilor lexicografice:\n");
    List_Node* ind_lex[27];
    index_lex(&l_dict, ind_lex);
    for(i=0;i<26;i++){
        printf(" %c - ",(char)(i+97));
        if( ind_lex[i] != NULL )
            printf(" %s \n", ind_lex[i]->word );
        else
            printf("Nu exista nici un cuvant care sa inceapa cu %c\n",(char)(i+97));
    }
    getchar();

    printf("\n\n Lista cuvintelor asemanatoare cu cuvantul \"%s\" cu maxim %d modificare/i:\n", word, changes);
    List sim_words;
    sim_words.head=NULL;
    sim_words = find_similar_words(word, changes, l_dict.head, l_dict.tail);
    print_list(sim_words.head, sim_words.tail);
    getchar();

    getchar();
    return 0;
}

