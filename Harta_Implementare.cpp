#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Harta.h"
#include "Capcana.h"
#include "Item.h"

Harta::Harta() {
    /// Setam marimea si alocam dinamic spatiu pentru matrice
    /// Punem itemele si capcanele pe harta
    marime = 15;
    matrice = new char *[marime];
    for (int i = 0; i < marime; i++) {
        matrice[i] = new char[marime];
        for (int j = 0; j < marime; j++) matrice[i][j] = '0';
    }

    /// Setam punctul de sosire random undeva in josul hartii pentru a nu fi prea aproape de player
    srand((unsigned int) time(nullptr));
    sosire.x = rand() % (marime - 1) + 1;
    sosire.y = rand() % (marime - marime / 2) + (marime / 2);
    matrice[sosire.y][sosire.x] = 'F';

    /// Punem itemele pe harta cate 2 fiecare
    int random_x, random_y;
    bool plasat;
    /// Populam lista de iteme de pe harta
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch (i) {
                case 0 :
                    iteme.emplace_back(new PotiuneInvincibilitate());
                    break;
                case 1:
                    iteme.emplace_back(new PotiuneVedere());
                    break;
                case 2:
                    iteme.emplace_back(new PapuciSaltareti());
                    break;
                default:
                    break;
            }
        }
    }
    /// Le plasam pe harta
    for (Item *i : iteme) {
        plasat = false;
        while (!plasat) {
            random_x = rand() % marime;
            random_y = rand() % marime;
            if (matrice[random_y][random_x] == '0') {
                matrice[random_y][random_x] = i->simbol;
                i->pozitie.x = random_x;
                i->pozitie.y = random_y;
                plasat = true;
            } else plasat = false;
        }
    }

    /// Populam lista de capcane
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            switch (i) {
                case 0 :
                    capcane.emplace_back(new Groapa());
                    break;
                case 1:
                    capcane.emplace_back(new IntoarcereInceput());
                    break;
                case 2:
                    capcane.emplace_back(new CapcanaUrs());
                    break;
                default:
                    break;
            }
        }
    }
    /// Le plasam pe harta
    for (Capcana *c : capcane) {
        plasat = false;
        while (!plasat) {
            random_x = rand() % marime;
            random_y = rand() % marime;
            if (matrice[random_y][random_x] == '0') {
                matrice[random_y][random_x] = c->simbol;
                c->pozitie.x = random_x;
                c->pozitie.y = random_y;
                plasat = true;
            } else plasat = false;
        }
    }
}

Harta::Harta(int m) {
    /// Setam marimea si alocam dinamic spatiu pentru matrice
    if (m < 15) marime = 15;
    else marime = m;
    /// Setam marimea si alocam dinamic spatiu pentru matrice
    /// Punem itemele si capcanele pe harta
    matrice = new char *[marime];
    for (int i = 0; i < marime; i++) {
        matrice[i] = new char[marime];
        for (int j = 0; j < marime; j++) matrice[i][j] = '0';
    }

    /// Setam punctul de sosire random undeva in josul hartii pentru a nu fi prea aproape de player
    srand((unsigned int) time(nullptr));
    sosire.x = rand() % (marime - 1) + 1;
    sosire.y = rand() % (marime - marime / 2) + (marime / 2);
    matrice[sosire.y][sosire.x] = 'F';

    /// Punem itemele pe harta cate 2 fiecare
    int random_x, random_y;
    bool plasat;
    /// Populam lista de iteme de pe harta
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch (i) {
                case 0 :
                    iteme.emplace_back(new PotiuneInvincibilitate());
                    break;
                case 1:
                    iteme.emplace_back(new PotiuneVedere());
                    break;
                case 2:
                    iteme.emplace_back(new PapuciSaltareti());
                    break;
                default:
                    break;
            }
        }
    }
    /// Le plasam pe harta
    for (Item *i : iteme) {
        plasat = false;
        while (!plasat) {
            random_x = rand() % marime;
            random_y = rand() % marime;
            if (matrice[random_y][random_x] == '0') {
                matrice[random_y][random_x] = i->simbol;
                i->pozitie.x = random_x;
                i->pozitie.y = random_y;
                plasat = true;
            } else plasat = false;
        }
    }

    /// Populam lista de capcane
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            switch (i) {
                case 0 :
                    capcane.emplace_back(new Groapa());
                    break;
                case 1:
                    capcane.emplace_back(new IntoarcereInceput());
                    break;
                case 2:
                    capcane.emplace_back(new CapcanaUrs());
                    break;
                default:
                    break;
            }
        }
    }
    /// Le plasam pe harta
    for (Capcana *c : capcane) {
        plasat = false;
        while (!plasat) {
            random_x = rand() % marime;
            random_y = rand() % marime;
            if (matrice[random_y][random_x] == '0') {
                matrice[random_y][random_x] = c->simbol;
                c->pozitie.x = random_x;
                c->pozitie.y = random_y;
                plasat = true;
            } else plasat = false;
        }
    }
}

Harta::Harta(const Harta &h) {
    /// Copiem marimea, alocam spatiu pt o noua matrice si copiem
    /// continutul din obiectul de copiat
    marime = h.marime;
    matrice = new char *[marime];
    for (int i = 0; i < marime; i++) {
        matrice[i] = new char[marime]();
    }
    for (int i = 0; i < marime; i++)
        for (int j = 0; j < marime; j++)
            matrice[i][j] = h.matrice[i][j];
    sosire = h.sosire;
    /// Copiem listele de iteme si de capcane
    iteme = h.iteme;
    capcane = h.capcane;
}

Harta::~Harta() {
    /// Dealocam memoria pentru matrice
    for (int i = 0; i < marime; i++)
        delete[] matrice[i];
    delete[] matrice;
    /// Egalam cu 0 toate celelalte variabile
    marime = 0;
    sosire.x = 0;
    sosire.y = 0;
}

char *Harta::operator[](int i) {
    if (i > marime) return nullptr;
    return matrice[i];
}

Harta &Harta::operator=(const Harta &h) {
    /// Procedura din constructorul de copiere
    marime = h.marime;
    matrice = new char *[marime];
    for (int i = 0; i < marime; i++) {
        matrice[i] = new char[marime]();
    }
    for (int i = 0; i < marime; i++)
        for (int j = 0; j < marime; j++)
            matrice[i][j] = h.matrice[i][j];
    sosire = h.sosire;
    /// Copiem listele de iteme si de capcane
    iteme = h.iteme;
    capcane = h.capcane;
    return *this;
}

void Harta::Afisare() {
    for (int i = 0; i < marime; i++) {
        for (int j = 0; j < marime; j++)
            std::cout << matrice[i][j] << ' ';
        std::cout << '\n';
    }
}