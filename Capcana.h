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
        if(it) it->Foloseste(r);
    }
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
