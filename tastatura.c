#include<stdio.h>


void citire_tastatura(char fisier[]){
    FILE * f = fopen(fisier,"r");
    int i,j,nr_coloane,nr_linii;
    char ch;
    fscanf(f,"%d%d",&nr_linii,&nr_coloane);
    for(i=0;i<nr_linii;i++){
        for(j=0;j<nr_coloane;j++){
            fscanf(f,"%c",&ch);
            linie_litera[(int)(tolower(ch))-97]=i;
            coloana_litera[(int)(tolower(ch))-97]=j;
        }
    }
    fclose(f);
}
