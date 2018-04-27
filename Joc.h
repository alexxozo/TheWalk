#ifndef THEWALK_REFACTOR_JOC_H
#define THEWALK_REFACTOR_JOC_H

#include "StructuriHelper.h"

class Joc {

protected:
    Harta harta;
    Robot *robo;
    int runda;
    bool joc_terminat;

public:
    /// Constructori si Destructori
    Joc(int marime, Robot *r);

    /// Functii pentru desfasurarea unei runde si a unui joc complet
    void Joaca(Mod mod);
    void JoacaRunda();
    void JoacaRundaSimulare();

};

#endif //THEWALK_REFACTOR_JOC_H
