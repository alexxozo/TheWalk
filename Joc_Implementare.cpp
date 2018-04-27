#include <iostream>
#include <cstring>
#include "Harta.h"
#include "Robot.h"
#include "Item.h"
#include "Joc.h"

Joc::Joc(int marime, Robot *r) : harta(marime) {
    robo = r;
    robo->SetHarta(harta);
    robo->InitLocuriVizitate(marime);
    runda = 0;
    joc_terminat = false;
};

void Joc::Joaca(Mod mod) {
    while (!joc_terminat) {
        /// Numaram rundele
        runda++;
        if (runda == 1) robo->Afisare();
        std::cout << "Runda: " << runda << '\n';

        /// Jucam runda
        if (mod == NORMAL)
            JoacaRunda();
        else if (mod == SIMULARE)
            JoacaRundaSimulare();
    }

    if (!robo->Mort())
        std::cout << "Ai terminat jocul in " << runda << " de runde";
    else std::cout << "Ai murit :( in runda " << runda << " ...";
}

void Joc::JoacaRunda() {
    char dir;
    bool miscare_inregistrata = false;
    Punct pozitie_curenta;
    Punct sosire = harta.GetSosire();

    /// Inregistram miscarea playerului
    while (!miscare_inregistrata) {
        std::cin >> dir;
        switch (dir) {
            case 'a':
                robo->Misca(STANGA);
                miscare_inregistrata = true;
                break;
            case 'd' :
                robo->Misca(DREAPTA);
                miscare_inregistrata = true;
                break;
            case 'w' :
                robo->Misca(SUS);
                miscare_inregistrata = true;
                break;
            case 's' :
                robo->Misca(JOS);
                miscare_inregistrata = true;
                break;
            default :
                miscare_inregistrata = false;
                std::cout << "Va rugam sa introduceti una dintre literele w a s d\n";
                break;
        }
    }

    /// Afisam harta impreuna cu playerul si item curent
    robo->Afisare();
    robo->Verificare_Pozitie();
    Item *it = robo->GetItem();
    std::cout << "ITEM: ";
    if (it != nullptr) {
        ItemSimbol simbol = it->GetItemSimbol();
        switch (simbol) {
            case POTIUNE_INVINCIBILITATE:
                std::cout << "Potiune Invincibilitate\n";
                break;
            case POTIUNE_VEDERE:
                std::cout << "Potiune Vedere\n";
                break;
            case PAPUCI_SALTARETI:
                std::cout << "Papuci Saltareti\n";
                break;
        }
    } else std::cout << "NIMIC\n";
    pozitie_curenta = robo->GetPozitie();
    if ((pozitie_curenta.x == sosire.x && pozitie_curenta.y == sosire.y) || robo->Mort()) {
        joc_terminat = true;
    }
}

void Joc::JoacaRundaSimulare() {
    char dir;
    bool gasit_directie = false;
    Punct pozitie_curenta = robo->GetPozitie();
    Punct sosire = harta.GetSosire();


    std::cout << "Va rugam sa apasati enter pentru continuarea simularii\n";
    std::cin.get();

    /// Aplicam pentru fiecare robot o strategie corespunzatoare
    robo->Misca(robo->UtilizeazaStrategie());

    /// Afisam harta impreuna cu playerul
    robo->Afisare();
    robo->Verificare_Pozitie();
    Item *it = robo->GetItem();
    std::cout << "ITEM: ";
    if (it != nullptr) {
        ItemSimbol simbol = it->GetItemSimbol();
        switch (simbol) {
            case POTIUNE_INVINCIBILITATE:
                std::cout << "Potiune Invincibilitate\n";
                break;
            case POTIUNE_VEDERE:
                std::cout << "Potiune Vedere\n";
                break;
            case PAPUCI_SALTARETI:
                std::cout << "Papuci Saltareti\n";
                break;
        }
    } else std::cout << "NIMIC\n";
    pozitie_curenta = robo->GetPozitie();
    if ((pozitie_curenta.x == sosire.x && pozitie_curenta.y == sosire.y) || robo->Mort()) {
        joc_terminat = true;
    }
}
