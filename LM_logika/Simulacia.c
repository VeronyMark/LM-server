// Simulacia.c

#include "Simulacia.h"
#include <stdio.h>
#include <stdlib.h>



void pridajMravca(struct Simulacia* simulacia) {
    int startx = rand() % simulacia->plocha.sirka;
    int starty = rand() % simulacia->plocha.vyska;
    struct Mravec mravecNovy = createMravec(startx, starty);
    simulacia->zoznamMravcov[simulacia->pocetMravcov++] = mravecNovy;
}

void nacitajMravcov(struct Simulacia* simulacia, long long numOfAnts) {


    simulacia->zoznamMravcov = (struct Mravec *)malloc(numOfAnts * sizeof(struct Mravec));

    if (simulacia->zoznamMravcov == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed for zoznamMravcov\n");
        exit(EXIT_FAILURE);
    }

    simulacia->pocetMravcov = numOfAnts;

    for (int i = 0; i < numOfAnts; ++i) {
        pridajMravca(simulacia);
    }
}

void nacitajAkaPlocha(struct Simulacia* simulacia, long long type, long long sirka, long long dlzka) {
    inicializujPlochu(&(simulacia->plocha), type, sirka, dlzka);
}
void inicializuj(struct Simulacia* simulacia, long long type,long long numOfAnts,  long long sirka, long long dlzka) {
    //inicializujPlochu(&(simulacia->plocha), type);
    nacitajAkaPlocha(simulacia, type, sirka, dlzka);
    //nacitajMravcov(simulacia);

    simulacia->zoznamMravcov = (struct Mravec *)malloc(numOfAnts * sizeof(struct Mravec));

    if (simulacia->zoznamMravcov == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed for zoznamMravcov\n");
        exit(EXIT_FAILURE);
    }

    simulacia->pocetMravcov = numOfAnts;

    for (int i = 0; i < numOfAnts; ++i) {
        pridajMravca(simulacia);
    }
}


void vypisSmerMravca(struct Simulacia* simulacia, int x, int y) {
    int mravecFound = 0;
    for (int j = 0; j < simulacia->pocetMravcov; j++) {
        int wrappedX = (simulacia->zoznamMravcov[j].polohaX + simulacia->plocha.sirka) % simulacia->plocha.sirka;
        int wrappedY = (simulacia->zoznamMravcov[j].polohaY + simulacia->plocha.vyska) % simulacia->plocha.vyska;

        if (wrappedX == x && wrappedY == y && !simulacia->zoznamMravcov[j].disabled) {
            vypisSmer(&(simulacia->zoznamMravcov[j]));
            mravecFound = 1;
            break;
        }
    }
    if (!mravecFound) {
        printf(".");
    }
}

void vypisHorizontalLine(int length) {
    for (int i = 0; i < (length * 2) - 1; i++) {
        printf("-");
    }
    printf("\n");
}

void vypisPlochuMravcov(struct Simulacia* simulacia) {
    printf("\n");
    vypisHorizontalLine(simulacia->plocha.sirka);

    for (int y = 0; y < simulacia->plocha.vyska; y++) {
        for (int x = 0; x < simulacia->plocha.sirka; x++) {
            if (x > 0) {
                printf("|");
            }
            vypisSmerMravca(simulacia, x, y);
        }
        printf("\n");
    }

    vypisHorizontalLine(simulacia->plocha.sirka);
    printf("\n");
}

void checkAndDisableAntsAtSamePosition(struct Simulacia* simulacia, int currentAntIndex, int x, int y) {

    for (int k = 0; k < simulacia->pocetMravcov; ++k) {
        if (k != currentAntIndex && !simulacia->zoznamMravcov[k].disabled) {
            int wrappedX = (simulacia->zoznamMravcov[k].polohaX + simulacia->plocha.sirka) % simulacia->plocha.sirka;
            int wrappedY = (simulacia->zoznamMravcov[k].polohaY + simulacia->plocha.vyska) % simulacia->plocha.vyska;

            if (wrappedX == x && wrappedY == y) {
                simulacia->zoznamMravcov[currentAntIndex].disabled = (true);
            }
        }
    }
}

void checkAndReverseAntsAtSamePosition(struct Simulacia* simulacia, int currentAntIndex, int x, int y) {

    for (int k = 0; k < simulacia->pocetMravcov; ++k) {
        if (k != currentAntIndex && !simulacia->zoznamMravcov[k].reverseLogic) {
            int wrappedX = (simulacia->zoznamMravcov[k].polohaX + simulacia->plocha.sirka) % simulacia->plocha.sirka;
            int wrappedY = (simulacia->zoznamMravcov[k].polohaY + simulacia->plocha.vyska) % simulacia->plocha.vyska;
            if (wrappedX == x && wrappedY == y) {
                setReverseLogic(&(simulacia->zoznamMravcov[currentAntIndex]), simulacia->zoznamMravcov[currentAntIndex].reverseLogic % 2);
            }
        }
    }
}

