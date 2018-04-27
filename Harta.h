#ifndef THEWALK_REFACTOR_HARTA_H
#define THEWALK_REFACTOR_HARTA_H

#include "StructuriHelper.h"
#include <vector>

class Item;

class Capcana;

class Harta {

protected:
    char **matrice;
    int marime = 0;
    Punct sosire;
    std::vector<Item *> iteme;
    std::vector<Capcana *> capcane;

public:
    /// Constructori si Destructori
    Harta();
    Harta(int m);
    Harta(const Harta &h);
    ~Harta();

    /// Operatori
    char *operator[](int i);
    Harta &operator=(const Harta &h);

    /// Getters & Setters
    int GetMarime() { return marime; }
    void SetMarime(int m) { marime = m; }
    Punct GetSosire() { return sosire; }
    void SetSosire(Punct s) { sosire = s; }

    /// Afisare folosita pentru debugging
    void Afisare();

    friend class Mega;
    friend class Ultra;
    friend class Giga;
};

#endif //THEWALK_REFACTOR_HARTA_H
