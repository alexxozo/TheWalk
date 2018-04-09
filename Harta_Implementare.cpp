#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Harta.h"

/**
 * Constructor pentru harta fara parametrii
 * Va crea o harta de 15x15 default si va
 * pozitiona capcane si iteme random.
 */
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
    Item iteme[3] = {POTIUNE_VEDERE, POTIUNE_INVINCIBILITATE, PAPUCI_SALTARETI};
    int random_x, random_y;
    bool plasat;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            plasat = false;
            while (!plasat) {
                random_x = rand() % marime;
                random_y = rand() % marime;
                if (matrice[random_y][random_x] == '0') {
                    matrice[random_y][random_x] = iteme[i];
                    plasat = true;
                } else plasat = false;
            }
        }
    }

    /// Punem capcanele pe harta cate 5 de fiecare
    Capcana capcane[3] = {GROAPA, CAPCANA_URS, INTOARCERE_INCEPUT};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            plasat = false;
            while (!plasat) {
                random_x = rand() % marime;
                random_y = rand() % marime;
                if (matrice[random_y][random_x] == '0') {
                    matrice[random_y][random_x] = capcane[i];
                    plasat = true;
                } else plasat = false;
            }
        }
    }

}

/**
 * Constructor cu parametrii pentru harta
 * Functioneaza la fel ca cel fara parametrii.
 * @param m = marimea dorita pentru harta, daca
 * aceasta este mai mica ca 15 atunci se va seta
 * marimea default 15.
 */
Harta::Harta(int m) {
    /// Setam marimea si alocam dinamic spatiu pentru matrice
    if (m < 15) marime = 15;
    else marime = m;
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
    srand((unsigned int) time(nullptr));
    Item iteme[3] = {POTIUNE_VEDERE, POTIUNE_INVINCIBILITATE, PAPUCI_SALTARETI};
    int random_x, random_y;
    bool plasat;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            plasat = false;
            while (!plasat) {
                random_x = rand() % marime;
                random_y = rand() % marime;
                if (matrice[random_y][random_x] == '0') {
                    matrice[random_y][random_x] = iteme[i];
                    plasat = true;
                } else plasat = false;
            }
        }
    }

    /// Punem capcanele pe harta cate 5 de fiecare
    Capcana capcane[3] = {GROAPA, CAPCANA_URS, INTOARCERE_INCEPUT};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            plasat = false;
            while (!plasat) {
                random_x = rand() % marime;
                random_y = rand() % marime;
                if (matrice[random_y][random_x] == '0') {
                    matrice[random_y][random_x] = capcane[i];
                    plasat = true;
                } else plasat = false;
            }
        }
    }
}

/*
 * Constructorul de copiere
 */
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
}

/**
 * Destructorul
 */
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

/**
 * Operatorul [] pentru a putea folosi harta ca o matrice bidimensionala
 * Exemplu: "harta[i][j]"
 * @param i = indexul liniei
 * @return returneaza linia corespunzatoare
 */
char *Harta::operator[](int i) {
    if (i > marime) return nullptr;
    return matrice[i];
}

/**
 * Operatorul = foloseste o procedura asemantoare cu constructorul de copiere
 * @param h = harta pe care vrem sa o copiem in this
 * @return *this
 */
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
    return *this;
}

/**
 * Functie de afisare a hartii fara player, utilizata in special pentru debugging.
 */
void Harta::Afisare() {
    for (int i = 0; i < marime; i++) {
        for (int j = 0; j < marime; j++)
            std::cout << matrice[i][j] << ' ';
        std::cout << '\n';
    }
}