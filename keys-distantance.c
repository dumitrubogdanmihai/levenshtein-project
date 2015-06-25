#include<stdio.h>
#include<string.h>
#include<math.h>
#include"keys-distantance.h"

void getNeighbors(char ch, char * neigh){
    int i,j;
    for( i = (int) keyboard[linie_litera[(int)ch]-1]; i<=(int)keyboard[linie_litera[(int)ch]+1] && i<=4 ; i++  ){
        if(i<0)i=0;
        for(  j = (int)keyboard[coloana_litera[(int)ch]-1]; j<=(int)keyboard[coloana_litera[(int)ch]+1] && j<=4 ; j++  ){
            if(j<0)j=0;
            strcpy(neigh,keyboard[i][j]);
        }
    }
}

int min(int a,int b){
    if(a<b)
        return a;
    return b;
}

int dist_lit(char a, char b){
    if(a==b)
        return 0;
    int dist_x = abs((int)linie_litera[(int)a]-linie_litera[(int)b]),
        dist_y = abs(coloana_litera[(int)a]-coloana_litera[(int)b]);
    if( dist_x == dist_y && dist_x == 1)
        return 1;
    return 1 + ( dist_x + dist_y  );
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
            linie_litera[(int)(tolower(ch))]=i;
            coloana_litera[(int)(tolower(ch))]=j;
            keyboard[i][j]=ch;
        }
    }
    fclose(f);
}
