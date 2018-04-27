#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#include "Robot.h"
#include "Item.h"
#include "Capcana.h"

/*
 * Functie folosita pentru sortare
 */
bool sortbysec(const std::pair<int, int> &a,
               const std::pair<int, int> &b) {
    return (a.second > b.second);
}

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
    std::cout << '\n';
    int marime_mapa = harta.GetMarime();
    for (int i = 0; i < marime_mapa; i++) {
        ///maybe needs refactoring
        for (int j = 0; j < marime_mapa; j++) {
            if (i <= pozitie.y + range_vedere && i >= pozitie.y + 1 && j == pozitie.x)
                std::cout << harta[i][j] << ' ';
            else if (i >= pozitie.y - range_vedere && i <= pozitie.y - 1 && j == pozitie.x)
                std::cout << harta[i][j] << ' ';
            else if (j <= pozitie.x + range_vedere && j >= pozitie.x + 1 && i == pozitie.y)
                std::cout << harta[i][j] << ' ';
            else if (j >= pozitie.x - range_vedere && j <= pozitie.x - 1 && i == pozitie.y)
                std::cout << harta[i][j] << ' ';
            else if (i == pozitie.y && j == pozitie.x) std::cout << (char) simbol << " ";
            else std::cout << "?" << ' ';
        }
        std::cout << '\n';
    }
}

void Robot::Misca(Directie dir) {
    /// Citim directia in care dorim deplasarea
    int marime_mapa = harta.GetMarime();
    switch (dir) {
        case STANGA:
            if (pozitie.x == 0) {
                std::cout << "Nu se poate!\n";
                return;
            }
            pozitie.x--;
            ultima_directie = STANGA;
            break;
        case DREAPTA:
            if (pozitie.x == marime_mapa - 1) {
                std::cout << "Nu se poate!\n";
                return;
            }
            pozitie.x++;
            ultima_directie = DREAPTA;
            break;
        case SUS:
            if (pozitie.y == 0) {
                std::cout << "Nu se poate!\n";
                return;
            }
            pozitie.y--;
            ultima_directie = SUS;
            break;
        case JOS:
            if (pozitie.y == marime_mapa - 1) {
                std::cout << "Nu se poate!\n";
                return;
            }
            pozitie.y++;
            ultima_directie = JOS;
            break;
    }
}

void Robot::InitLocuriVizitate(int marime) {
    locuriVizitate = new int *[marime];
    for (int i = 0; i < marime; i++) {
        locuriVizitate[i] = new int[marime];
        for (int j = 0; j < marime; j++) locuriVizitate[i][j] = 0;
    }
}

void Ultra::Verificare_Pozitie() {
    /// Verificare item pe pozitia robotului
    /// Daca nu are niciun item atunci cauta iteme pe pozitia sa adaugam egalam item cu itemul gasit iar itemul gasit este sters
    /// din vectorul cu iteme al hartii
    if (item == nullptr) {
        std::vector<Item *>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end();) {
            PotiuneInvincibilitate *invincibilitate = dynamic_cast<PotiuneInvincibilitate *>(*it);
            if (invincibilitate && pozitie.x == invincibilitate->pozitie.x &&
                pozitie.y == invincibilitate->pozitie.y) {
                item = invincibilitate;
                harta[invincibilitate->pozitie.y][invincibilitate->pozitie.x] = '0';
                it = harta.iteme.erase(it);
                std::cout
                        << "Bravo Ultra ai gasit o potiune de invincibilitate! Vei fi invincibil pentru urmatoarele 5 capcane!\n";
                break;
            } else {
                ++it;
            }
        }
    }
    /// Verificare capcana pe pozitia robotului
    for (Capcana *c : harta.capcane) {
        if (pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if (item) {
                c->EfectItem(this);
            } else {
                c->Efect(this);
            }
        }
    }
}

void Mega::Verificare_Pozitie() {
    if (item == nullptr) {
        std::vector<Item *>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end();) {
            PapuciSaltareti *papuci = dynamic_cast<PapuciSaltareti *>(*it);
            if (papuci && pozitie.x == papuci->pozitie.x &&
                pozitie.y == papuci->pozitie.y) {
                item = (*it);
                harta[(*it)->pozitie.y][(*it)->pozitie.x] = '0';
                it = harta.iteme.erase(it);
                std::cout << "Bravo Mega ai gasit papuci saltareti! Vei putea sari peste urmatoarea capcana!\n";
            } else {
                ++it;
            }
        }
    }
    for (Capcana *c : harta.capcane) {
        if (pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if (item) {
                c->EfectItem(this);
            } else {
                c->Efect(this);
            }
        }
    }
}

