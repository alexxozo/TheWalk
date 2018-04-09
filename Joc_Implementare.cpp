#include <iostream>
#include "Harta.h"
#include "Robot.h"
#include "Joc.h"

/**
 * Constructorul pentru joc
 * @param marime = marimea hartii
 * @param r = tipul de robot
 */
Joc::Joc(int marime, Robot &r) : harta(marime) {
    robo = &r;
    robo->SetHarta(harta);
    runda = 0;
    joc_terminat = false;
};

/**
 * Functie pentru desfasurarea unui joc
 */
void Joc::Joaca() {
    while (!joc_terminat) {
        /// Numaram rundele
        runda++;
        if (runda == 1) robo->Afisare();
        std::cout << "Runda: " << runda << '\n';

        /// Jucam runda
        JoacaRunda();
    }

    if (!robo->Mort())
        std::cout << "Ai terminat jocul in " << runda << " de runde";
    else std::cout << "Ai murit :( in runda " << runda << " ...";
}

/**
 * Functie pentru desfasurarea unei runde
 */
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

    /// Afisam harta impreuna cu playerul
    robo->Afisare();
    robo->Verificare_Locatie();
    pozitie_curenta = robo->GetPozitie();
    if ((pozitie_curenta.x == sosire.x && pozitie_curenta.y == sosire.y) || robo->Mort()) {
        joc_terminat = true;
    }
}

