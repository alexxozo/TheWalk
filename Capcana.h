#ifndef THEWALK_REFACTOR_CAPCANA_H
#define THEWALK_REFACTOR_CAPCANA_H

#include "StructuriHelper.h"
#include "Robot.h"
#include "Item.h"

class Capcana {
protected:
    Punct pozitie;
    CapcanaSimbol simbol;
public:
    Capcana() {
        pozitie.x = 0;
        pozitie.y = 0;
    }
    void EfectItem(Robot *r) {
        Item *it = r->GetItem();
        PotiuneInvincibilitate *invincibilitate = new PotiuneInvincibilitate;
        invincibilitate = dynamic_cast<PotiuneInvincibilitate *>(it);
        PotiuneVedere *vedere  = new PotiuneVedere;
        vedere = dynamic_cast<PotiuneVedere *>(it);
        PapuciSaltareti *papuci =  new PapuciSaltareti;
        papuci = dynamic_cast<PapuciSaltareti *>(it);
        if(invincibilitate != NULL) {
            invincibilitate->Foloseste(r);
         if (vedere != NULL) {
            vedere->Foloseste(r);
        } if(papuci != NULL) {
            papuci->Foloseste(r);
        }
    };
    virtual void Efect(Robot *r) = 0;
    friend class Harta;
    friend class Giga;
    friend class Ultra;
    friend class Mega;
};

class Groapa : public Capcana{
public:
    Groapa() : Capcana() {
        simbol = GROAPA;
    }

    void Efect(Robot *r) {
        r->SetViata(false);
    }

};

class CapcanaUrs : public Capcana {
public:
    CapcanaUrs() : Capcana() {
        simbol = CAPCANA_URS;
    }

    void Efect(Robot *r) {
        r->SetViata(false);
    }

};

class IntoarcereInceput : public Capcana{
public:
    IntoarcereInceput() : Capcana() {
        simbol = INTOARCERE_INCEPUT;
    }

    void Efect(Robot *r) {
        r->SetPozitie(0,0);
        r->Afisare();
    }

};

#endif //THEWALK_REFACTOR_CAPCANA_H