void Giga::Verificare_Pozitie() {
    if (item == nullptr) {
        std::vector<Item *>::iterator it;
        for (it = harta.iteme.begin(); it != harta.iteme.end();) {
            PotiuneVedere *vedere = dynamic_cast<PotiuneVedere *>(*it);
            if (vedere && pozitie.x == vedere->pozitie.x &&
                pozitie.y == vedere->pozitie.y) {
                item = (*it);
                harta[(*it)->pozitie.y][(*it)->pozitie.x] = '0';
                it = harta.iteme.erase(it);
                std::cout
                        << "Bravo Giga ai gasit potiune de vedere! Distanta la care vei va creste cu fiecare capcana pe care calci!\n";
            } else {
                ++it;
            }
        }
    }

    for (Capcana *c : harta.capcane) {
        if (pozitie.x == c->pozitie.x && pozitie.y == c->pozitie.y) {
            if (item) {
                c->EfectItem(this);
            } else {
                c->Efect(this);
            }
        }
    }
}

Directie Ultra::UtilizeazaStrategie() {
    /// Strategiile vor functiona astfel:
    /// Cream un vector care va lucra ca o coada de prioritati
    /// Punem in el elemente de tipul pair<Directie, int>
    /// Acestea reprezinta directia si ponderea pentru directia respectiva in functie de fiecare robot
    /// Iar la final vom extrage directia cu cea mai mare pondere

    Punct pozitie_curenta = GetPozitie();
    std::vector<std::pair<Directie, int>> coadaPrioritati;
    locuriVizitate[pozitie_curenta.y][pozitie_curenta.x]++;

    /// Scanam cele 4 directii si adaugam la coadaPrioritati
    /// Daca gasim finalul pe harta atunci setam prioritatea spre directia aceea cu 10 (deci va fi prima din coada)
    /// Daca nu gasim finalul setam ponderile pentru directii in functie de cate locuri libere exista in fiecare directie
    /// Strategia lui Ultra = cauta sa colecteze iteme si daca are item trece NUMAI daca este nevoie prin capcane (daca in acea directie se afla finalul)

    /// Verificare SUS
    int locuriLibere = 0;
    bool directieFinal = false;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y - i < 0) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y - i][pozitie_curenta.x] == 'F') {
            directieFinal = true;
            coadaPrioritati.push_back(std::make_pair(SUS, 10));
        }
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y - 1][pozitie_curenta.x]))
            if (item != nullptr && directieFinal) {
                coadaPrioritati.push_back(std::make_pair(SUS, 20));
            } else break;
        /// Daca gasim un item
        if (harta[pozitie_curenta.y - i][pozitie_curenta.x] == 'i') {
            coadaPrioritati.push_back(std::make_pair(SUS, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y - i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(SUS, locuriLibere));

    /// Verificare DREAPTA
    locuriLibere = 0;
    directieFinal = false;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x + i >= harta.GetMarime()) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x + i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(DREAPTA, 10));
        }
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + 1]))
            if (item != nullptr && directieFinal) {
                coadaPrioritati.push_back(std::make_pair(DREAPTA, 11));
            } else break;
        /// Daca gasim un item
        if (harta[pozitie_curenta.y][pozitie_curenta.x + 1] == 'i') {
            coadaPrioritati.push_back(std::make_pair(DREAPTA, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1];
    }
    coadaPrioritati.push_back(std::make_pair(DREAPTA, locuriLibere));

    /// Verificare JOS
    locuriLibere = 0;
    directieFinal = false;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y + i >= harta.GetMarime()) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y + i][pozitie_curenta.x] == 'F') {
            coadaPrioritati.push_back(std::make_pair(JOS, 10));
        }
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y + 1][pozitie_curenta.x]))
            if (item != nullptr && directieFinal) {
                coadaPrioritati.push_back(std::make_pair(JOS, 11));
            } else break;
        /// Daca gasim un item
        if (harta[pozitie_curenta.y + i][pozitie_curenta.x] == 'i') {
            coadaPrioritati.push_back(std::make_pair(JOS, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y + i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(JOS, locuriLibere));

    /// Verificare STANGA
    locuriLibere = 0;
    directieFinal = false;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x - i < 0) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x - i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(STANGA, 10));
        }
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - 1]))
            if (item != nullptr && directieFinal) {
                coadaPrioritati.push_back(std::make_pair(STANGA, 11));
            } else break;
        /// Daca gasim un item
        if (harta[pozitie_curenta.y][pozitie_curenta.x - i] == 'i') {
            coadaPrioritati.push_back(std::make_pair(STANGA, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1];
    }
    coadaPrioritati.push_back(std::make_pair(STANGA, locuriLibere));

    /// Sortam vectorul pentru a extrage cea mai mare pondere
    std::sort(coadaPrioritati.begin(), coadaPrioritati.end(), sortbysec);

    ///Debugging

    /*for(std::pair<Directie, int> x : coadaPrioritati) {
        std::cout<<x.first<<'/'<<x.second<<' ';
    }
    std::cout<<'\n';*/


    return coadaPrioritati.front().first;
}

