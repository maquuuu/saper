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

void odkryjPole(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *ods³onietePola) {
    if (mapa[x][y] == '.') {
        rozszerzOdkrycie(mapa, wiersze, kolumny, x, y, koniecGry, ods³onietePola);
    } else if (mapa[x][y] == 'F') {
        printf("Pole oznaczone flag¹!\n");
    } else if (mapa[x][y] == 'M') {
        *koniecGry = 1;
    } else {
        printf("To pole jest ju¿ odkryte!\n");
    }
}

void rozszerzOdkrycie(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *ods³onietePola) {
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny || mapa[x][y] != '.') {
        return;
    }

    int liczbaMin = liczMiny(mapa, wiersze, kolumny, x, y);
    mapa[x][y] = '0' + liczbaMin;

    (*ods³onietePola)++;

    if (liczbaMin == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == '.') {
                    rozszerzOdkrycie(mapa, wiersze, kolumny, nx, ny, koniecGry, ods³onietePola);
                }
            }
        }
    }
}

void ustawFlage(char **mapa, int x, int y) {
    if (mapa[x][y] == '.' || mapa[x][y] == 'M') {
        mapa[x][y] = 'F';
        printf("Flaga ustawiona na polu (%d, %d)\n", x, y);
    } else if (mapa[x][y] == 'F') {
        mapa[x][y] = '.';
        printf("Flaga usuniêta z pola (%d, %d)\n", x, y);
    } else {
        printf("To pole jest ju¿ odkryte , nie mo¿na ustawiæ flagi.\n");
    }
}

