#include "Mravec.h"
#include <stdio.h>

int isDisabled(const Mravec *mravec) {
    return mravec->disabled;
}

void setDisabled(Mravec *mravec, int disabled) {
    mravec->disabled = disabled;
}

int isReverseLogic(const Mravec *mravec) {
    return mravec->reverseLogic;
}

void setReverseLogic(Mravec *mravec, int reverseLogic) {
    mravec->reverseLogic = reverseLogic;
}

int getPolohaX(const Mravec *mravec) {
    return mravec->polohaX;
}

void setPolohaX(Mravec *mravec, int polohaX) {
    mravec->polohaX = polohaX;
}

int getPolohaY(const Mravec *mravec) {
    return mravec->polohaY;
}

void setPolohaY(Mravec *mravec, int polohaY) {
    mravec->polohaY = polohaY;
}

int getSmer(const Mravec *mravec) {
    return mravec->smer;
}

void setSmer(Mravec *mravec, int smer) {
    mravec->smer = smer;
}

void otocVpravo(Mravec *mravec) {
    mravec->smer = (mravec->smer + 1) % 4;
}

void otocVlavo(Mravec *mravec) {
    mravec->smer = (mravec->smer + 3) % 4;
}

void posunVpred(Mravec *mravec) {
    if (mravec->smer == 0) mravec->polohaY--;
    else if (mravec->smer == 1) mravec->polohaX++;
    else if (mravec->smer == 2) mravec->polohaY++;
    else if (mravec->smer == 3) mravec->polohaX--;
}

void vypis(const Mravec *mravec) {
    printf("\nPoloha X: %d\n", mravec->polohaX);
    printf("Poloha Y: %d\n", mravec->polohaY);
    printf("Smer: %d\n\n", mravec->smer);
}

void vypisSmer(const Mravec *mravec) {
    if (mravec->smer == 0) printf("^");
    if (mravec->smer == 1) printf(">");
    if (mravec->smer == 2) printf("v");
    if (mravec->smer == 3) printf("<");
}
