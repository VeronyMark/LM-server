#include "Mravec.h"
#include <stdio.h>

struct Mravec createMravec(int startX, int startY) {
    struct Mravec newMravec;
    newMravec.polohaX = startX;
    newMravec.polohaY = startY;
    newMravec.smer = 0;
    newMravec.disabled = 0;
    newMravec.reverseLogic = 0;

    return newMravec;
}

int isDisabled(const struct Mravec *mravec) {
    return mravec->disabled;
}

void setDisabled(struct Mravec *mravec, int disabled) {
    mravec->disabled = disabled;
}

int isReverseLogic(const struct Mravec *mravec) {
    return mravec->reverseLogic;
}

void setReverseLogic(struct Mravec *mravec, int reverseLogic) {
    mravec->reverseLogic = reverseLogic;
}

int getPolohaX(const struct Mravec *mravec) {
    return mravec->polohaX;
}

void setPolohaX(struct Mravec *mravec, int polohaX) {
    mravec->polohaX = polohaX;
}

int getPolohaY(const struct Mravec *mravec) {
    return mravec->polohaY;
}

void setPolohaY(struct Mravec *mravec, int polohaY) {
    mravec->polohaY = polohaY;
}

int getSmer(const struct Mravec *mravec) {
    return mravec->smer;
}

void setSmer(struct Mravec *mravec, int smer) {
    mravec->smer = smer;
}

void otocVpravo(struct Mravec *mravec) {
    mravec->smer = (mravec->smer + 1) % 4;
}

void otocVlavo(struct Mravec *mravec) {
    mravec->smer = (mravec->smer + 3) % 4;
}

void posunVpred(struct Mravec *mravec) {
    if (mravec->smer == 0) mravec->polohaY--;
    else if (mravec->smer == 1) mravec->polohaX++;
    else if (mravec->smer == 2) mravec->polohaY++;
    else if (mravec->smer == 3) mravec->polohaX--;
}

void vypis(const struct Mravec *mravec) {
    printf("\nPoloha X: %d\n", mravec->polohaX);
    printf("Poloha Y: %d\n", mravec->polohaY);
    printf("Smer: %d\n\n", mravec->smer);
}

void vypisSmer(const struct Mravec *mravec) {
    if (mravec->smer == 0) printf("^");
    if (mravec->smer == 1) printf(">");
    if (mravec->smer == 2) printf("v");
    if (mravec->smer == 3) printf("<");
}
