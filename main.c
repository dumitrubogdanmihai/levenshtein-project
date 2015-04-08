#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "levenshtein.h"


int main() {
    int i=0,lev;
    char buffer[255];
    char cmdLine[80];
    char cuvanttt[80]="CEAW";
    List l;
    ListNode *n = NULL;
    l.head = NULL;


    FILE *f=fopen("cuvinte.txt","r");
    while(fgets(&buffer,255,f)){
        //if( listSearch(&l,&buffer)==NULL ){
            n = (ListNode*) malloc(sizeof(ListNode));
            n->word = malloc(sizeof(buffer));
            strcpy(n->word,buffer);
            listInsert(&l,n);
        //}
    }

printf("Cuvintele au fost incarcate din fisier! \n\n\n");

    ListNode *x;
    x = l.head;
    while ( x!=NULL ) {
        lev = leven1(cuvanttt, strlen(cuvanttt), x->word, strlen(x->word));
        if( lev <= 1){
            printf("%d - %s",lev , x->word );
            //break;
        }
     //printf("%s cu %d \n\n",x->word,lev);
        x = x->next;
    }
    printf("\n\nS-au cautat toate cuvintele!");
    getchar();
}
