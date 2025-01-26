#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wynik.h"  

#define LATWY_WIERSZE 9
#define LATWY_KOLUMNY 9
#define SREDNI_WIERSZE 16
#define SREDNI_KOLUMNY 16
#define TRUDNY_WIERSZE 16
#define TRUDNY_KOLUMNY 30


#define LATWY_MINY 10
#define SREDNI_MINY 40
#define TRUDNY_MINY 99

void generujMape(int wiersze, int kolumny, int miny, int poziomTrudnosci);
void wypiszMape(char **mapa, int wiersze, int kolumny, int koniecGry);
void losujMiny(char **mapa, int wiersze, int kolumny, int x, int y, int miny);
int liczMiny(char **mapa, int wiersze, int kolumny, int x, int y);
void odkryjPole(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odsłonietePola);
void wykonajRuch(char **mapa, int wiersze, int kolumny, int x, int y, char akcja, int *koniecGry, int *odsłonietePola);
void ustawFlage(char **mapa, int x, int y);

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
            generujMape(LATWY_WIERSZE, LATWY_KOLUMNY, LATWY_MINY, 1);
            break;
        case 2:
            generujMape(SREDNI_WIERSZE, SREDNI_KOLUMNY, SREDNI_MINY, 2);
            break;
        case 3:
            generujMape(TRUDNY_WIERSZE, TRUDNY_KOLUMNY, TRUDNY_MINY, 3);
            break;
        default:
            printf("Nieprawidlowy wybor!\n");
            return 1;
    }

    return 0;
}

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
        scanf(" %c %d %d", &akcja, &x, &y);

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
    }

    printf("Koniec gry!\n");
}

void wypiszMape(char **mapa, int wiersze, int kolumny, int koniecGry) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            
            if (koniecGry && mapa[i][j] == 'M') {
                printf("M ");
            } else if (mapa[i][j] == 'M') {
                
                printf(". ");
            } else {
                printf("%c ", mapa[i][j]);
            }
        }
        printf("\n");
    }
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

int liczMiny(char **mapa, int wiersze, int kolumny, int x, int y) {
    int liczbaMin = 0;

    // Sprawdzamy pola
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && mapa[nx][ny] == 'M') {
                liczbaMin++;
            }
        }
    }

    return liczbaMin;
}

void odkryjPole(char **mapa, int wiersze, int kolumny, int x, int y, int *koniecGry, int *odsłonietePola) {
    if (mapa[x][y] == '.') {
        
        int liczbaMin = liczMiny(mapa, wiersze, kolumny, x, y);
        mapa[x][y] = '0' + liczbaMin;  
        (*odsłonietePola)++;  
    } else if (mapa[x][y] == 'F') {
        
        printf("Pole oznaczone flagą!\n");
    } else if (mapa[x][y] == 'M') {
        *koniecGry = 1;  
    } else {
        
        printf("To pole jest już odkryte!\n");
    }
}

void wykonajRuch(char **mapa, int wiersze, int kolumny, int x, int y, char akcja, int *koniecGry, int *odsłonietePola) {
    if (akcja == 'r') {
        odkryjPole(mapa, wiersze, kolumny, x, y, koniecGry, odsłonietePola);
    } else if (akcja == 'f') {
        ustawFlage(mapa, x, y);  
    }
}

void ustawFlage(char **mapa, int x, int y) {
    if (mapa[x][y] == '.') {
        mapa[x][y] = 'F';  
        printf("Flaga ustawiona na polu (%d, %d)\n", x, y);
    } else if (mapa[x][y] == 'F') {
        mapa[x][y] = '.';  
        printf("Flaga usunięta z pola (%d, %d)\n", x, y);
    } else {
        printf("To pole jest już odkryte lub zawiera minę, nie można ustawić flagi.\n");
    }
}

