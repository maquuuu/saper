#ifndef MAPA_H
#define MAPA_H

void generujMape(int wiersze, int kolumny, int miny, int poziomTrudnosci);
void wypiszMape(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int koniecGry);
void losujMiny(char **mapa, int wiersze, int kolumny, int x, int y, int miny);

#endif

