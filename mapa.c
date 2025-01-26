#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

void generujMape(int wiersze, int kolumny, int miny, int poziomTrudnosci) {
    char **mapa = malloc(wiersze * sizeof(char *));
    for (int i = 0; i < wiersze; i++) {
        mapa[i] = malloc(kolumny * sizeof(char));
        for (int j = 0; j < kolumny; j++) {
            mapa[i][j] = '.';
        }
    }

    wypiszMape(mapa, wiersze, kolumny, 0);

    int x, y;
    char akcja;
    int pierwszeOdkrycie = 1;
    int koniecGry = 0;
    int odsłonietePola = 0;

    while (!koniecGry) {
        printf("Podaj ruch (f x y - flaga, r x y - odkrycie): ");
        scanf(" %c %d %d", &akcja, &y, &x);
        if (x < 0 || x >= kolumny || y < 0 || y >= wiersze) {
    printf("Nieprawidlowe wspolrzedne! Podaj wartości w zakresie: 0 <= x < %d i 0 <= y < %d.\n", kolumny, wiersze);
    continue;
	}
        if (akcja == 'q') {
            break;
        }

        if (akcja == 'r') {
            if (pierwszeOdkrycie) {
                losujMiny(mapa, wiersze, kolumny, x, y, miny);
                pierwszeOdkrycie = 0;
            }

            wykonajRuch(mapa, wiersze, kolumny, x, y, akcja, &koniecGry, &odsłonietePola);
        } else if (akcja == 'f') {
            wykonajRuch(mapa, wiersze, kolumny, x, y, akcja, &koniecGry, &odsłonietePola);
        }
        wypiszMape(mapa, wiersze, kolumny, koniecGry);
        obliczWynik(odsłonietePola, poziomTrudnosci);
        if (odsłonietePola == wiersze * kolumny - miny) {
            printf("Gratulacje! Wygrales!\n");
            koniecGry = 1;
        }
    }
   printf("Koniec gry!\n");
    char nazwaGracza[50];
        printf("Podaj swoja nazwe gracza: ");
        scanf("%s", nazwaGracza);
    FILE *plik = fopen("leaderboard.txt", "a");
        if (plik) {
            fprintf(plik, "Gracz: %s | Wynik: %d\n",
                    nazwaGracza,
                    odsłonietePola*poziomTrudnosci);
            fclose(plik);
            printf("Twoj wynik zostal zapisany w pliku leaderboard.txt.\n");
        } else {
            printf("Nie udalo się zapisac wyniku do pliku.\n");
        }
        najlepsiGracze();
    for (int i = 0; i < wiersze; i++) {
        free(mapa[i]);
    }
    free(mapa);  
}

void wypiszMape(char **mapa, int wiersze, int kolumny, int koniecGry) {
    printf("    ");
    for (int j = 0; j < kolumny; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    printf("   ");
    for (int j = 0; j < kolumny; j++) {
        printf("---");
    }
    printf("\n");
    for (int i = 0; i < wiersze; i++) {
        printf("%2d |", i);
        for (int j = 0; j < kolumny; j++) {
            if (koniecGry && mapa[i][j] == 'M') {
                printf(" M ");
            } else if (mapa[i][j] == 'M') {
                printf(" . ");
            } else {
                printf(" %c ", mapa[i][j]);
            }
        }
        printf("|\n");
    }
    printf("   ");
    for (int j = 0; j < kolumny; j++) {
        printf("---");
    }
    printf("\n");
}

void losujMiny(char **mapa, int wiersze, int kolumny, int x, int y, int miny) {
    srand(time(NULL));

    int minyDoRozmieszczenia = miny;

    while (minyDoRozmieszczenia > 0) {
        int mx = rand() % wiersze;
        int my = rand() % kolumny;

        if (mapa[mx][my] != 'M' && !(mx == x && my == y)) {
            mapa[mx][my] = 'M';
            minyDoRozmieszczenia--;
        }
    }
}
