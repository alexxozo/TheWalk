#include <iostream>
#include "Robot.h"
#include "Item.h"
#include "Capcana.h"

Robot::Robot() {
    /// Incepem din coltul stanga sus
    pozitie.x = 0;
    pozitie.y = 0;
    item = nullptr;
    in_viata = true;
    ultima_directie = DREAPTA;
    range_vedere = 4;
}

void Robot::Afisare() {
    /// Afisam mapa si pozitia robotului
    std::cout<<'\n';
    int marime_mapa = harta.GetMarime();
    for(int i = 0; i < marime_mapa; i++)
    {
        ///maybe needs refactoring
        for(int j = 0; j < marime_mapa; j++) {
            if(i <= pozitie.y + range_vedere && i >= pozitie.y + 1 && j == pozitie.x)
                std::cout<<harta[i][j]<<' ';
            else if(i >= pozitie.y - range_vedere && i <= pozitie.y - 1 && j == pozitie.x)
                std::cout<<harta[i][j]<<' ';
            else if(j <= pozitie.x + range_vedere && j >= pozitie.x + 1 && i == pozitie.y)
                std::cout<<harta[i][j]<<' ';
            else if(j >= pozitie.x - range_vedere && j <= pozitie.x - 1 && i == pozitie.y)
                std::cout<<harta[i][j]<<' ';
            else if(i == pozitie.y && j == pozitie.x) std::cout<<(char)simbol<<" ";
            else std::cout<<"?"<<' ';
        }
        std::cout<<'\n';
    }
}

void Robot::Misca(Directie dir) {
    /// Citim directia in care dorim deplasarea
    int marime_mapa = harta.GetMarime();
    switch(dir) {
        case STANGA:
            if(pozitie.x == 0) { std::cout<<"Nu se poate!\n"; return ; }
            pozitie.x--;
            ultima_directie = STANGA;
            break;
        case DREAPTA:
            if(pozitie.x == marime_mapa - 1) { std::cout<<"Nu se poate!\n"; return ; }
            pozitie.x++;
            ultima_directie = DREAPTA;
            break;
        case SUS:
            if(pozitie.y == 0) { std::cout<<"Nu se poate!\n"; return ; }
            pozitie.y--;
            ultima_directie = SUS;
            break;
        case JOS:
            if(pozitie.y == marime_mapa - 1) { std::cout<<"Nu se poate!\n"; return ; }
            pozitie.y++;
            ultima_directie = JOS;
            break;
    }
}

void Ultra::Verificare_Pozitie() {
    /// Verificare item pe pozitia robotului
    /// Daca nu are niciun item atunci cauta iteme pe pozitia sa adaugam egalam item cu itemul gasit iar itemul gasit este sters
    /// din vectorul cu iteme al hartii
    if(item == nullptr) {
        std::vector<Item*>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end(); ) {
            PotiuneInvincibilitate *invincibilitate = dynamic_cast<PotiuneInvincibilitate *>(*it);
            if (invincibilitate && pozitie.x == invincibilitate->pozitie.x &&
                pozitie.y == invincibilitate->pozitie.y) {
                item = invincibilitate;
                harta[invincibilitate->pozitie.y][invincibilitate->pozitie.x] = '0';
                delete *it;
                it = harta.iteme.erase(it);
                std::cout<<"Bravo Ultra ai gasit o potiune de invincibilitate! Vei fi invincibil pentru urmatoarele 3 capcane!\n";
                break;
            } else {
                ++it;
            }
        }
    }
    /// Verificare capcana pe pozitia robotului
    for(Capcana *c : harta.capcane) {
        if(pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if(item)
            {
                if(item->GetTip() == ACTIV)
                    c->EfectItem(this);
            } else {
                c->Efect(this);
            }
        }
    }


    if(item && item->GetTip() == PASIV) {
        item->Foloseste(this);
    }
}

void Mega::Verificare_Pozitie() {
    if(item == nullptr) {
        std::vector<Item*>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end(); ) {
            PapuciSaltareti *papuci = dynamic_cast<PapuciSaltareti *>(*it);
            if (papuci && pozitie.x == papuci->pozitie.x &&
                pozitie.y == papuci->pozitie.y) {
                item = (*it);
                harta[(*it)->pozitie.y][(*it)->pozitie.x] = '0';
                delete *it;
                it = harta.iteme.erase(it);
                std::cout<<"Bravo Mega ai gasit papuci saltareti! Vei putea sari peste urmatoarea capcana!\n";
            } else {
                ++it;
            }
        }
    }
    for(Capcana *c : harta.capcane) {
        if(pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if(item)
            {
                if(item->GetTip() == ACTIV)
                    c->EfectItem(this);
            } else {
                    c->Efect(this);
            }
        }
    }

    if(item && item->GetTip() == PASIV) {
        item->Foloseste(this);
    }
}

void Giga::Verificare_Pozitie() {
    if(item == nullptr) {
        std::vector<Item*>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end(); ) {
            PotiuneVedere *vedere = dynamic_cast<PotiuneVedere *>(*it);
            if (vedere && pozitie.x == vedere->pozitie.x &&
                pozitie.y == vedere->pozitie.y) {
                item = (*it);
                harta[(*it)->pozitie.y][(*it)->pozitie.x] = '0';
                delete *it;
                it = harta.iteme.erase(it);
                std::cout<<"Bravo Giga ai gasit potiune de vedere! Vei putea vedea la 8 patratele distanta pentru 8 runde!\n";
            } else {
                ++it;
            }
        }
    }

    for(Capcana *c : harta.capcane) {
        if(pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if(item != nullptr)
            {
                if(item->GetTip() == ACTIV)
                    c->EfectItem(this);
            } else {
                c->Efect(this);
            }
        }
    }
}