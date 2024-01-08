struct Mravec {
    int polohaX;
    int polohaY;
    int smer; // 0 = hore | 1 = vpravo | 2 = dole | 3 = vľavo
    int disabled; // 0 or 1 (bool)
    int reverseLogic; // 0 or 1 (bool)
};

struct Mravec createMravec(int startX, int startY);
int isDisabled(const struct Mravec *mravec);
void setDisabled(struct Mravec *mravec, int disabled);
int isReverseLogic(const struct Mravec *mravec);
void setReverseLogic(struct Mravec *mravec, int reverseLogic);
int getPolohaX(const struct Mravec *mravec);
void setPolohaX(struct Mravec *mravec, int polohaX);
int getPolohaY(const struct Mravec *mravec);
void setPolohaY(struct Mravec *mravec, int polohaY);
int getSmer(const struct Mravec *mravec);
void setSmer(struct Mravec *mravec, int smer);
void otocVpravo(struct Mravec *mravec);
void otocVlavo(struct Mravec *mravec);
void posunVpred(struct Mravec *mravec);
void vypis(const struct Mravec *mravec);
void vypisSmer(const struct Mravec *mravec);


