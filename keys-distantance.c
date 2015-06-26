///\file keys-distantance.c
///\brief Biblioteca C pentru implementarea imbunatatirii corectarii .
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -functia ce construieste o matrice ce reproduce partial tastatura
* -gasirea vecinilor unui caracter din aceasta matricea
* -aflarea distanei dintre litere pentru o eficienta sporita la corectare
*/

#include<stdio.h> ///> printf()
#include<string.h> ///> strcpy()
#include<assert.h>
#include<math.h> ///>abs()
#include<string.h> ///>tolower()
#include"keys-distantance.h" ///> getNeighbors(),dist_lit(),distanta_cuvinte(),load_keyboard()
//>>>>>>> origin/master

char* getNeighbors(char ch){//under developing

    ///\fn void getNeighbors(char ch, char * neigh)
    ///\brief Verifica vecinii unei taste.
    ///\param ch Variabila de tip char ce memoreaza tasta pentru care se verifica vecinii
    ///\param neigh Pointer de tip char ce memoreaza vecinii lui ch
    ///
    ///Implemntarea gasirii vecinilor unui caracter de pe tastatura.


    int i,j;
    static char * neigh[10];
    neigh[0]='\0';
    for( i = linie_litera[(int)ch]-1;  i<=linie_litera[(int)ch]+1 && i<nr_linii_taste ; i++  ){
        if(i<0)i=0;
        printf("\n");
        for(  j = coloana_litera[(int)ch]-1; j<=coloana_litera[(int)ch]+1 && j<=nr_coloane_taste ; j++  ){
            if(j<0)j=0;
            if(i!=linie_litera[(int)ch] && j!=coloana_litera[(int)ch])
                strcat(neigh,keyboard[i][j]);
            //printf("%c",keyboard[i][j]);
        }
    }
      //  printf("\n");
        return neigh;
}

int min(int a,int b){

    ///\fn int min(int a,int b)
    ///\brief Returneaza minimul.
    ///\param a Variabila de tip intreg
    ///\param b Variabila de tip intreg
    ///
    ///Implementarea aflarii minimului dintre doua numere intregi.


    if(a<b)
        return a;
    return b;
}

int dist_lit(char a, char b){

    ///\fn int dist_lit(char a, char b)
    ///\brief Returneaza distanta dintre doua caractere.
    ///\param a Variabila de tip char
    ///\param b Variabila de tip char
    ///
    ///Implementarea aflarii distantei dintre doua caractere ale matricei ce reproduce partial tastatura.



    if(a>='A'&&a<='Z')
        a=tolower(a);

    if(b>='A'&&b<='Z')
        b=tolower(b);


    if(a==b)
        return 0;
    int dist_x = abs((int)linie_litera[(int)a]-linie_litera[(int)b]),
        dist_y = abs(coloana_litera[(int)a]-coloana_litera[(int)b]);
    if( dist_x == dist_y && dist_x == 1)
        return 1;
    assert(dist_x + dist_y < nr_linii_taste + nr_coloane_taste +3);
    return  dist_x + dist_y ;
}

void load_keyboard(char fisier[]){

    ///\fn void load_keyboard(char fisier[])
    ///\brief Memoreaza tastatura.
    ///\param fisier Variabila de tip char ce memoreaza numele fisierului
    ///
    ///Implementarea citirii din fisier a matricei ce reproduce partial tastatura.


    FILE * f = fopen(fisier,"r");
    int i,j;
    char ch;
    fscanf(f,"%d%d",&nr_linii_taste,&nr_coloane_taste);
    for(i=0;i<255;i++){
        linie_litera[i]=nr_linii_taste;
        coloana_litera[i]=nr_coloane_taste;
    }
    for(i=0;i<nr_linii_taste;i++){
            fscanf(f,"%c",&ch);
        for(j=0;j<nr_coloane_taste;j++){
            fscanf(f,"%c",&ch);
            linie_litera[(int)(tolower(ch))]=i;
            coloana_litera[(int)(tolower(ch))]=j;
            keyboard[i][j]=ch;
        }
    }
    fclose(f);
}
