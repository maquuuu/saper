#include <stdio.h>
#include "mapa.h"
#include "ruch.h"
#include "wynik.h"
#include "common.h"
#include "interak.h"
#include "zapis.h"

void wykonajRuch(char **mapa, char **widocznaMapa, int wiersze, int kolumny, int x, int y, char akcja, int *koniecGry, int *odslonietePola) {
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny) {
        printf("Poza zakresem mapy!\n");
        return;
    }

    if (akcja == 'r') {
        odkryjPole(mapa, widocznaMapa, wiersze, kolumny, x, y, koniecGry, odslonietePola);
    } else if (akcja == 'f') {
        ustawFlage(mapa, widocznaMapa, x, y);
    } else {
        printf("Nieznana akcja! Uzyj 'r' do odkrycia lub 'f' do oznaczenia pola.\n");
    }
}