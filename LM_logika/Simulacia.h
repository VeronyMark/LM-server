#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Plocha.h"
#include "Mravec.h"

#ifndef LANGTONOVMRAVEC_SIMULACIA_H
#define LANGTONOVMRAVEC_SIMULACIA_H

struct Simulacia {
    struct Plocha plocha;
    struct Mravec* zoznamMravcov;
    int pocetMravcov;
};

void nacitajAkaPlocha(struct Simulacia* simulacia, long long type, long long sirka, long long dlzka);
void pridajMravca(struct Simulacia* simulacia);
void nacitajMravcov(struct Simulacia* simulacia, long long numOfAnts);
void inicializuj(struct Simulacia* simulacia, long long type,long long numOfAnts, long long sirka, long long dlzka) ;

int nacitajPocetKrokov(struct Simulacia* simulacia);
int nacitajLogiku(struct Simulacia* simulacia);
int nacitajRiesenieKolizii(struct Simulacia* simulacia);
void vypisSmerMravca(struct Simulacia* simulacia, int x, int y);
void vypisHorizontalLine(int length);
void vypisPlochuMravcov(struct Simulacia* simulacia);
void checkAndDisableAntsAtSamePosition(struct Simulacia* self, int currentAntIndex, int x, int y);
void checkAndReverseAntsAtSamePosition(struct Simulacia* self, int currentAntIndex, int x, int y);
void otocMravca(struct Simulacia* simulacia, int logika, int farbaPola, int indexMravca);
void simulujKrok(struct Simulacia* simulacia, int j, int logika, int riesenieKolizii);
bool isAntOnIndex(struct Simulacia* simulacia, int index);
void simuluj(struct Simulacia* simulacia, long long row,  long long column,  long long numberAnts,  long long numberSteps,  long long type,  long long logic,  long long solutions );
#endif // LANGTONOVMRAVEC_SIMULACIA_H
