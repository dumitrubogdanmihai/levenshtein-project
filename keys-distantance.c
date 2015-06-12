#include<stdio.h>
#include"keys-distantance.h"

int min(int a,int b){
    if(a<b)
        return a;
    return b;
}

int dist_lit(char a, char b){
    return (  abs(linie_litera[a-97]-linie_litera[b-97]) +  abs(coloana_litera[a-97]-coloana_litera[b-97])  );
}

int distanta_cuvinte(char * c1, char *c2){
    int i,j,s=0;
    for(i=0;i< min(strlen(c1),strlen(c2)) ; i++)
        s+= dist_lit( c1+i, c2+i );
    return s;
}

void load_keyboard(char fisier[]){
    FILE * f = fopen(fisier,"r");
    int i,j,nr_coloane,nr_linii;
    char ch;
    fscanf(f,"%d%d",&nr_linii,&nr_coloane);
    for(i=0;i<nr_linii;i++){
            fscanf(f,"%c",&ch);
        for(j=0;j<nr_coloane;j++){
            fscanf(f,"%c",&ch);
            linie_litera[(int)(tolower(ch))-97]=i;
            coloana_litera[(int)(tolower(ch))-97]=j;
        }
    }
    fclose(f);
}
