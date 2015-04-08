#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "levenshtein.h"

int main() {
    int i=0,lev=-1;
    char buffer[255];
    char word[80]="CEAW";
    List l;
    list_node *n = NULL;
    l.head = NULL;

    FILE *f=fopen("cuvinte.txt","r");
    while(fgets(&buffer,255,f)){

        // pentru unica aparitie a fiecarui cuvant
        //if( listSearch(&l,&buffer)==NULL ){
            n = (list_node*) malloc(sizeof(list_node));
            n->word = malloc(sizeof(buffer));
            strcpy(n->word,buffer);
            list_insert(&l,n);
        //}
    }


    printf("Cuvintele au fost incarcate din fisier! \n\n\n");

    list_node *x;
    x = l.head;
    while ( x!=NULL ) {
        lev = leven1(word, strlen(word), x->word, strlen(x->word));
        assert(lev>=0);
        if( lev <= 1){
            printf("%d - %s",lev , x->word );
            //break;
        }
     //printf("%s cu %d \n\n",x->word,lev);
        x = x->next;
    }
    printf("\n\nS-au cautat toate cuvintele!");

    fclose(f);
    getchar();
}

