#include <stdio.h>
#include <stdlib.h>
#include "dzialanie.h"
#include "mapa.h"
void poruszajSie(char **mapa, int wiersze, int kolumny) {
    int x = 0, y = 0;
    char akcja;

    while (1) {
        system("clear");
        wypiszMape(mapa, wiersze, kolumny);
        printf("Aktualna pozycja: (%d, %d)\n", x, y);
        printf("Wybierz akcję:\n");
        printf("w - góra, s - dół, a - lewo, d - prawo\n");
        printf("f - ustaw flage, r - odkryj pole, q - wyjście\n");
        printf("Twoja akcja: ");
        scanf(" %c", &akcja);

        if (akcja == 'q') {
            printf("Zakończono grę.\n");
            break;
        }

        switch (akcja) {
            case 'w':
                if (x > 0) x--;
                else printf("Nie możesz iść wyżej!\n");
                break;
            case 's':
                if (x < wiersze - 1) x++;
                else printf("Nie możesz iść niżej!\n");
                break;
            case 'a':
                if (y > 0) y--;
                else printf("Nie możesz iść bardziej w lewo!\n");
                break;
            case 'd':
                if (y < kolumny - 1) y++;
                else printf("Nie możesz iść bardziej w prawo!\n");
                break;
            case 'f':
            case 'r':
                wykonajRuch(mapa, wiersze, kolumny, x, y, akcja);
                break;
            default:
                printf("Nieprawidłowa akcja!\n");
        }
    }
}