Directie Mega::UtilizeazaStrategie() {

    /// Strategiile vor functiona astfel:
    /// Cream un vector care va lucra ca o coada de prioritati
    /// Punem in el elemente de tipul pair<Directie, int>
    /// Acestea reprezinta directia si ponderea pentru directia respectiva in functie de fiecare robot
    /// Iar la final vom extrage directia cu cea mai mare pondere

    Punct pozitie_curenta = GetPozitie();
    std::vector<std::pair<Directie, int>> coadaPrioritati;
    locuriVizitate[pozitie_curenta.y][pozitie_curenta.x]++;

    /// Scanam cele 4 directii si adaugam la coadaPrioritati
    /// Daca gasim finalul pe harta atunci setam prioritatea spre directia aceea cu 10 (deci va fi prima din coada)
    /// Daca nu gasim finalul setam ponderile pentru directii in functie de cate locuri libere exista in fiecare directie
    /// Strategia lui Mega este una pasiva = evita capcanele si cauta sa mearga pe unde este cel mai liber

    /// Verificare SUS
    int locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y - i < 0) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y - 1][pozitie_curenta.x])) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y - i][pozitie_curenta.x] == 'F') {
            coadaPrioritati.push_back(std::make_pair(SUS, 10));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y - i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(SUS, locuriLibere));

    /// Verificare DREAPTA
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x + i >= harta.GetMarime()) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + 1])) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x + i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(DREAPTA, 10));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1];
    }
    coadaPrioritati.push_back(std::make_pair(DREAPTA, locuriLibere));

    /// Verificare JOS
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y + i >= harta.GetMarime()) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y + 1][pozitie_curenta.x])) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y + i][pozitie_curenta.x] == 'F') {
            coadaPrioritati.push_back(std::make_pair(JOS, 10));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y + i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(JOS, locuriLibere));

    /// Verificare STANGA
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x - i < 0) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - 1])) break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x - i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(STANGA, 10));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1];
    }
    coadaPrioritati.push_back(std::make_pair(STANGA, locuriLibere));

    /// Sortam vectorul pentru a extrage cea mai mare pondere
    std::sort(coadaPrioritati.begin(), coadaPrioritati.end(), sortbysec);

    ///Debugging
    /*
    for(std::pair<Directie, int> x : coadaPrioritati) {
        std::cout<<x.first<<'/'<<x.second<<' ';
    }
    std::cout<<'\n';
     */

    return coadaPrioritati.front().first;
}

