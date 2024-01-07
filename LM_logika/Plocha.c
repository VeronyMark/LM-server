#include "Plocha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vytvorPlochuRandom(Plocha *plocha) {
    int sirkaNacitana, vyskaNacitana;

    printf("Zadajte rozmery plochy ktora bude vygenerovana RANDOM: \n");
    printf("Sirka: \n");
    scanf("%d", &sirkaNacitana);
    printf("Vyska: \n");
    scanf("%d", &vyskaNacitana);

    if (0 < sirkaNacitana && sirkaNacitana < 50) plocha->sirka = sirkaNacitana;
    if (0 < vyskaNacitana && vyskaNacitana < 50) plocha->vyska = vyskaNacitana;

    int pocetPoli = plocha->sirka * plocha->vyska;
    plocha->plocha = (Pole *)malloc(pocetPoli * sizeof(Pole));

    for (int i = 0; i < pocetPoli; i++) {
        int cislo = rand() % 2;
        initializePole(&plocha->plocha[i], cislo);
    }
}

void vytvorPlochuManual(Plocha *plocha) {
    int sirkaNacitana, vyskaNacitana;

    printf("Zadajte rozmery plochy ktora bude vygenerovana MANUALNE: \n");
    printf("Sirka: \n");
    scanf("%d", &sirkaNacitana);
    printf("Vyska: \n");
    scanf("%d", &vyskaNacitana);

    if (0 < sirkaNacitana && sirkaNacitana < 50) plocha->sirka = sirkaNacitana;
    if (0 < vyskaNacitana && vyskaNacitana < 50) plocha->vyska = vyskaNacitana;

    int pocetPoli = plocha->sirka * plocha->vyska;
    plocha->plocha = (Pole *)malloc(pocetPoli * sizeof(Pole));

    for (int i = 0; i < pocetPoli; i++) {
        int cislo = 0;
        initializePole(&plocha->plocha[i], cislo);
    }

    int stop, x, y;

    while (1) {
        printf("Zadajte suradnice prvku ktory chcete nastavit na cierny:\n");
        printf("X: ");
        scanf("%d", &x);
        printf("Y: ");
        scanf("%d", &y);

        if (0 <= x && x < plocha->sirka && 0 <= y && y < plocha->vyska) zmenFarbaOnIndex(plocha, y * plocha->sirka + x);

        printf("Zadajte \n"
               "0 - dalsie pole na cierne \n"
               "1 - ukoncit zadavanie ciernych poli \n");

        scanf("%d", &stop);

        if (stop == 1)
            break;

        while (getchar() != '\n')
            ; // clear input buffer
    }
}

void vytvorPlochuSubor(Plocha *plocha, const char *subor) {
    FILE *file = fopen(subor, "r");
    if (!file) {
        fprintf(stderr, "Chyba pri otvarani suboru!\n");
        return;
    }

    fscanf(file, "%d %d", &plocha->sirka, &plocha->vyska);
    int pocetPoli = plocha->sirka * plocha->vyska;

    plocha->plocha = (Pole *)malloc(pocetPoli * sizeof(Pole));

    for (int i = 0; i < plocha->vyska; ++i) {
        for (int j = 0; j < plocha->sirka; ++j) {
            int cislo;
            fscanf(file, "%d", &cislo);
            initializePole(&plocha->plocha[i * plocha->sirka + j], cislo);
        }
    }
    fclose(file);
}

Plocha createPlocha() {
    Plocha plocha;
    plocha.sirka = 0;
    plocha.vyska = 0;
    plocha.plocha = NULL;
    return plocha;
}

Plocha createPlochaWithSize(int sirka, int vyska) {
    Plocha plocha;
    plocha.sirka = sirka;
    plocha.vyska = vyska;
    int pocetPoli = plocha.sirka * plocha.vyska;
    plocha.plocha = (Pole *)malloc(pocetPoli * sizeof(Pole));
    for (int i = 0; i < pocetPoli; i++) {
        initializePole(&plocha.plocha[i], 0);
    }
    return plocha;
}

int getSirka(const Plocha *plocha) {
    return plocha->sirka;
}

void setSirka(Plocha *plocha, int sirka) {
    plocha->sirka = sirka;
}

int getVyska(const Plocha *plocha) {
    return plocha->vyska;
}

void setVyska(Plocha *plocha, int vyska) {
    plocha->vyska = vyska;
}

int getVelkostPlochy(const Plocha *plocha) {
    return plocha->sirka * plocha->vyska;
}

void vypisPlochu(const Plocha *plocha) {
    printf("\n");
    for (int i = 0; i < (plocha->sirka * 2) - 1; i++) {
        printf("-");
    }
    printf("\n");

    int pocetPoli = plocha->sirka * plocha->vyska;
    for (int i = 0; i < pocetPoli; i++) {
        if (i > 0 && i % plocha->sirka == 0) {
            printf("\n");
        }
        if (i % plocha->sirka != 0) {
            printf("|");
        }

        int cislo = getFarba(&plocha->plocha[i]);
        printf("%d", cislo);
    }

    printf("\n");
    for (int i = 0; i < (plocha->sirka * 2) - 1; i++) {
        printf("-");
    }
}

Pole getPoleOnIndex(const Plocha *plocha, int index) {
    if (index < getVelkostPlochy(plocha)) {
        return plocha->plocha[index];
    } else {
        Pole pole;
        initializePole(&pole, 0);
        return pole;
    }
}

void zmenFarbaOnIndex(Plocha *plocha, int index) {
    if (index < getVelkostPlochy(plocha)) {
        zmenFarbaOnIndex(&plocha->plocha[index], index);
    }
}
