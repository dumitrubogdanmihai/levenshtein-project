#include<stdio.h> ///> printf()
#include"keys-distantance.h" ///> getNeighbors(),dist_lit(),distanta_cuvinte(),load_keyboard()

void getNeighbors(char ch, char * neigh){
    int i,j;
    for( i = keyboard[linie_litera[ch]-1]; i<=keyboard[linie_litera[ch]+1] && i<=4 ; i++  ){
        if(i<0)i=0;
        for(  j = keyboard[coloana_litera[ch]-1]; j<=keyboard[coloana_litera[ch]+1] && j<=4 ; j++  ){
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
    int dist_x = abs(linie_litera[a]-linie_litera[b]),
        dist_y = abs(coloana_litera[a]-coloana_litera[b]);
    if( dist_x == dist_y && dist_x == 1)
        return 1;
    return 1 + ( dist_x + dist_y  );
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
            linie_litera[(int)(tolower(ch))]=i;
            coloana_litera[(int)(tolower(ch))]=j;
            keyboard[i][j]=ch;
        }
    }
    fclose(f);
}
