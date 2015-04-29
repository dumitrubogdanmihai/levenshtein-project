#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

int leven1( char *a, unsigned int lena, char *b, unsigned int lenb,int m[100][100] );
int min_val(int a, int b, int c);
int gasire_litera( int *k,int *l,int i,char *cuvant,char tastatura[4][10] );
int marja_eroare_tastatura(char *cuvant,bool *marja_eroare,char tastatura[4][10],int i,int k,int l);

int main()
{
    char cuvant[100];       //cuvantul citit de la tastatura
    char cuvant_dex[100];   //cuvantul citit din fisier
    unsigned int lungime_cuvant=0;         //lungimea cuvantului citit de la tastatura
    unsigned int lungime_cuvant_dex=0;     //lungimea cuvantului citit din fisier

    char tastatura[4][10]={ {'1','2','3','4','5','6','7','8','9','0'},{'q','w','e','r','t','y','u','i','o','p'},{'a','s','d','f','g','h','j','k','l','!'},{'z','x','c','v','b','n','m','!','!','!'} };

    int i,j;
    int matrice_levenshtein[100][100];    //matricea care retine diferentele dintre 2 cuvinte in urma algoritumui levenshtein


    //Afisare matrice tastatura
    for( i=0;i<4;i++ ){
        for( j=0;j<10;j++ ){
            if(  tastatura[i][j] != '!' ){
                printf("%c ",tastatura[i][j] );
            }
        }
        printf("\n");
    }
    printf("\n\n");

    gets(cuvant);
    lungime_cuvant=strlen( cuvant );
    strlwr(cuvant);

    FILE *f=fopen("in2.txt","r");

    while( !feof(f) ){

        fgets(cuvant_dex,100,f);
        lungime_cuvant_dex=strlen( cuvant_dex );
        strlwr(cuvant_dex);           // transforma toate literele mari ale sirului in litere mici

        if( leven1(cuvant,lungime_cuvant,cuvant_dex,lungime_cuvant_dex,matrice_levenshtein) == 1 ){
            printf("\n Distanta este 1 \n");
            //getchar();

            i=1;  //retine pozitia primei litere din cuvantul introdus diferita de litera de pe aceasi pozitie din cuvantul din dex
            j=1;  //retine pozitia primei litere din cuvanul din dex diferita de litera de pe aceasi pozitie din cuvantul introdus

            while( i<=lungime_cuvant && j<=lungime_cuvant_dex ){
                    if( matrice_levenshtein[i][j] == 1 ){
                        break;
                    }
                    i++;
                    j++;
            }
            printf("\n\n i=%d \n\n",i);

            //Marja de eroare de la taastatura
            //Se parcurge matricea tastatura si se cauta litera egala cu litera de pe pozitia i a variabilei cuvant

            int k=0,l=0;
            bool marja_eroare=false;

            gasire_litera( &k,&l,i,cuvant,tastatura);

            printf("\n\n Coordonatele sunt : k=%d  l=%d \n\n",k,l);
            getchar();

            printf( "\n\n Litera egala din matricea tastatura este: %c \n\n ",tastatura[k][l] );
            getchar();

            marja_eroare_tastatura( cuvant,&marja_eroare,tastatura,i,k,l );

            printf("\n\n A trecut de fuctia marja_eroare_tastatura \n\n");
            getchar();

            //Se transfrma cuvantul gresit in cuvantul gasit cu distanta levenshtein

            if( marja_eroare == false ){

                printf("\n\n *** S-a terminat marja de eroare de la tastatura *** \n\n");
                printf("\n\n Cuvantul corect este: %s \n\n",cuvant_dex);
                printf("\n\n S-a corectat cuvantul: %s \n\n",cuvant);

                lungime_cuvant=lungime_cuvant_dex;
                strcpy(cuvant,cuvant_dex);

                printf("\n\nIn urma corectarii acesta a devenit: %s \n\n",cuvant);
                getchar();
            }
        }
    }

    fclose(f);

    //Afisare matrice levenshtein
    for( i=0;i<=lungime_cuvant;i++ ){
        for( j=0;j<=lungime_cuvant_dex;j++ ){
            printf( "%d ",matrice_levenshtein[i][j] );
        }
        printf("\n");
    }

    return 0;
}

