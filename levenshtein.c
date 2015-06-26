///\file levenshtein.c
///\brief Biblioteca C pentru  .
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
*/

#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include "levenshtein.h"
#include "keys-distantance.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>

int min_val(int a, int b, int c);
int leven( char *a, unsigned int lena, char *b, unsigned int lenb );
int leven2( char *a, unsigned int lena, char *b, unsigned int lenb );
int difference(char **a, unsigned int lena, char **b, unsigned int lenb);
void sort_list_lev( List *l , char* word);

int min_val(int a, int b, int c) {
    ///\fn min_val(int a, int b, int c)
    ///\brief Returneaza minimul dintre 3 intregi.
    ///\param a Variabila de tip int
    ///\param b Variabila de tip int
    ///\param c Variabila de tip int
    ///
    ///Implementarea aflarii minimului dintre 3 numere de tip integer.

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
    ///\fn int leven( char *a, unsigned int lena, char *b, unsigned int lenb )
    ///\brief Returneaza diferenta dintre 2 cuvinte
    ///\param a Variabila de tip pointer la char reprezentand primul cuvant
    ///\param b Variabila de tip int reprezentant lungimea primului cuvant
    ///\param b Variabila de tip pointer la char reprezentand al doilea cuvant
    ///\param c Variabila de tip int reprezentand lungimea celui de-al doilea cuvant
    ///
    ///Implementarea diferentei dintre 2 cuvinte folosind modelul iterativ al functiei lui Levenshtein
    unsigned int m[150][150];
    int i,j;

    for(i=0;i<=lena;i++)
        m[i][0]=i;
    for(j=0;j<=lenb;j++)
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


int leven2( char *a, unsigned int lena, char *b, unsigned int lenb ){// iterativ
    ///\fn int leven2( char *a, unsigned int lena, char *b, unsigned int lenb )
    ///\brief Returneaza diferenta dintre 2 cuvinte
    ///\param a Variabila de tip pointer la char reprezentand primul cuvant
    ///\param b Variabila de tip int reprezentant lungimea primului cuvant
    ///\param b Variabila de tip pointer la char reprezentand al doilea cuvant
    ///\param c Variabila de tip int reprezentand lungimea celui de-al doilea cuvant
    ///
    ///Implementarea diferentei dintre 2 cuvinte folosind modelul iterativ al functiei lui Levenshtein dar tinand cont de distanta din taste pe tastatura

if(abs(lena-lenb)>4)
    return 99;

    int m[150][150];
    int dist[150][150];
    int  i,j,I,J;

for(I=0;I<=lena;I++){
        for(J=0;J<=lenb;J++){
                m[I][J]=10;
                dist[I][J]=dist_lit(a[I],b[J]);
        }
}
    //m[0][0]=0;
    m[0][0]=dist[0][0];
    for(i=1;i<lena;i++)
        m[i][0]=1 + m[i-1][0] + dist[i][0]/2;
    for(j=1;j<lenb;j++)
        m[0][j]=1+ m[0][j-1] + dist[0][j]/2;
    m[lena][0]=m[lena-1][0];
    m[0][lenb]=m[0][lenb-1];
//printf("%s   %s\n\t\t\t%d %d\n",a,b,i,j);
    for(i=0;i<lena;i++){
        for(j=0;j<lenb;j++){
//        for(I=0;I<lena;I++){
//        for(J=0;J<lenb;J++){
//                printf("%d\t",m[I][J]);
//        }
//        printf("|\n");
//    }printf("\n");
//        printf("\n");
            if(a[i]==b[j]){
//                m[i+1][j+1]=min_val(m[i][j], m[i][j-1],  m[i-1][j]);
                m[i+1][j+1]=m[i][j];
            }
            else{
                if (a[i] != b[j-1] ) {// litera a[i] nu se afla in celalalt sir
                    if( dist[i][j] == 1 ){ // a apasat pe langa
                        m[i+1][j+1] = min_val(m[i][j], m[i][j+1],  m[i+1][j]) + 2;
                    }
                    else{
                        m[i+1][j+1] += min_val(m[i][j], m[i][j+1],  m[i+1][j]) + 2  + dist[i][j];
                    }
                }
                else{
                    m[i+1][j+1] = min_val(m[i][j], m[i][j+1],  m[i+1][j])+1;
                }
            }
        }
    }
//if(m[lena][lenb] + abs(lena-lenb)<=0||m[lena][lenb] + abs(lena-lenb)>100){
//        printf("%s   %s\n",a,b);
//        for(I=0;I<lena;I++){
//        for(J=0;J<lenb;J++){
//                printf("%d\t",m[I][J]);
//        }
//        printf("|\n");
//    }printf("\n");
//        printf("\n");
//}
    return m[lena][lenb] + abs(lena-lenb);
    //return m[lena][lenb]+abs(lena-lenb);
}
int difference(char **a, unsigned int lena, char **b, unsigned int lenb){
    ///\fn difference(char **a, unsigned int lena, char **b, unsigned int lenb)
    ///\brief Returneaza diferenta dintre 2 cuvinte
    ///\param a Variabila de tip pointer la char reprezentand primul cuvant
    ///\param b Variabila de tip int reprezentant lungimea primului cuvant
    ///\param b Variabila de tip pointer la char reprezentand al doilea cuvant
    ///\param c Variabila de tip int reprezentand lungimea celui de-al doilea cuvant
    ///
    ///Implementarea diferentei dintre 2 cuvinte in functie de functia dorita ( functia intiala este leven2 si se poate fi modificata din optiunile aplicatiei )

    if(sugg_funct==0)
        return leven(a, lena, b, lenb);
    else
        return leven2(a, lena, b, lenb);
}

void sort_list_lev( List *l , char* word){//sorteaza lexicografic lista cu insertion sort
    ///\fn sort_list_lev( List *l , char* word)
    ///\brief Returneaza diferenta dintre 2 cuvinte
    ///\param l Variabila de tip pointer la List reprezentand lista ce se doreste ordonata
    ///\param word Variabila de tip pointer la char reprezentand cuvantul cuvantul de refereinta pentru care s-a construit lista
    ///
    ///Implementarea sortarii listei sugestiilor pentru cuvantul dat ca parametru prin variablia word
    List_Node *i;
    List_Node *key;
    List_Node *key_next;

    if(l->head==NULL||l->head->next==NULL)
        return;

    key = l->head->next;

    while( key != NULL){
    key_next = key->next;

        i = key->prev;

        while( i!=NULL  &&  difference(word,strlen(word),key->word,strlen(key->word)) < difference(word, strlen(word), i->word, strlen(i->word)) ){
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

void find_sim_words( List* l_sim, char * word , int changes, List_Node *start, List_Node *stop ){

    ///\fn find_sim_words( List* l_sim, char * word , int changes, List_Node *start, List_Node *stop )
    ///\brief Construieste lista cuvintelor asemanatoare
    ///\param l_sim Variabila de tip pointer la List reprezentand lista de sugestii
    ///\param word Variabila de tip pointer la char reprezentand cuvantul cuvantul de refereinta pentru care se construieste lista
    ///\param changes Variabila de int care reprezinta numarul de diferente maxime admise
    ///\param start Variabila de pointer la List_Node care reprezinta nodul de la care se porneste cautarea
    ///\param stop Variabila de pointer la List_Node care reprezinta nodul de la care se opreste cautarea
    ///
    ///Implementarea cautarii sugestiilor pentru cuvantul dat prin parametrul word cu un numar maxim de diferente


    l_sim->head = NULL;
    l_sim->tail = NULL;
    List_Node *i;
    List_Node *aux;
    int dif=0;
    i = start;



    while ( i!=NULL && i->prev != stop) {
        dif = difference(word, strlen(word), i->word, strlen(i->word));
//        printf("%s\n",i->word);
        assert(dif>=0);
        if( dif <= changes){
            aux = (List_Node*) malloc(sizeof(List_Node));
            aux->word = (char *) malloc(sizeof(char)*  strlen(i->word) );
            strcpy(aux->word,i->word);
            list_insert(l_sim,aux);
        }
        i = i->next;
    }

    sort_list_lev(l_sim, word);
}
