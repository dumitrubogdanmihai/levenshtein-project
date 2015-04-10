#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "levenshtein.h"

int main() {
    int i=0,lev=-1;
    char buffer[255];
    char word[80]="CARNEALA";
    List l;
    List_Node *n = NULL;
    l.head = NULL;
    l.tail = NULL;

    FILE *f=fopen("dictionary/rodex.txt","r");
    while(fgets(&buffer,255,f)){
        if( buffer[strlen(buffer)-1] == '\n' )
            buffer[strlen(buffer)-1] ='\0';
        // pentru unica aparitie a fiecarui cuvant
        //if( listSearch(&l,&buffer)==NULL ){
            n = (List_Node*) malloc(sizeof(List_Node));
            n->word = malloc(sizeof(buffer));
            strcpy(n->word,buffer);
            list_insert(&l,n);
        //}
    }
    printf("Cuvintele au fost incarcate din fisier! \n\n\n");
    print_list(l,'a');
    sort_list_len(&l);
    print_list(l,'a');

    List_Node *x;
    x = l.head;
    while ( x!=NULL ) {
        lev = leven1(word, strlen(word), x->word, strlen(x->word));
        assert(lev>=0);
        if( lev <= 1){
            printf("%d - %s",lev , x->word );
        }
        //sprintf("%s cu %d \n\n",x->word,lev);
        x = x->next;
    }
    printf("\n\nS-a executat functia lev pt toate cuvintele!");

    fclose(f);
    getchar();
    return 0;
}

