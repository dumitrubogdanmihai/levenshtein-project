#ifndef KEYS-DISTANCE_H_INCLUDED
#define KEYS-DISTANCE_H_INCLUDED

int linie_litera[260],coloana_litera[260];
char keyboard[6][15];


void getNeighbors(char ch, char * neigh);
int dist_lit(char a, char b);
void load_keyboard(char fisier[]);

#endif // KEYS-DISTANCE_H_INCLUDED
