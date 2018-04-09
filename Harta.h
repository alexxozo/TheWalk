#ifndef HARTA_H_INCLUDED
#define HARTA_H_INCLUDED

#include "StructuriHelper.h"

class Harta {

protected:
    char **matrice;
    int marime = 0;
    Punct sosire;

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
};

#endif // HARTA_H_INCLUDED
