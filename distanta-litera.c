#include<stdio.h>

int distanta_litera(char a, char b){
    return (  abs(linie_litera[a-97]-linie_litera[b-97]) +  abs(coloana_litera[a-97]-coloana_litera[b-97])  );
}
