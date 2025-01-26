#include <stdio.h>
#include <string.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"

void obliczWynik(int odslonietePola, int poziomTrudnosci) {
    int wynik = odslonietePola* poziomTrudnosci;
    printf("Aktualny wynik: %d\n", wynik);
}
void najlepsiGracze() {
    FILE *plik = fopen("leaderboard.txt", "r");
    if (!plik) {
        printf("Nie udalo sie otworzyc pliku leaderboard.txt.\n");
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
        printf("Nieprawidlowy format: %s\n", linia);
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
    printf("%d\n", liczbaGraczy);
    int top = liczbaGraczy < 5 ? liczbaGraczy : 5;
    for (int i = 0; i < top; i++) {
        printf("%d. %s - %d punktow\n", i + 1, nazwy[i], wyniki[i]);
    }
}
