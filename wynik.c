#include <stdio.h>
#include <string.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

void obliczWynik(int ods³onietePola, int poziomTrudnosci) {
    int wynik = ods³onietePola* poziomTrudnosci;
    printf("Aktualny wynik: %d\n", wynik);
}
void najlepsiGracze() {
    FILE *plik = fopen("leaderboard.txt", "r");
    if (!plik) {
        printf("Nie uda³o siê otworzyæ pliku leaderboard.txt.\n");
        return;
    }

    char linia[256];
    char nazwy[MAX_GRACZY][MAX_NAZWA];
    int wyniki[MAX_GRACZY];
    int liczbaGraczy = 0;

    while (fgets(linia, sizeof(linia), plik)) {
    if (sscanf(linia, "Gracz: %49s | Wynik: %d", nazwy[liczbaGraczy], &wyniki[liczbaGraczy]) == 2) {
        liczbaGraczy++;
        if (liczbaGraczy >= MAX_GRACZY) {
            break;
        }
    } else {
        printf("Nieprawid³owy format: %s\n", linia);
    }
}
    fclose(plik);
    for (int i = 0; i < liczbaGraczy - 1; i++) {
        for (int j = i + 1; j < liczbaGraczy; j++) {
            if (wyniki[i] < wyniki[j]) {
                int tempWynik = wyniki[i];
                wyniki[i] = wyniki[j];
                wyniki[j] = tempWynik;

                char tempNazwa[MAX_NAZWA];
                strcpy(tempNazwa, nazwy[i]);
                strcpy(nazwy[i], nazwy[j]);
                strcpy(nazwy[j], tempNazwa);
            }
        }
    }
    if (liczbaGraczy == 0) {
        printf("Brak wyników w leaderboardzie.\n");
        return;
    }
    printf("=== Najlepsi gracze ===\n");
    printf("dasdaw%d\n", liczbaGraczy);
    int top = liczbaGraczy < 5 ? liczbaGraczy : 5;
    for (int i = 0; i < top; i++) {
        printf("%d. %s - %d punktów\n", i + 1, nazwy[i], wyniki[i]);
    }
}
