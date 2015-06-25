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

int leven( char *a, unsigned int lena, char *b, unsigned int lenb ){// iterativ
    int m[50][50];
    int dist[50][50];
    int  i,j;

    for(i=0;i<lena;i++)
        for(j=0;j<lenb;j++)
            dist[i][j] = dist_lit(a[i],b[j]);

    //m[0][0]=0;
    m[0][0]=dist[0][0];
    for(i=1;i<lena;i++)
        //m[i][0]=2*i;
        m[i][0]=1 + m[i-1][0]/2 + dist[i][0]/2;
        //m[i][0]=i + dist[i][0];
        //m[i][0]=m[i-1][0] + min_val(dist[i][0], dist[i-1][0], dist[i+1][0]) + 1;
    for(j=1;j<lenb;j++)
        //m[0][j]=2*j;
        m[0][j]=1+ m[0][j-1]/2 + dist[0][j]/2;
        //m[0][j]=j + dist[0][j];
        //m[0][j]=m[0][j-1] + min_val(dist[0][j], dist[0][j-1], dist[0][j+1]) + 1;
    m[lena][0]=m[lena-1][0];
    m[0][lenb]=m[0][lenb-1];


    for(i=0;i<lena;i++){
        for(j=0;j<lenb;j++){

            if(a[i]==b[j]){
                m[i+1][j+1]=m[i][j];
            }
            else{

                if (a[i] != b[j-1] && a[i]!= b[j-1]) {// litera a[i] nu se afla in celalalt sir
                    if( dist[i][j] == 1 ){ // a apasat pe langa
                        m[i+1][j+1] = min_val(m[i][j], m[i][j-1],  m[i-1][j]) + dist[i][j];
                    }
                    else{
                        m[i+1][j+1] += min_val(m[i][j], m[i][j-1],  m[i-1][j]) + 2  + dist[i][j];
                    }
                }
                else {
                    if(b[j] != a[i-1] && b[j] != a[i+1]){// litera b[j] nu se afla in celalalt sir
                        if( dist[i][j] == 1 ){ // a apasat pe langa
                            m[i+1][j+1] = min_val(m[i][j], m[i][j-1],  m[i-1][j]) + dist[i][j];
                        }
                        else{
                            m[i+1][j+1] += min_val(m[i][j], m[i][j-1],  m[i-1][j]) + 2  + dist[i][j];
                        }
                    }
                }


                if(lena==lenb){
                    m[i+1][j+1]=min_val(m[i][j], m[i][j-1],  m[i-1][j]);

                    if (  dist[i-1][j] == dist[i][j-1] && dist[i][j-1] == 0 ){// inversare litere
                        m[i+1][j+1] = min_val(m[i][j-1], m[i][j-1],  m[i-1][j] );
                    }
                    else{
                        if(dist[i][j]>=1)
                            m[i+1][j+1]+=1;
                        m[i+1][j+1] += dist[i][j];
                    }
                }
                else{// lena != lenb
                    if (  dist[i-1][j] == dist[i][j-1] && dist[i][j-1] == 0 ){// inversare litere
                        m[i+1][j+1]= 1 + min_val(m[i][j-1], m[i][j-1],  m[i-1][j]);
                    }
                    else{
                        if( m[i-1][j] + dist[i-1][j] == min_val(m[i][j-1], m[i][j-1],  m[i-1][j]) ){
                            m[i+1][j+1]=m[i-1][j];
                        }
                        if( m[i][j-1] + dist[i][j-1] == min_val(m[i][j-1], m[i][j-1],  m[i-1][j]) ){
                            m[i+1][j+1]=m[i][j-1];
                        }
                    }
                }
            }
        }
    }
    return m[lena][lenb] + abs(lena-lenb);
    //return m[lena][lenb]+abs(lena-lenb);
}

void find_similar_words( List* l_sim, char * word , int changes, List_Node *start, List_Node *stop ){
    l_sim->head = NULL;
    l_sim->tail = NULL;
    List_Node *i;
    List_Node *aux;
    int lev;
    i = start;
    while ( i!=NULL && i->prev != stop) {
        lev = leven(word, strlen(word), i->word, strlen(i->word));
        assert(lev>=0);
        if( lev <= changes){
            aux = (List_Node*) malloc(sizeof(List_Node));
            aux->word = (char *) malloc(sizeof(char)*  strlen(i->word) );
            strcpy(aux->word,i->word);
            list_insert(l_sim,aux);
        }
        i = i->next;
    }

    sort_list_lev(l_sim, word);
}

void sort_list_lev( List *l , char* word){//sorteaza lexicografic lista cu insertion sort
    register List_Node *i;
    register List_Node *key;
    register List_Node *key_next;
    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = key->prev;
        while( i!=NULL  &&  leven(word,strlen(word),key->word,strlen(key->word)) < leven(word, strlen(word), i->word, strlen(i->word)) ){
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
