#ifndef THEWALK_REFACTOR_ITEM_H
#define THEWALK_REFACTOR_ITEM_H

#include "StructuriHelper.h"
#include <iostream>

class Item {
protected:
    Punct pozitie;
    ItemSimbol simbol;
public:
    /// Cosntructor
    Item() {
        pozitie.x = 0;
        pozitie.y = 0;
    };

    /// Operatorul egal
    Item &operator=(const Item &i) {
        pozitie = i.pozitie;
        simbol = i.simbol;
    }

    /// Functie de utilizare a itemului specifica pentru fiecare item
    virtual void Foloseste(Robot *r) = 0;

    /// Getters & Setters
    ItemSimbol GetItemSimbol() { return simbol; }

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
    }

    virtual void Foloseste(Robot *r) override {
        if (counter != 0)
            std::cout << "Mai ai " << --counter << " capcane pe care le poti evita!\n";

        if (counter == 0)
            r->SetItem(nullptr);
    }
};

class PotiuneVedere : public Item {
private:
    int counter;
public:
    PotiuneVedere() : Item() {
        simbol = POTIUNE_VEDERE;
        counter = 3;
    }

    virtual void Foloseste(Robot *r) override {
        if (counter != 0) {
            std::cout << "Mai ai " << --counter
                      << " capcane pe care poti pasi fara sa mori si astfel iti vei extinde vederea!\n";
            r->AddRange();
        }

        if (counter == 0)
            r->SetItem(nullptr);
    }
};

class PapuciSaltareti : public Item {
public:
    PapuciSaltareti() : Item() {
        simbol = PAPUCI_SALTARETI;
    }

    virtual void Foloseste(Robot *r) override {
        r->Misca(r->GetDirectie());
        std::cout << "Bravo! Ai sarit peste capcana.\n\n";
        r->Afisare();
        r->SetItem(nullptr);
    }
};

#endif //THEWALK_REFACTOR_ITEM_H
