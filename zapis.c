#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"
#include "zapis.h"

void wczytajZPliku(const char *nazwaPliku) {
    printf("Wczytywanie planszy z pliku: %s\n", nazwaPliku);
    FILE *plik = fopen(nazwaPliku, "r");
    if (!plik) {
        printf("Nie udalo sie otworzyc pliku: %s\n", nazwaPliku);
        return;
    }

    char linia[1024];
    fgets(linia, sizeof(linia), plik);
    fgets(linia, sizeof(linia), plik);

    int wiersze = 0, kolumny = 0;

    if (fgets(linia, sizeof(linia), plik)) {
        if (strchr(linia, '|')) {
            char *start = strchr(linia, '|') + 2;
            char *end = strrchr(linia, '|');
            kolumny = (end - start + 1) / 3;
        }
    }

    rewind(plik);
    while (fgets(linia, sizeof(linia), plik)) {
        if (strchr(linia, '|')) {
            wiersze++;
        }
    }

    char **mapa = malloc(wiersze * sizeof(char *));
    if (!mapa) {
        printf("Blad alokacji pamięci dla mapy.\n");
        fclose(plik);
        return;
    }

    rewind(plik);
    fgets(linia, sizeof(linia), plik);
    fgets(linia, sizeof(linia), plik);

    int wierszIndex = 0;
    while (fgets(linia, sizeof(linia), plik)) {
        if (strchr(linia, '|')) {
            mapa[wierszIndex] = malloc((kolumny + 1) * sizeof(char));
            char *start = strchr(linia, '|') + 2;
            for (int i = 0; i < kolumny; i++) {
                mapa[wierszIndex][i] = start[i * 3]; 
            }
            mapa[wierszIndex][kolumny] = '\0';
            wierszIndex++;
        }
    }
    fclose(plik);

    int odslonietePola = 0, polaZMinami = 0, polaBezMin = 0;
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            char pole = mapa[i][j];
            if (pole >= '0' && pole <= '8') {
                odslonietePola++;
            } else if (pole == 'M') {
                polaZMinami++;
            } else if (pole == '.') {
                polaBezMin++;
            }
        }
    }

    int poziomTrudnosci = 0;
    const char *nazwaPoziomu = "Wlasny";
    if (wiersze == 9 && kolumny == 9 && polaZMinami == 10) {
        poziomTrudnosci = 1;
        nazwaPoziomu = "Latwy";
    } else if (wiersze == 16 && kolumny == 16 && polaZMinami == 40) {
        poziomTrudnosci = 2;
        nazwaPoziomu = "Sredni";
    } else if (wiersze == 16 && kolumny == 30 && polaZMinami == 99) {
        poziomTrudnosci = 3;
        nazwaPoziomu = "Trudny";
    }

    printf("Analiza pliku: %s\n", nazwaPliku);
    printf("Rozmiar planszy: %dx%d\n", wiersze, kolumny);
    printf("Poziom trudnosci: %s\n", nazwaPoziomu);
    printf("Odsloniete pola: %d\n", odslonietePola);
    printf("Pola z minami: %d\n", polaZMinami);
    printf("Nieodsloniete pola bez min: %d\n", polaBezMin);

    int punkty = odslonietePola * poziomTrudnosci;
    printf("Liczba punktow: %d\n", punkty);
    if (polaBezMin == 0) {
        printf("Wynik: Wygrana\n");
    } else {
        printf("Wynik: Przegrana\n");
    }

    for (int i = 0; i < wiersze; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void zapiszMapeDoPliku(char **mapa, int wiersze, int kolumny) {
    char nazwaPliku[100];
    printf("Podaj nazwę pliku, do ktorego chcesz zapisac mape (jesli nie chcesz zapisywac nacisnij 'q': ");
    scanf("%s", nazwaPliku);
    if (strcmp(nazwaPliku, "q") == 0){
    return;
    }
    FILE *plik = fopen(nazwaPliku, "w");
    if (plik == NULL) {
        printf("Nie udalo sie otworzyc pliku do zapisu.\n");
        return;
    }
    fprintf(plik, "     ");
    for (int j = 0; j < kolumny; j++) {
        fprintf(plik, "%2d ", j);
    }
    fprintf(plik, "\n");
    fprintf(plik, "   ");
    fprintf(plik, " ");
    for (int j = 0; j < kolumny; j++) {
        fprintf(plik, "---");
    }
    fprintf(plik, "-\n");

    for (int i = 0; i < wiersze; i++) {
        fprintf(plik, "%2d |", i);
        for (int j = 0; j < kolumny; j++) {
            fprintf(plik, " %c ", mapa[i][j]);
        }
        fprintf(plik, "|\n");
    }

    fprintf(plik, "   ");
    fprintf(plik, " ");
    for (int j = 0; j < kolumny; j++) {
        fprintf(plik, "---");
    }
    fprintf(plik, "-\n");

    fclose(plik);
    printf("Mapa została zapisana w pliku: %s\n", nazwaPliku);
}
