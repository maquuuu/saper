#ifndef INTERAKCJA_H
#define INTERAKCJA_H

int liczMiny(char **mapa, int wiersze, int kolumny, int x, int y);
void odkryjPole(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *ods³onietePola);
void rozszerzOdkrycie(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *ods³onietePola);
void ustawFlage(char **mapa, int x, int y);

#endif

