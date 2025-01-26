#include <stdio.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

void wykonajRuch(char **mapa, int wiersze, int kolumny, int x, int y, char akcja, int *koniecGry, int *odslonietePola) {
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny) {
        printf("Poza zakresem mapy!\n");
        return;
    }

    if (akcja == 'r') {
        if (mapa[x][y] == 'M') {
            printf("Bum! Trafiles na mine!\n");
            *koniecGry = 1;
            return;
        } else if (mapa[x][y] == '.' || mapa[x][y] == 'F') {
            int minyWokol = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == 'M') {
                        minyWokol++;
                    }
                }
            }

            mapa[x][y] = minyWokol + '0';
            (*odslonietePola)++;

            if (minyWokol == 0) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int nx = x + i;
                        int ny = y + j;
                        if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == '.') {
                            wykonajRuch(mapa, wiersze, kolumny, nx, ny, akcja, koniecGry, odslonietePola);
                        }
                    }
                }
            }
        }
    } else if (akcja == 'f') {
        if (mapa[x][y] == '.') {
            mapa[x][y] = 'F';
        } else if (mapa[x][y] == 'F') {
            mapa[x][y] = '.';
        }
    }
}

