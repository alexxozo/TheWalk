#include <iostream>
#include <cstring>
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
void Joc::Joaca(Mod mod) {
    while (!joc_terminat) {
        /// Numaram rundele
        runda++;
        if (runda == 1) robo->Afisare();
        std::cout << "Runda: " << runda << '\n';

        /// Jucam runda
        if(mod == NORMAL)
            JoacaRunda();
        else if(mod == SIMULARE)
            JoacaRundaSimulare();
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

void Joc::JoacaRundaSimulare(){
    char dir;
    bool gasit_directie = false;
    Punct pozitie_curenta = robo->GetPozitie();
    Punct sosire = harta.GetSosire();

    /// seed random
    srand((unsigned int) time(nullptr));

    std::cout << "Va rugam sa apasati enter pentru continuarea simularii\n";
    std::cin.get();


    int random_miscare = rand() % 4;

    /// Pentru terminarea jocului
    if(pozitie_curenta.y - 1 > 0 && harta[pozitie_curenta.y - 1][pozitie_curenta.x] == 'F')
        goto SUS;
    else if(pozitie_curenta.x + 1 < harta.GetMarime() - 1 && harta[pozitie_curenta.y][pozitie_curenta.x + 1] == 'F')
        goto DREAPTA;
    else if(pozitie_curenta.y + 1 < harta.GetMarime() - 1 && harta[pozitie_curenta.y + 1][pozitie_curenta.x] == 'F')
        goto JOS;
    else if(pozitie_curenta.x - 1 > 0 && harta[pozitie_curenta.y ][pozitie_curenta.x - 1] == 'F')
        goto STANGA;

    switch(random_miscare) {
        case 0:
            goto SUS;
        case 1:
            goto DREAPTA;
        case 2:
            goto STANGA;
        case 3:
            goto JOS;
    }

    /// Inregistram miscarea playerului
    while(true) {
        SUS:
        if(pozitie_curenta.y - 1 > 0 && strchr("#!~", harta[pozitie_curenta.y - 1][pozitie_curenta.x]) == nullptr) {
            robo->Misca(SUS);
            break;
        }
        DREAPTA:
        if(pozitie_curenta.x + 1 < harta.GetMarime() - 1 && strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + 1]) == nullptr) {
            robo->Misca(DREAPTA);
            break;
        }
        JOS:
        if(pozitie_curenta.y + 1 < harta.GetMarime() - 1 && strchr("#!~", harta[pozitie_curenta.y + 1][pozitie_curenta.x]) == nullptr) {
            robo->Misca(JOS);
            break;
        }
        STANGA:
        if(pozitie_curenta.x - 1 > 0 && strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - 1]) == nullptr) {
            robo->Misca(STANGA);
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

