#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dzialanie.h"

#define LATWY_WIERSZE 9
#define LATWY_KOLUMNY 9
#define LATWY_MINY 10

#define SREDNI_WIERSZE 16
#define SREDNI_KOLUMNY 16
#define SREDNI_MINY 40

#define TRUDNY_WIERSZE 16
#define TRUDNY_KOLUMNY 30
#define TRUDNY_MINY 99

void generujMape(int wiersze, int kolumny, int miny);
void wypiszMape(char **mapa, int wiersze, int kolumny);

int main() {
    int wybor;

    printf("Wybierz poziom trudnosci:\n");
    printf("1. Latwy (9x9, 10 min)\n");
    printf("2. Sredni (16x16, 40 min)\n");
    printf("3. Trudny (16x30, 99 min)\n");
    printf("Podaj numer: ");

    scanf("%d", &wybor);

    switch (wybor) {
        case 1:
            generujMape(LATWY_WIERSZE, LATWY_KOLUMNY, LATWY_MINY);
            break;
        case 2:
            generujMape(SREDNI_WIERSZE, SREDNI_KOLUMNY, SREDNI_MINY);
            break;
        case 3:
            generujMape(TRUDNY_WIERSZE, TRUDNY_KOLUMNY, TRUDNY_MINY);
            break;
        default:
            printf("Nieprawidlowy wybor!\n");
            return 1;
    }

    return 0;
}

void generujMape(int wiersze, int kolumny, int miny) {
    char **mapa = malloc(wiersze * sizeof(char *));
    for (int i = 0; i < wiersze; i++) {
        mapa[i] = malloc(kolumny * sizeof(char));
        for (int j = 0; j < kolumny; j++) {
            mapa[i][j] = '.';
        }
    }

    srand(time(NULL));
    for (int i = 0; i < miny; i++) {
        int x, y;
        do {
            x = rand() % wiersze;
            y = rand() % kolumny;
        } while (mapa[x][y] == 'M');
        mapa[x][y] = 'M';
    }

void wypiszMape(char **mapa, int wiersze, int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (mapa[i][j] == 'M') {
                printf(". ");
            } else {
                printf("%c ", mapa[i][j]);
            }
        }
        printf("\n");
    }
}