Directie Giga::UtilizeazaStrategie() {

    /// Strategiile vor functiona astfel:
    /// Cream un vector care va lucra ca o coada de prioritati
    /// Punem in el elemente de tipul pair<Directie, int>
    /// Acestea reprezinta directia si ponderea pentru directia respectiva in functie de fiecare robot
    /// Iar la final vom extrage directia cu cea mai mare pondere

    Punct pozitie_curenta = GetPozitie();
    std::vector<std::pair<Directie, int>> coadaPrioritati;
    locuriVizitate[pozitie_curenta.y][pozitie_curenta.x]++;

    /// Scanam cele 4 directii si adaugam la coadaPrioritati
    /// Daca gasim finalul pe harta atunci setam prioritatea spre directia aceea cu 10 (deci va fi prima din coada)
    /// Daca nu gasim finalul setam ponderile pentru directii in functie de cate locuri libere exista in fiecare directie
    /// Strategia lui Giga = cauta sa colecteze iteme si daca are iteme trece prin capcane

    /// Verificare SUS
    int locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y - i < 0) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y - 1][pozitie_curenta.x]))
            if (item != nullptr) {
                coadaPrioritati.push_back(std::make_pair(SUS, 11));
            } else break;

        /// Daca gasim finalul
        if (harta[pozitie_curenta.y - i][pozitie_curenta.x] == 'F') {
            coadaPrioritati.push_back(std::make_pair(SUS, 10));
        }
        /// Daca gasim un item
        if (harta[pozitie_curenta.y - i][pozitie_curenta.x] == 'v') {
            coadaPrioritati.push_back(std::make_pair(SUS, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y - i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y - 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(SUS, locuriLibere));

    /// Verificare DREAPTA
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x + i >= harta.GetMarime()) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + 1]))
            if (item != nullptr) {
                coadaPrioritati.push_back(std::make_pair(DREAPTA, 11));
            } else break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x + i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(DREAPTA, 10));
        }
        /// Daca gasim un item
        if (harta[pozitie_curenta.y][pozitie_curenta.x + 1] == 'v') {
            coadaPrioritati.push_back(std::make_pair(DREAPTA, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x + i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x + 1];
    }
    coadaPrioritati.push_back(std::make_pair(DREAPTA, locuriLibere));

    /// Verificare JOS
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.y + i >= harta.GetMarime()) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y + 1][pozitie_curenta.x]))
            if (item != nullptr) {
                coadaPrioritati.push_back(std::make_pair(JOS, 11));
            } else break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y + i][pozitie_curenta.x] == 'F') {
            coadaPrioritati.push_back(std::make_pair(JOS, 10));
        }
        /// Daca gasim un item
        if (harta[pozitie_curenta.y + i][pozitie_curenta.x] == 'v') {
            coadaPrioritati.push_back(std::make_pair(JOS, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y + i][pozitie_curenta.x]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y + 1][pozitie_curenta.x];
    }
    coadaPrioritati.push_back(std::make_pair(JOS, locuriLibere));

    /// Verificare STANGA
    locuriLibere = 0;
    for (int i = 1; i <= range_vedere; i++) {
        /// Daca iesim de pe harta
        if (pozitie_curenta.x - i < 0) break;
        /// Daca gasim o capcana fix langa
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - 1]))
            if (item != nullptr) {
                coadaPrioritati.push_back(std::make_pair(STANGA, 11));
            } else break;
        /// Daca gasim finalul
        if (harta[pozitie_curenta.y][pozitie_curenta.x - i] == 'F') {
            coadaPrioritati.push_back(std::make_pair(STANGA, 10));
        }
        /// Daca gasim un item
        if (harta[pozitie_curenta.y][pozitie_curenta.x - i] == 'v') {
            coadaPrioritati.push_back(std::make_pair(STANGA, 11));
        }
        /// Daca pozitia este libera incrementam ponderea pt directia aceasta
        if (strchr("#!~", harta[pozitie_curenta.y][pozitie_curenta.x - i]) == nullptr) {
            locuriLibere++;
        }
        /// Daca am vizitat deja pozitia de langa noi atunci scadem din ponderea pentru directie
        if (i == 1 && locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1] > 0)
            locuriLibere -= locuriVizitate[pozitie_curenta.y][pozitie_curenta.x - 1];
    }
    coadaPrioritati.push_back(std::make_pair(STANGA, locuriLibere));

    /// Sortam vectorul pentru a extrage cea mai mare pondere
    std::sort(coadaPrioritati.begin(), coadaPrioritati.end(), sortbysec);

    ///Debugging

    /*for(std::pair<Directie, int> x : coadaPrioritati) {
        std::cout<<x.first<<'/'<<x.second<<' ';
    }
    std::cout<<'\n';
    */

    return coadaPrioritati.front().first;
}

void Ultra::PrezentareStrategie() {
    std::cout<<"Strategia lui Ultra = cauta sa colecteze iteme si daca are item trece NUMAI daca este nevoie prin capcane (daca in acea directie se afla finalul)\n";
}

void Mega::PrezentareStrategie() {
    std::cout<<"Strategia lui Mega este una pasiva = evita capcanele si cauta sa mearga pe unde este cel mai liber\n";
}

void Giga::PrezentareStrategie() {
    std::cout<<"Strategia lui Giga = cauta sa colecteze iteme si daca are iteme trece prin capcane\n";
}