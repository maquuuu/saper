#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"
#include "zapis.h"

void generujMape(int wiersze, int kolumny, int miny, int poziomTrudnosci) {
    char **mapa = malloc(wiersze * sizeof(char *));
    char **widocznaMapa = malloc(wiersze * sizeof(char *));
    for (int i = 0; i < wiersze; i++) {
        widocznaMapa[i] = malloc(kolumny * sizeof(char));
        for (int j = 0; j < kolumny; j++) {
            widocznaMapa[i][j] = '.';
        }
    }
    for (int i = 0; i < wiersze; i++) {
        mapa[i] = malloc(kolumny * sizeof(char));
        for (int j = 0; j < kolumny; j++) {
            mapa[i][j] = '.';
        }
    }

    wypiszMape(mapa, widocznaMapa, wiersze, kolumny, 0);

    int x, y;
    char akcja;
    int wygrana = 0;
    int pierwszeOdkrycie = 1;
    int koniecGry = 0;
    int odsĹ‚onietePola = 0;

    while (!koniecGry) {
        printf("Podaj ruch (f x y - flaga, r x y - odkrycie): ");
        scanf(" %c %d %d", &akcja, &y, &x);
        if (x < 0 || y >= kolumny || y < 0 || x >= wiersze) {
    printf("Nieprawidlowe wspolrzedne! Podaj wartosci w zakresie: 0 <= x < %d i 0 <= y < %d.\n", kolumny, wiersze);
    continue;
	}
        if (akcja == 'q') {
            break;
        }

        if (akcja == 'r') {
            if (mapa[x][y] >= '0' && mapa[x][y] <= '8') {
            printf("To pole zostalo juz odkryte! Wybierz inne pole.\n");
            continue;
        }
            if (pierwszeOdkrycie) {
                losujMiny(mapa, wiersze, kolumny, x, y, miny);
                pierwszeOdkrycie = 0;
            }

            wykonajRuch(mapa, widocznaMapa, wiersze, kolumny, x, y, akcja, &koniecGry, &odsĹ‚onietePola);
        } else if (akcja == 'f') {
            wykonajRuch(mapa, widocznaMapa, wiersze, kolumny, x, y, akcja, &koniecGry, &odsĹ‚onietePola);
        }
        else if(akcja != 'f' || akcja != 'r' || akcja != 'q') {
            printf("Nieprawidlowa komenda.\n");
            continue;
        }
        wypiszMape(mapa, widocznaMapa, wiersze, kolumny, koniecGry);
        obliczWynik(odsĹ‚onietePola, poziomTrudnosci);
        if (odsĹ‚onietePola == wiersze * kolumny - miny) {
            printf("Gratulacje! Wygrales!\n");
            koniecGry = 1;
            wygrana = 1;
        }
    }
    if(!wygrana){
        printf("Bum! Trafiles na mine!\n");
	}
    printf("Koniec gry!\n");
        zapiszLeaderboard(odsĹ‚onietePola, poziomTrudnosci);
        najlepsiGracze();
        zapiszMapeDoPliku(mapa, wiersze, kolumny);
    for (int i = 0; i < wiersze; i++) {
        free(mapa[i]);
    }
    free(mapa);
    for (int i = 0; i < wiersze; i++) {
        free(widocznaMapa[i]);
    }
    free(widocznaMapa);  
}

void wypiszMape(char **mapa, char**widocznaMapa, int wiersze, int kolumny, int koniecGry) {
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
            }else if ( mapa[i][j] >= '0' && mapa[i][j] <= '8') {
                printf(" %c ", mapa[i][j]);
            }else {
                printf(" %c ", widocznaMapa[i][j]);
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
