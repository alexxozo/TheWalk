#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "StructuriHelper.h"
#include "Harta.h"


class Robot {
protected:
    Punct pozitie;
    Harta mapa;
    Item item;
    char nume;
    bool in_viata;
    int invincibil_counter, vedere_counter;
    bool blocat;
    Directie ultima_directie;
    int range_vedere;

public:
    /// Constructori si Destructori
    Robot();

    /// Functii de interactionare cu harta/iteme/capcane
    void Misca(Directie dir);
    void Afisare();
    void Utilizeaza_Item(Item i);
    void Verifica_Ridicare_Item();
    void Verifica_Capcana();
    void Efect_Capcana(Capcana capcana);
    void Verificare_Locatie();

    /// Getters & Setters
    void SetPozitie(int x, int y) {
        pozitie.x = x;
        pozitie.y = y;
    }
    Punct GetPozitie() { return pozitie; }
    void SetHarta(Harta &h) { mapa = h; }
    Harta GetHarta() { return mapa; }
    bool Mort() { return !in_viata; }
};

/// Clasele pentru fiecare tip de robot
class Ultra : public Robot {
public:
    Ultra() {
        nume = 'U';
    }
};
class Mega : public Robot {
public:
    Mega() {
        nume = 'M';
    }
};
class Giga : public Robot {
public:
    Giga() {
        nume = 'G';
    }
};

#endif // ROBOT_H_INCLUDED
