#include <iostream>
#include "Robot.h"

/**
 * Contructorul pentru robot
 */
Robot::Robot() {
    /// Incepem din coltul stanga sus
    pozitie.x = 0;
    pozitie.y = 0;
    nume = 'X';
    item = FARA_ITEM;
    in_viata = true;
    blocat = false;
    invincibil_counter = 0;
    vedere_counter = 0;
    ultima_directie = DREAPTA;
    range_vedere = 4;
}

/**
 * Functie ce schimba pozitia robotului in functie de locul lui
 * pe harta.
 * @param dir = directia de deplasare
 */
void Robot::Misca(Directie dir) {
    /// Citim directia in care dorim deplasarea
    int marime_mapa = mapa.GetMarime();
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

/**
 * Afisarea robotului pe harta
 */
void Robot::Afisare() {
    /// Afisam mapa si pozitia robotului
    int marime_mapa = mapa.GetMarime();
    for(int i = 0; i < marime_mapa; i++)
    {
        ///maybe needs refactoring
        for(int j = 0; j < marime_mapa; j++) {
            if(i <= pozitie.y + range_vedere && i >= pozitie.y + 1 && j == pozitie.x)
                std::cout<<mapa[i][j]<<' ';
            else if(i >= pozitie.y - range_vedere && i <= pozitie.y - 1 && j == pozitie.x)
                std::cout<<mapa[i][j]<<' ';
            else if(j <= pozitie.x + range_vedere && j >= pozitie.x + 1 && i == pozitie.y)
                std::cout<<mapa[i][j]<<' ';
            else if(j >= pozitie.x - range_vedere && j <= pozitie.x - 1 && i == pozitie.y)
                std::cout<<mapa[i][j]<<' ';
            else if(i == pozitie.y && j == pozitie.x) std::cout<<nume<<" ";
            else std::cout<<"?"<<' ';
        }
        std::cout<<'\n';
    }
}

/**
 * Modul in care robotul poate utiliza itemul
 * in functie de tipul sau.
 * @param i = item gasit
 */
void Robot::Utilizeaza_Item(Item i) {
    if(nume == 'U' && i == POTIUNE_INVINCIBILITATE) {
        std::cout<<"Felicitari Ultra! Ai gasit o potiune de invincibilitate! (Esti invincibil pentru urmatoarele 8 runde)\n";
        mapa[pozitie.y][pozitie.x] = '0';
        invincibil_counter += 8;
        item = POTIUNE_INVINCIBILITATE;
    } else if (nume == 'M' && i == PAPUCI_SALTARETI) {
        std::cout<<"Felicitari Mega! Ai gasit o pereche de papuci saltareti! (Poti sari peste urmatorul obstacol ce iti apare in cale)\n";
        mapa[pozitie.y][pozitie.x] = '0';
        item = PAPUCI_SALTARETI;
    } else if(nume == 'G' && i == POTIUNE_VEDERE) {
        std::cout<<"Felicitari Giga! Ai gasit o potiune pentru vedere! (Poti vedea acum la 8 casute departare pentru 8 runde)\n";
        mapa[pozitie.y][pozitie.x] = '0';
        vedere_counter += 8;
        item = POTIUNE_VEDERE;
    }
}

/**
 * Verificare item gasit
 */
void Robot::Verifica_Ridicare_Item() {
    Item item_curent = (Item)mapa[pozitie.y][pozitie.x];
    if(item_curent == POTIUNE_INVINCIBILITATE || item_curent == POTIUNE_VEDERE || item_curent == PAPUCI_SALTARETI) {
        Utilizeaza_Item(item_curent);
    }
}

/**
 * Verificare capcana gasita
 */
void Robot::Verifica_Capcana() {
    Capcana  capcana_curenta = (Capcana)mapa[pozitie.y][pozitie.x];
    if(capcana_curenta == GROAPA || capcana_curenta == INTOARCERE_INCEPUT || capcana_curenta == CAPCANA_URS) {
        Efect_Capcana(capcana_curenta);
    }
}

/**
 * Efectul unei capcane in functie de itemul pe care
 * il are robotul.
 * @param capcana = capcana pe care a ajuns robotul
 */
void Robot::Efect_Capcana(Capcana capcana) {
    if(capcana == GROAPA) {
        std::cout<<"Groapa\n";
        if(item == PAPUCI_SALTARETI) {
            Misca(ultima_directie);
            Afisare();
            item = FARA_ITEM;
            std::cout<<"Ai sarit peste groapa!\n";
        } else if(item == FARA_ITEM) {
            in_viata = false;
        }
    } else if(capcana == INTOARCERE_INCEPUT) {
        std::cout<<"Intoarcere inceput!\n";
        if (item == PAPUCI_SALTARETI){
            Misca(ultima_directie);
            Afisare();
            item = FARA_ITEM;
            std::cout<<"Ai sarit peste capcana!\n";
        } else if(item == FARA_ITEM){
            pozitie.x = 0;
            pozitie.y = 0;
            Afisare();
        }
    } else if(capcana == CAPCANA_URS) {
        std::cout<<"Capcana urs!\n";
        if(item == PAPUCI_SALTARETI) {
            Misca(ultima_directie);
            Afisare();
            item = FARA_ITEM;
            std::cout<<"Ai sarit peste capcana!\n";
        } else if(item == FARA_ITEM){
            in_viata = false;
        }
    }
}

/**
 * Functia utilizeaza Verificare_Capcana si Verificare_Item pentru a
 * afla daca pe pozitia robotului se afla o capcana sau un item.
 */
void Robot::Verificare_Locatie() {
    Verifica_Ridicare_Item();
    Verifica_Capcana();

    if(invincibil_counter != 0) {
        std::cout << "Mai ai " << invincibil_counter-- << " runde de invincibilitate!\n";
    } else if(invincibil_counter == 0 && item == POTIUNE_INVINCIBILITATE){
        item = FARA_ITEM;
    }
    if(vedere_counter != 0) {
        std::cout << "Mai ai " << vedere_counter-- << " runde de vedere extinsa!\n";
        range_vedere = 8;
    } else if(vedere_counter == 0 && item == POTIUNE_VEDERE){
        range_vedere = 4;
        item = FARA_ITEM;
    }
}