void otocMravca(struct Simulacia* simulacia, int logika, int farbaPola, int indexMravca) {
    if (logika == 0) {
        if (farbaPola == 0) {
            otocVpravo(&(simulacia->zoznamMravcov[indexMravca]));
        }
        if (farbaPola == 1) {
            otocVlavo(&(simulacia->zoznamMravcov[indexMravca]));
        }
    } else if (logika == 1) {
        if (farbaPola == 0) {
            otocVlavo(&(simulacia->zoznamMravcov[indexMravca]));
        }
        if (farbaPola == 1) {
            otocVpravo(&(simulacia->zoznamMravcov[indexMravca]));
        }
    }
}

void simulujKrok(struct Simulacia* simulacia, int j, int logika, int riesenieKolizii) {
    int mravecX = simulacia->zoznamMravcov[j].polohaX;
    int mravecY = simulacia->zoznamMravcov[j].polohaY;
    int index = mravecY * simulacia->plocha.sirka + mravecX;
    struct Pole pole = getPoleOnIndex(&(simulacia->plocha), index);
    int color = getFarba(&pole);
    if (riesenieKolizii == 0) {
        checkAndDisableAntsAtSamePosition(simulacia, j, mravecX, mravecY);
    }
    if (riesenieKolizii == 1) {
        checkAndReverseAntsAtSamePosition(simulacia, j, mravecX, mravecY);
    }
    otocMravca(simulacia, logika, color, j);
    zmenFarbaOnIndex(&(simulacia->plocha), index);
    posunVpred(&(simulacia->zoznamMravcov[j]));
    setPolohaX(&(simulacia->zoznamMravcov[j]), (getPolohaX(&(simulacia->zoznamMravcov[j])) + simulacia->plocha.sirka) % simulacia->plocha.sirka);
    setPolohaY(&(simulacia->zoznamMravcov[j]), (getPolohaY(&(simulacia->zoznamMravcov[j])) + simulacia->plocha.vyska) % simulacia->plocha.vyska);
}

bool isAntOnIndex(struct Simulacia* simulacia, int index) {
    int width = simulacia->plocha.sirka;
    int height = simulacia->plocha.vyska;
    int x = index % width;
    int y = index / width;
    for (int j = 0; j < simulacia->pocetMravcov; ++j) {
        int wrappedX = (getPolohaX(&(simulacia->zoznamMravcov[j])) + width) % width;
        int wrappedY = (getPolohaY(&(simulacia->zoznamMravcov[j])) + height) % height;

        if (wrappedX == x && wrappedY == y && !simulacia->zoznamMravcov[j].disabled) {
            return true;
        }
    }
    return false;
}


void simuluj(struct Simulacia* simulacia,  long long row,  long long column,  long long numberAnts,  long long numberSteps,  long long type,  long long logic,  long long solutions ) {
    inicializuj(simulacia, type, numberAnts, row, column );
    int pocetKrokov = numberSteps;// nacitajPocetKrokov(simulacia);
    int logika = logic;// nacitajLogiku(simulacia);
    int riesenieKolizii = solutions;// nacitajRiesenieKolizii(simulacia);
    vypisPlochu(&(simulacia->plocha));
    vypisPlochuMravcov(simulacia);

    for (int i = 0; i < pocetKrokov; ++i) {

        for (int j = 0; j < simulacia->pocetMravcov; ++j) {

            if (riesenieKolizii == 0) {
                if (!simulacia->zoznamMravcov[j].disabled) {

                    simulujKrok(simulacia, j, logika, riesenieKolizii);
                }
            }
            if (riesenieKolizii == 1) {
                if (!simulacia->zoznamMravcov[j].reverseLogic) {

                    simulujKrok(simulacia, j, logika, riesenieKolizii);
                }
                if (simulacia->zoznamMravcov[j].reverseLogic) {
                    int opacnaLogika = (logika + 1) % 2;
                    simulujKrok(simulacia, j, opacnaLogika, riesenieKolizii);
                }
            }
        }
        printf("\n\n");
        printf("KROK: %d\n", i);
        vypisPlochu(&(simulacia->plocha));
        vypisPlochuMravcov(simulacia);
        printf("\n");
    }
    zrusPlochu(&(simulacia->plocha));
    free(simulacia->zoznamMravcov);

}
