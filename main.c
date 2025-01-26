#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

int main(int argc, char *argv[]) {
    int wiersze = 0, kolumny = 0, miny = 0, opcja;
    int tryb_wlasny = 0;

    printf("Poziom trudnosci:\n");
    printf("1. Latwy (9x9)\n");
    printf("2. Sredni (16x16)\n");
    printf("3. Trudny (16x30)\n");
    printf("4. W³asny (kxw)\n");

    while ((opcja = getopt(argc, argv, "1234")) != -1) {
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
            default:
                printf("Nieprawidlowy wybór!\n");
                return 1;
        }
    }

    if (tryb_wlasny) {
        printf("Wybra³eœ tryb w³asny.\n");
        while (kolumny <= 0) {
            printf("Podaj liczbê kolumn (wiêksz¹ od 0): ");
            scanf("%d", &kolumny);
        }
        while (wiersze <= 0) {
            printf("Podaj liczbê wierszy (wiêksz¹ od 0): ");
            scanf("%d", &wiersze);
        }
        while (miny <= 0 || miny >= wiersze * kolumny) {
            printf("Podaj liczbê min (wiêksz¹ od 0 i mniejsz¹ ni¿ liczba pól %d): ", wiersze * kolumny);
            scanf("%d", &miny);
        }
        if (wiersze == 0 || kolumny == 0 || miny == 0) {
            printf("Nieprawid³owy wybór!");
            return 1;
        } else {
            generujMape(wiersze, kolumny, miny, 0);
        }
    }

    return 0;
}

