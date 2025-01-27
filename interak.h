#ifndef INTERAKCJA_H
#define INTERAKCJA_H

int liczMiny(char **mapa, int wiersze, int kolumny, int x, int y);
void odkryjPole(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odslonietePola);
void rozszerzOdkrycie(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odslonietePola);
void ustawFlage(char **mapa, char **widocznaMapa, int x, int y);

#endif

