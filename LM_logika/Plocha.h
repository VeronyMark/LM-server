#ifndef LANGTONOVMRAVEC_PLOCHA_H
#define LANGTONOVMRAVEC_PLOCHA_H

#include "Pole.h"

struct Plocha {
    long long sirka;
    long long vyska;
    struct Pole *plocha;
};

void vytvorPlochuRandom(struct Plocha *plocha, long long sirkaNacitana, long long vyskaNacitana);
void vytvorPlochuManual(struct Plocha *plocha);
void inicializujPlochu(struct Plocha *plocha, int randomOrManualOrFile, long long sirkaNacitana, long long vyskaNacitana);
void zrusPlochu(struct Plocha *plocha);
void vypisPlochu(const struct Plocha *plocha);
struct Pole getPoleOnIndex(const struct Plocha *plocha, int index);
void zmenFarbaOnIndex(struct Plocha *plocha, int index);

#endif // LANGTONOVMRAVEC_PLOCHA_H