int leven1( char *a, unsigned int lena, char *b, unsigned int lenb,int m[100][100] )
{
    int i,j;
    int k,l;

    for(i=0;i<=lena;i++)
        m[i][0]=i;
    for(j=0;j<=lenb;j++)
        m[0][j]=j;

    for(i=0;i<=lena-1;i++){
        for(j=0;j<=lenb-1;j++){
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

// Fuctia returneaza coordonatele literei egale din matricea tastatura
int gasire_litera( int *k,int *l,int i,char *cuvant,char tastatura[4][10] )
{
    for( *k=0;*k<4;*k=*k+1 ){
        for( *l=0;*l<10;*l=*l+1 ){

            printf("\n\n %c %c \n\n",cuvant[i-1],tastatura[*k][*l]);
            //getchar();

            if( cuvant[i-1] == tastatura[*k][*l] ){
                printf("\n\nS-a gasit litera in matricea tastatura\n\n");
                getchar();
                return;
            }
        }
    }
}

int marja_eroare_tastatura(char *cuvant,bool *marja_eroare,char tastatura[4][10],int i,int k,int l)
{
            char var_cuvant[100];
            int aux;
    for( aux=0;aux<8;aux++ ){
            //se ia litera de pe diagonala sus stanga din matricea tastatura
            FILE *fisier1=fopen("rodex.txt","r");

            cuvant[i-1]=tastatura[k-1][l-1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();

            while( !feof(fisier1) ){

                fgets(var_cuvant,100,fisier1);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier1);

         //   printf("\n\n !!! A trecut de prima citire din fisier :%s \n\n",cuvant);
         //   getchar();



            //se ia litera din stanga din matricea tastatura
            FILE *fisier2=fopen("rodex.txt","r");

            cuvant[i-1]=tastatura[k][l-1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier2) ){

                fgets(var_cuvant,100,fisier2);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier2);



            //se ia litera de pe diagonala jos stanga din matricea tastatura
            FILE *fisier3=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k+1][l-1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier3) ){

                fgets(var_cuvant,100,fisier3);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier3);



            //se ia litera de sus din matricea tastatura
            FILE *fisier4=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k-1][l];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier4) ){

                fgets(var_cuvant,100,fisier4);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier4);


            //se ia litera de jos din matricea tastatura
            FILE *fisier5=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k+1][l-1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();

            while( !feof(fisier5) ){

                fgets(var_cuvant,100,fisier5);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();

                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier5);

            //se ia litera de pe diagonala sus dreapta din matricea tastatura
            FILE *fisier6=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k-1][l+1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier6) ){

                fgets(var_cuvant,100,fisier6);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier6);



            //se ia litera din dreapta din matricea tastatura
            FILE *fisier7=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k][l+1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier1) ){

                fgets(var_cuvant,100,fisier7);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier7);



            //se ia litera de pe diagonala jos dreapta din matricea tastatura
            FILE *fisier8=fopen("rodex.txt","r");
            cuvant[i-1]=tastatura[k+1][l+1];

            printf( "\n\n --- In uram inlocuirii literei s-a format cuvantul : %s \n\n",cuvant );
            getchar();


            while( !feof(fisier8) ){

                fgets(var_cuvant,100,fisier8);
                strlwr(var_cuvant);

                printf( "\n\n Cuvantul citit din fisier este : %s \n\n",var_cuvant );
                //getchar();


                if( strcmp(cuvant,var_cuvant)==0 ){
                    printf("\n\n!!!!!! Cuvant gasit in dictionar in urma inlocuirii literei este : %s \n\n",var_cuvant);
                    getchar();

                    printf("\n\n Cuvantul a devenit : %s !\n\n",cuvant);
                   // getchar();

                    *marja_eroare=true;
                    return;
                }
            }
            fclose(fisier8);
    }
}





