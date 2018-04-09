#ifndef THEWALK_STRUCTURIHELPER_H
#define THEWALK_STRUCTURIHELPER_H

/// Coordonate pe harta
struct Punct {
    int x, y;
};

/// Tipurile de item
enum Item {
    FARA_ITEM, POTIUNE_VEDERE = 'v', POTIUNE_INVINCIBILITATE = 'i', PAPUCI_SALTARETI = 's'
};

/// Diferitele capcane
enum Capcana {
    GROAPA = '#', CAPCANA_URS = '!', INTOARCERE_INCEPUT = '~'
};

/// Directiile de deplasare
enum Directie {
    STANGA, SUS, DREAPTA, JOS
};

#endif //THEWALK_STRUCTURIHELPER_H
