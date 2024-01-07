#include "Pole.h"

void initializePole(Pole *pole, int farba) {
    pole->farba = farba;
}

int getFarba(const Pole *pole) {
    return pole->farba;
}

void zmenFarba(Pole *pole) {
    pole->farba = (pole->farba + 1) % 2;
}
