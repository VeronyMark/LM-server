#include "Plocha.h"
#include <stdio.h>
#include <stdlib.h>

void vytvorPlochuRandom(struct Plocha *plocha, long long sirkaNacitana, long long vyskaNacitana) {
    /*  int sirkaNacitana, vyskaNacitana;

      printf("Zadajte rozmery plochy ktora bude vygenerovana RANDOM:\n");
      printf("Sirka: ");
      scanf("%d", &sirkaNacitana);
      printf("Vyska: ");
      scanf("%d", &vyskaNacitana);
  */
    plocha->sirka = (0 < sirkaNacitana && sirkaNacitana < 50) ? sirkaNacitana : 50;
    plocha->vyska = (0 < vyskaNacitana && vyskaNacitana < 50) ? vyskaNacitana : 50;

    for (int i = 0; i < plocha->sirka * plocha->vyska; i++) {
        initPole(&plocha->plocha[i], rand() % 2);
    }
}

void vytvorPlochuManual(struct Plocha *plocha) {
    int i;
    plocha->sirka = 50;
    plocha->vyska = 50;

    plocha->plocha = (struct Pole *)malloc(plocha->sirka * plocha->vyska * sizeof(struct Pole));

    if (plocha->plocha == NULL) {
        fprintf(stderr, "Memory allocation failed MANUAL\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < plocha->sirka * plocha->vyska; i++) {
        initPole(&plocha->plocha[i], 0); // Initialize with 0 for simplicity
    }

    int stop, x, y;

    while (1) {
        printf("Zadajte suradnice prvku ktory chcete nastavit na cierny:\n");
        printf("X: ");
        if (scanf("%d", &x) != 1) {
            fprintf(stderr, "Invalid input for X\n");
            exit(EXIT_FAILURE);
        }
        printf("Y: ");
        if (scanf("%d", &y) != 1) {
            fprintf(stderr, "Invalid input for Y\n");
            exit(EXIT_FAILURE);
        }

        if (0 <= x && x < plocha->sirka && 0 <= y && y < plocha->vyska) {
            zmenFarba(&plocha->plocha[y * plocha->sirka + x]);
        }

        printf("Zadajte\n"
               "0 - dalsie pole na cierne\n"
               "1 - ukoncit zadavanie ciernych poli\n");

        scanf("%d", &stop);

        if (stop == 1) {
            break;
        }

        fflush(stdin);
    }
}

void inicializujPlochu(struct Plocha *plocha, int randomOrManualOrFile,long long sirkaNacitana, long long vyskaNacitana) {
    plocha->sirka = sirkaNacitana;
    plocha->vyska = vyskaNacitana;
    plocha->plocha = (struct Pole *)malloc(plocha->sirka * plocha->vyska * sizeof(struct Pole));

    //plocha->plocha = (struct Pole *)malloc(plocha->sirka * plocha->vyska * sizeof(struct Pole));

    if (plocha->plocha == NULL) {
        fprintf(stderr, "Memory allocation failed INICIALIZACIA\n");
        exit(EXIT_FAILURE);
    }

    if (randomOrManualOrFile == 0) {
        vytvorPlochuRandom(plocha, sirkaNacitana, vyskaNacitana);
    } else if (randomOrManualOrFile == 1) {
        vytvorPlochuManual(plocha);
    }
}

void zrusPlochu(struct Plocha *plocha) {
    free(plocha->plocha);
    plocha->plocha = NULL;
}

void vypisPlochu(const struct Plocha *plocha) {
    int i;

    printf("\n");
    for (i = 0; i < (plocha->sirka * 2) - 1; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < plocha->sirka * plocha->vyska; i++) {
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
    for (i = 0; i < (plocha->sirka * 2) - 1; i++) {
        printf("-");
    }
}

struct Pole getPoleOnIndex(const struct Plocha *plocha, int index) {
    return plocha->plocha[index];
}

void zmenFarbaOnIndex(struct Plocha *plocha, int index) {
    zmenFarba(&plocha->plocha[index]);
}
