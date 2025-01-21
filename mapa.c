#include <stdio.h>
#include <stdlib.h>
#include "dzialanie.h"

#define LATWY_WIERSZE 9
#define LATWY_KOLUMNY 9

#define SREDNI_WIERSZE 16
#define SREDNI_KOLUMNY 16

#define TRUDNY_WIERSZE 16
#define TRUDNY_KOLUMNY 30

void generujMape(int wiersze, int kolumny);
void wypiszMape(char **mapa, int wiersze, int kolumny);

int main() {
    int wybor;

    printf("Wybierz poziom trudnosci:\n");
    printf("1. Latwy (9x9)\n");
    printf("2. Sredni (16x16)\n");
    printf("3. Trudny (16x30)\n");
    printf("Podaj numer: ");

    scanf("%d", &wybor);

    switch (wybor) {
        case 1:
            generujMape(LATWY_WIERSZE, LATWY_KOLUMNY);
            break;
        case 2:
            generujMape(SREDNI_WIERSZE, SREDNI_KOLUMNY);
            break;
        case 3:
            generujMape(TRUDNY_WIERSZE, TRUDNY_KOLUMNY);
            break;
        default:
            printf("Nieprawidlowy wybor!\n");
            return 1;
    }

    return 0;
}

void generujMape(int wiersze, int kolumny) {
    char **mapa = malloc(wiersze * sizeof(char *));
    for (int i = 0; i < wiersze; i++) {
        mapa[i] = malloc(kolumny * sizeof(char));
        for (int j = 0; j < kolumny; j++) {
            mapa[i][j] = '.';
        }
    }

    wypiszMape(mapa, wiersze, kolumny);

    int x, y;
    char akcja;
    while (1) {
        printf("Podaj ruch (f x y - flaga, r x y - odkrycie): ");
        scanf(" %c %d %d", &akcja, &x, &y);

        if (akcja == 'q') {
            break;
        }

        wykonajRuch(mapa, wiersze, kolumny, x, y, akcja);
        wypiszMape(mapa, wiersze, kolumny);
    }

    for (int i = 0; i < wiersze; i++) {
        free(mapa[i]);
    }
    free(mapa);
}


void wypiszMape(char **mapa, int wiersze, int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

