#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "levenshtein.h"
#include <stdbool.h>

int main() {
    char word[80]="CERNEALA";

    int changes = 1;
    List l;
    List similar_words;
    l.head = NULL;
    l.tail = NULL;
    similar_words.head = NULL;
    similar_words.tail = NULL;

    load_dictionary(&l,"dictionary/rodex.txt",false);
    printf("originala:\n");
    print_list(l,'a');

    sort_list_len(&l);
    printf("ordonata:\n");
    print_list(l,'a');

    similar_words = find_similar_words(&l, word, changes);
    printf("lev:\n");
    print_list(similar_words,'a');
//
//    List_Node *x;
//    x = l.head;
//    while ( x!=NULL ) {
//        lev = leven1(word, strlen(word), x->word, strlen(x->word));
//        assert(lev>=0);
//        if( lev <= 1){
//            printf("%d - %s",lev , x->word );
//        }
//        //sprintf("%s cu %d \n\n",x->word,lev);
//        x = x->next;
//    }    printf("\n\nS-a executat functia lev pt toate cuvintele!");

    getchar();
    return 0;
}

