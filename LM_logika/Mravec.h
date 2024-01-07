#ifndef LM_SERVER_MRAVEC_H
#define LM_SERVER_MRAVEC_H

typedef struct {
    int polohaX;
    int polohaY;
    int smer; // 0 = hore | 1 = vpravo | 2 = dole | 3 = vľavo
    int disabled;
    int reverseLogic;
} Mravec;

Mravec createMravec();
int isDisabled(const Mravec *mravec);
void setDisabled(Mravec *mravec, int disabled);
int isReverseLogic(const Mravec *mravec);
void setReverseLogic(Mravec *mravec, int reverseLogic);
int getPolohaX(const Mravec *mravec);
void setPolohaX(Mravec *mravec, int polohaX);
int getPolohaY(const Mravec *mravec);
void setPolohaY(Mravec *mravec, int polohaY);
int getSmer(const Mravec *mravec);
void setSmer(Mravec *mravec, int smer);
void otocVpravo(Mravec *mravec);
void otocVlavo(Mravec *mravec);
void posunVpred(Mravec *mravec);
void vypis(const Mravec *mravec);
void vypisSmer(const Mravec *mravec);

#endif //LM_SERVER_MRAVEC_H
