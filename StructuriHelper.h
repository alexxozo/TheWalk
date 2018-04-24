#ifndef THEWALK_REFACTOR_STRUCTURIHELPER_H
#define THEWALK_REFACTOR_STRUCTURIHELPER_H

/// Coordonate pe harta
struct Punct {
    int x, y;
};

/// Tipurile de item pe harta
enum ItemSimbol {
    FARA_ITEM, POTIUNE_VEDERE = 'v', POTIUNE_INVINCIBILITATE = 'i', PAPUCI_SALTARETI = 's'
};

/// Diferitele capcane pe harta
enum CapcanaSimbol {
    GROAPA = '#', CAPCANA_URS = '!', INTOARCERE_INCEPUT = '~'
};

/// Diferitele tipuri de roboti pe harta
enum RobotSimbol {
    MEGA = 'M', GIGA = 'G', ULTRA = 'U'
};

/// Directiile de deplasare
enum Directie {
    STANGA, SUS, DREAPTA, JOS
};

enum Mod {
    NORMAL, SIMULARE
};

enum TipItem {
    PASIV, ACTIV
};

#endif //THEWALK_REFACTOR_STRUCTURIHELPER_H
