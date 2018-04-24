#ifndef THEWALK_REFACTOR_ROBOT_H
#define THEWALK_REFACTOR_ROBOT_H

#include "StructuriHelper.h"
#include "Harta.h"

#include <vector>

class Robot {

protected:
    Punct pozitie;
    Harta harta;
    Item *item;
    RobotSimbol simbol;
    bool in_viata;
    Directie ultima_directie;
    int range_vedere;

public:
    /// Constructori si Destructori
    Robot();

    /// Functii de interactionare cu harta/iteme/capcane
    void Misca(Directie dir);
    void Afisare();
    virtual void Verificare_Pozitie() = 0;

    /// Getters & Setters
    void SetPozitie(int x, int y) {
        pozitie.x = x;
        pozitie.y = y;
    }

    Punct GetPozitie() { return pozitie; }
    void SetHarta(Harta &h) { harta = h; }
    Harta GetHarta() { return harta; }
    bool Mort() { return !in_viata; }
    Item* GetItem() { return item; }
    Item* SetItem(Item *i) { item = i; }
    Directie GetDirectie() { return ultima_directie; }
    void AddRange() { range_vedere++; }
    void SetViata(bool v) { in_viata = v; }

    friend class Capcana;
};

/// Clasele pentru fiecare tip de robot
class Ultra : public Robot {
public:
    Ultra() : Robot() {
        simbol = ULTRA;
    }
    void Verificare_Pozitie();
};

class Mega : public Robot {
public:
    Mega() : Robot() {
        simbol = MEGA;
    }
    void Verificare_Pozitie();
};

class Giga : public Robot {
public:
    Giga() : Robot() {
        simbol = GIGA;
    }
    void Verificare_Pozitie();
};


#endif //THEWALK_REFACTOR_ROBOT_H
