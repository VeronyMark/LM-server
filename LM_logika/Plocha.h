#include "Pole.h"

#ifndef LM_SERVER_PLOCHA_H
#define LM_SERVER_PLOCHA_H

typedef struct {
    int sirka;
    int vyska;
    Pole *plocha;
} Plocha;

Plocha createPlocha();
Plocha createPlochaWithSize(int sirka, int vyska);
void vytvorPlochuRandom(Plocha *plocha);
void vytvorPlochuManual(Plocha *plocha);
void vytvorPlochuSubor(Plocha *plocha, const char *subor);
int getSirka(const Plocha *plocha);
void setSirka(Plocha *plocha, int sirka);
int getVyska(const Plocha *plocha);
void setVyska(Plocha *plocha, int vyska);
int getVelkostPlochy(const Plocha *plocha);
void vypisPlochu(const Plocha *plocha);
Pole getPoleOnIndex(const Plocha *plocha, int index);
void zmenFarbaOnIndex(Plocha *plocha, int index);

#endif //LM_SERVER_PLOCHA_H
