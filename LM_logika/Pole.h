#ifndef LM_SERVER_POLE_H
#define LM_SERVER_POLE_H

typedef struct {
    int farba; // 0 = biela | 1 = cierna
} Pole;

void initializePole(Pole *pole, int farba);
int getFarba(const Pole *pole);
void zmenFarba(Pole *pole);

#endif //LM_SERVER_POLE_H
