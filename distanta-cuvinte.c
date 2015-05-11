#include<stdio.h>

int distanta_cuvinte(char * c1, char *c2){
    int i,j,s=0;
    for(i=0;i< min(strlen(c1),strlen(c2)) ; i++)
        s+= distanta_litera( c1+i, c2+i );
    return s;
}
