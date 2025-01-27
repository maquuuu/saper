#include <stdio.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

int liczMiny(char **mapa, int wiersze, int kolumny, int x, int y) {
    int liczbaMin = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == 'M') {
                liczbaMin++;
            }
        }
    }

    return liczbaMin;
}

void odkryjPole(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odslonietePola) {
    if (mapa[x][y] == '.') {
        rozszerzOdkrycie(mapa, widocznaMapa, wiersze, kolumny, x, y, koniecGry, odslonietePola);
    } else if (widocznaMapa[x][y] == 'F') {
        printf("Pole oznaczone flaga!\n");
    } else if (mapa[x][y] == 'M') {
        printf("Bum! Trafiles na mine!\n");
        *koniecGry = 1;
    } else {
        printf("To pole jest juz odkryte!\n");
    }
}


void rozszerzOdkrycie(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odslonietePola) {
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny || mapa[x][y] != '.') {
        return;
    }

    int liczbaMin = liczMiny(mapa, wiersze, kolumny, x, y);
    mapa[x][y] = '0' + liczbaMin;

    (*odslonietePola)++;

    if (liczbaMin == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == '.') {
                    rozszerzOdkrycie(mapa, widocznaMapa, wiersze, kolumny, nx, ny, koniecGry, odslonietePola);
                }
            }
        }
    }
}


void ustawFlage(char **mapa, char **widocznaMapa, int x, int y) {
    if (widocznaMapa[x][y] == '.' && !(mapa[x][y] >= '0' && mapa[x][y] <= '8')) {
        widocznaMapa[x][y] = 'F';
        printf("Flaga ustawiona na polu (%d, %d)\n", x, y);
    } else if (widocznaMapa[x][y] == 'F') {
        widocznaMapa[x][y] = '.';
        printf("Flaga usunieta z pola (%d, %d)\n", x, y);
    } else {
        printf("To pole jest juz odkryte, nie mozna ustawic flagi.\n");
    }
}
