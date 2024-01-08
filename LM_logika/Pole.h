#ifndef LANGTONOVMRAVEC_POLE_H
#define LANGTONOVMRAVEC_POLE_H

struct Pole {
    int farba; // 0 = biela | 1 = cierna
};

void initPole(struct Pole *pole, int farba);
int getFarba(const struct Pole *pole);
void zmenFarba(struct Pole *pole);

#endif // LANGTONOVMRAVEC_POLE_H