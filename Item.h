#ifndef THEWALK_REFACTOR_ITEM_H
#define THEWALK_REFACTOR_ITEM_H

#include "StructuriHelper.h"
#include <iostream>

class Item {
protected:
    Punct pozitie;
    ItemSimbol simbol;
    TipItem tip;
public:
    Item() {
        pozitie.x = 0;
        pozitie.y = 0;
    };

    Item &operator = (const Item &i) {
        pozitie = i.pozitie;
        simbol = i.simbol;
        tip = i.tip;
    }

    TipItem GetTip() { return tip; }

    virtual void Foloseste(Robot *r) = 0;
    friend class Harta;
    friend class Giga;
    friend class Ultra;
    friend class Mega;

};

class PotiuneInvincibilitate : public Item {
private:
    int counter = 0;
public:
    PotiuneInvincibilitate() : Item() {
        simbol = POTIUNE_INVINCIBILITATE;
        counter = 3;
        tip = ACTIV;
    }
    void Foloseste(Robot *r) {
        if(counter != 0) {
            std::cout << "Mai ai " << counter-- << " capcane pe care le poti evita!\n";
        } else if(counter == 0){
            r->SetItem(nullptr);
        }
    }
};

class PotiuneVedere : public Item {
private:
    int counter;
public:
    PotiuneVedere() : Item() {
        simbol = POTIUNE_VEDERE;
        counter = 3;
        tip = ACTIV;
    }
    void Foloseste(Robot *r) {
        std::cout<<"Am ajuns aici!";
        if(counter != 0) {
            std::cout << "Mai ai " << counter-- << " capcane pe care poti pasi fara sa mori si astfel iti vei extinde vederea!\n";
            r->AddRange();
        } else if(counter == 0) {
            r->SetItem(nullptr);
        }
    }
};

class PapuciSaltareti: public Item {
public:
    PapuciSaltareti() : Item() {
        simbol = PAPUCI_SALTARETI;
        tip = ACTIV;
    }
    void Foloseste(Robot *r) {
        r->Misca(r->GetDirectie());
        std::cout<<"\n\n";
        r->Afisare();
        r->SetItem(nullptr);
    }
};

#endif //THEWALK_REFACTOR_ITEM_H
