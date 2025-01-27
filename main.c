#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"
#include "zapis.h"

int main(int argc, char *argv[]) {
    int wiersze = 0, kolumny = 0, miny = 0, opcja;
    int tryb_wlasny = 0;
    char *plik = NULL;

    printf("Poziom trudnosci:\n");
    printf("1. Latwy (9x9)\n");
    printf("2. Sredni (16x16)\n");
    printf("3. Trudny (16x30)\n");
    printf("4. Wlasny (kxw)\n");
    printf("f. Wczytywanie gry z pliku.(-f <plik>)\n");

    while ((opcja = getopt(argc, argv, "1234f:")) != -1) {
        switch (opcja) {
            case '1':
                generujMape(LATWY_WIERSZE, LATWY_KOLUMNY, LATWY_MINY, 1);
                break;
            case '2':
                generujMape(SREDNI_WIERSZE, SREDNI_KOLUMNY, SREDNI_MINY, 2);
                break;
            case '3':
                generujMape(TRUDNY_WIERSZE, TRUDNY_KOLUMNY, TRUDNY_MINY, 3);
                break;
            case '4':
                tryb_wlasny = 1;
                break;
            case 'f':
                plik = optarg;
                break;
            default:
                printf("Nieprawidlowy wybor!\n");
                return 1;
        }
    }
    if (plik != NULL) {
        wczytajZPliku(plik);
        return 0;
    }
   if (tryb_wlasny) {
    printf("Wybrales tryb wlasny.\n");
    while (kolumny <= 0) {
        printf("Podaj liczbe kolumn (wieksze od 0): ");
        if (scanf("%d", &kolumny) != 1) {
            printf("Niepoprawny format! Podaj liczbe calkowita.\n");
            while (getchar() != '\n');
            kolumny = 0;
        }
    }
    while (wiersze <= 0) {
        printf("Podaj liczbe wierszy (wieksze od 0): ");
        if (scanf("%d", &wiersze) != 1) {
            printf("Niepoprawny format! Podaj liczbe calkowita.\n");
            while (getchar() != '\n');
            wiersze = 0;
        }
    }
    while (miny <= 0 || miny >= wiersze * kolumny) {
        printf("Podaj liczbe min (wieksze od 0 i mniejsze niz liczba pol %d): ", wiersze * kolumny);
        if (scanf("%d", &miny) != 1) {
            printf("Niepoprawny format! Podaj liczbe calkowita.\n");
            while (getchar() != '\n');
            miny = 0;
        }
    }
    if (wiersze == 0 || kolumny == 0 || miny == 0) {
        printf("Nieprawidlowy wybor!");
        return 1;
    } else {
        generujMape(wiersze, kolumny, miny, 0);
    }
}

    return 0;
}
