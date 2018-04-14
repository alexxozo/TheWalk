#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED

#include "StructuriHelper.h"

class Joc {

protected:
    Harta harta;
    Robot *robo;
    int runda;
    bool joc_terminat;

public:
    /// Constructori si Destructori
    Joc(int marime, Robot &r);

    /// Functii pentru desfasurarea unei runde si a unui joc complet
    void Joaca(Mod mod);
    void JoacaRunda();
    void JoacaRundaSimulare();

};

#endif // JOC_H_INCLUDED
