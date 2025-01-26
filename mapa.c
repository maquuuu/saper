#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LATWY_WIERSZE 9
#define LATWY_KOLUMNY 9
#define LATWY_MINY 10

#define SREDNI_WIERSZE 16
#define SREDNI_KOLUMNY 16
#define SREDNI_MINY 40

#define TRUDNY_WIERSZE 16
#define TRUDNY_KOLUMNY 30
#define TRUDNY_MINY 99

char **generujMape(int wiersze, int kolumny, int miny);
void wypiszMape(char **mapa, int wiersze, int kolumny);
void zwolnijMape(char **mapa, int wiersze);

int main() {
    int wybor;
    int wiersze, kolumny, miny;
    char **mapa;

    printf("Wybierz poziom trudnosci:\n");
    printf("1. Latwy (9x9, 10 min)\n");
    printf("2. Sredni (16x16, 40 min)\n");
    printf("3. Trudny (16x30, 99 min)\n");
    printf("Podaj numer: ");
    if (scanf("%d", &wybor) != 1) {
        fprintf(stderr, "Błąd: nieprawidłowe dane wejściowe!\n");
        return 1;
    }

    switch (wybor) {
        case 1:
            wiersze = LATWY_WIERSZE;
            kolumny = LATWY_KOLUMNY;
            miny = LATWY_MINY;
            break;
        case 2:
            wiersze = SREDNI_WIERSZE;
            kolumny = SREDNI_KOLUMNY;
            miny = SREDNI_MINY;
            break;
        case 3:
            wiersze = TRUDNY_WIERSZE;
            kolumny = TRUDNY_KOLUMNY;
            miny = TRUDNY_MINY;
            break;
        default:
            printf("Nieprawidlowy wybor!\n");
            return 1;
    }

    mapa = generujMape(wiersze, kolumny, miny);
    if (mapa == NULL) {
        fprintf(stderr, "Błąd: nie udało się utworzyć mapy!\n");
        return 1;
    }

    wypiszMape(mapa, wiersze, kolumny);

    zwolnijMape(mapa, wiersze);

    return 0;
}

char **generujMape(int wiersze, int kolumny, int miny) {
    char **mapa = malloc(wiersze * sizeof(char *));
    if (mapa == NULL) {
        fprintf(stderr, "Błąd: nie udało się przydzielić pamięci dla wierszy mapy!\n");
        return NULL;
    }

    for (int i = 0; i < wiersze; i++) {
        mapa[i] = malloc(kolumny * sizeof(char));
        if (mapa[i] == NULL) {
            fprintf(stderr, "Błąd: nie udało się przydzielić pamięci dla kolumn mapy w wierszu %d!\n", i);
            zwolnijMape(mapa, i);
            return NULL;
        }
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

    return mapa;
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

void zwolnijMape(char **mapa, int wiersze) {
    for (int i = 0; i < wiersze; i++) {
        free(mapa[i]);
    }
    free(mapa);
}
