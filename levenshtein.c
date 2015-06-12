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
int leven1( char *a, unsigned int lena, char *b, unsigned int lenb ){// iterativ
    unsigned int m[50][50];
    int i,j;

    for(i=0;i<lena;i++)
        m[i][0]=i;
    for(j=0;j<lenb;j++)
        m[0][j]=j;

    for(i=0;i<lena;i++){
        for(j=0;j<lenb;j++){
            if(a[i]==b[j]){
                m[i+1][j+1]=m[i][j];
            }
            else{
                m[i+1][j+1]=min_val(m[i][j], m[i][j+1], m[i+1][j]) + 1;
            }
        }
    }
    return m[lena][lenb];
}
int leven_upgraded( char *a, unsigned int lena, char *b, unsigned int lenb ){// iterativ
    unsigned int m[50][50];
    int i,j;
    for(i=0;i<lena;i++)
        m[i][0]=i;
    for(j=0;j<lenb;j++)
        m[0][j]=j;

    for(i=0;i<lena;i++){
        for(j=0;j<lenb;j++){
            if(a[i]==b[j]){
                m[i+1][j+1]=m[i][j];
            }
            else{
                m[i+1][j+1]=min_val(m[i][j], m[i][j+1], m[i+1][j]) + distanta_litera(a[i],b[j]);
            }
        }
    }
    return m[lena][lenb]+(abs(strlen(a)-strlen(b)));
}
int leven2(const char *s, int ls, const char *t, int lt){// recursiv
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
void find_similar_words( List* l_sim, char word[], int changes, List_Node *start, List_Node *stop ){
    l_sim->head = NULL;
    l_sim->tail = NULL;
    List_Node *x;
    List_Node *aux;
    int lev;

    x = start;
    while ( x!=NULL && x->prev != stop) {
        lev = leven_upgraded(word, strlen(word), x->word, strlen(x->word));
        assert(lev>=0);
        if( lev <= changes){
            aux = (List_Node*) malloc(sizeof(List_Node));
            aux->word = (char *) malloc(sizeof(char)*  strlen(x->word) );
            strcpy(aux->word,x->word);
            list_insert(l_sim,aux);
        }
        x = x->next;
    }
}

void sort_list_lev( List *l , char* word){//sorteaza lexicografic lista cu insertion sort
    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = key->prev;
        while( i!=NULL  &&  leven1(word,strlen(word),key->word,strlen(key->word)) < leven1(word, strlen(word), i->word, strlen(i->word)) ){
            i = i->prev;
        }
        if(key->prev != i){
            if(i==NULL){
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->prev != NULL)
                    key->prev->next = key->next;
                if(key->next != NULL)
                    key->next->prev = key->prev;
                key->next = l->head;
                key->prev = NULL;
                l->head->prev = key;
                l->head = key;
            }
            else{
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->next != NULL)
                    key->next->prev = key->prev;
                if(key->prev != NULL)
                    key->prev->next = key->next;
                key->next = i->next;
                if(i->next != NULL)
                    i->next->prev = key;
                i->next = key;
                key->prev = i;
            }
        }

    key = key_next;
    }
}
void sort_list_lev_upgraded( List *l , char* word){//sorteaza lexicografic lista cu insertion sort
    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    if(l->head==NULL)
        return;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = key->prev;
        while( i!=NULL  &&  leven_upgraded(word,strlen(word),key->word,strlen(key->word)) < leven1(word, strlen(word), i->word, strlen(i->word)) ){
            i = i->prev;
        }
        if(key->prev != i){
            if(i==NULL){
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->prev != NULL)
                    key->prev->next = key->next;
                if(key->next != NULL)
                    key->next->prev = key->prev;
                key->next = l->head;
                key->prev = NULL;
                l->head->prev = key;
                l->head = key;
            }
            else{
                if(key == l->tail)
                    l->tail = key->prev;

                if(key->next != NULL)
                    key->next->prev = key->prev;
                if(key->prev != NULL)
                    key->prev->next = key->next;
                key->next = i->next;
                if(i->next != NULL)
                    i->next->prev = key;
                i->next = key;
                key->prev = i;
            }
        }

    key = key_next;
    }
}
