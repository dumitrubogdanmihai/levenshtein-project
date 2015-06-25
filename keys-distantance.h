///\file list.h
///\brief Biblioteca C pentru realizarea imbunatatirea .
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -functia ce construieste o matrice ce reproduce partial tastatura
* -gasirea vecinilor unui caracter din aceasta matricea
* -aflarea distanei dintre litere pentru o eficienta sporita la corectare
*/

#ifndef KEYS-DISTANCE_H_INCLUDED
#define KEYS-DISTANCE_H_INCLUDED

int linie_litera[260],coloana_litera[260];
char keyboard[6][15];


void getNeighbors(char ch, char * neigh);
int dist_lit(char a, char b);
int distanta_cuvinte(char * c1, char *c2);
void load_keyboard(char fisier[]);

#endif // KEYS-DISTANCE_H_INCLUDED
