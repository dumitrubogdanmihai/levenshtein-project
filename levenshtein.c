#include "list.h"
#include<stdio.h>
#include<string.h>
#include <assert.h>

int min_val(int a, int b, int c) {
    if(a < b){
        if(a < c)
            return a;
        else
            return c;
    }
    else{
        if(b < c)
            return b;
        else
            return c;
    }
}

// iterativ
int leven1( char *a, unsigned int lena, char *b, unsigned int lenb ){
    unsigned int m[50][50];
    int i,j;
//    int k,l;

    for(i=0;i<lena;i++)
        m[i][0]=i;
    for(j=0;j<lenb;j++)
        m[0][j]=j;

    for(i=0;i<lena-1;i++){
        for(j=0;j<lenb-1;j++){
            if(a[i]==b[j]){
                m[i+1][j+1]=m[i][j];
            }
            else{
                m[i+1][j+1]=min_val(m[i][j], m[i][j+1], m[i+1][j]) + 1;
            }
        }
//        //afisare matrice
//        for(k=0;k<lena;k++){
//            for(l=0;l<lenb;l++){
//                printf("%d ",m[k][l]);
//            }
//            printf("\n");
//        }
//        printf("\n");
    }
    return m[lena-1][lenb-1];
}

// recursiv
int leven2(const char *s, int ls, const char *t, int lt){
        int a, b, c;

        if (!ls) return lt;
        if (!lt) return ls;

        if (s[ls] == t[ls])
                return leven2(s, ls - 1, t, lt - 1);
        a = leven2(s, ls - 1, t, lt - 1);
        b = leven2(s, ls,     t, lt - 1);
        c = leven2(s, ls - 1, t, lt    );

        if (a > b) a = b;
        if (a > c) a = c;

        return a + 1;
}


List find_similar_words( char word[], int changes, List_Node *start, List_Node *stop ){
    List sim;
    sim.head = NULL;
    sim.tail = NULL;
    List_Node *x;
    List_Node *aux;
    int lev;

    x = start;

    while ( x!=NULL && x->prev != stop) {
        lev = leven1(word, strlen(word), x->word, strlen(x->word));
        assert(lev>=0);
        if( lev <= changes){
            aux = (List_Node*) malloc(sizeof(List_Node));
            aux->word = (char *) malloc(sizeof( x->word ));
            strcpy(aux->word,x->word);
            list_insert(&sim,aux);
        }
        x = x->next;
    }
    return sim;
}
