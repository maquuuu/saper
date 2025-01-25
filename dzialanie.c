#include "dzialanie.h"
#include <stdio.h>

void wykonajRuch(char **mapa, int wiersze, int kolumny, int x, int y, char akcja) {
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny) {
        printf("Nieprawidlowe wspolrzedne!\n");
        return;
    }

    if (akcja == 'f') {
        ustawFlage(mapa, x, y);
    } else if (akcja == 'r') {
        odkryjPole(mapa, x, y);
    } else {
        printf("Nieprawidlowa akcja!\n");
    }
}

void ustawFlage(char **mapa, int x, int y) {
    if (mapa[x][y] == 'F') {
        mapa[x][y] = '.';
    } else if (mapa[x][y] == '.') {
        mapa[x][y] = 'F';
    } else {
        printf("Nie mozna ustawic flagi na odkrytym polu!\n");
    }
}

void odkryjPole(char **mapa, int x, int y) {
    if (mapa[x][y] == 'M') {
        printf("Trafiles na mine. Gra skonczona!\n");
        exit(0);
    } else if (mapa[x][y] == '.') {
        mapa[x][y] = 'O';
    } else if (mapa[x][y] == 'F') {
        printf("Pole oznaczone flaga!\n");
    } else {
        printf("To pole jest juz odkryte!\n");
    }
}

