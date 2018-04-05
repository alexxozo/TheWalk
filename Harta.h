#ifndef HARTA_H_INCLUDED
#define HARTA_H_INCLUDED

#include "Robot.h"
#include <time.h>
#include <stdlib.h>

struct Punct { int x, y; };
enum Item { POTIUNE_VEDERE = 'v', POTIUNE_INVINCIBILITATE = 'i', PAPUCI_SALTARETI = 's' };

class Harta {
    char **matrice;
    int marime;
    Punct sosire;

    public:
        Harta() {
            /// Setam marimea si alocam dinamic spatiu pentru matrice
            /// Punem itemele pe harta random (cate 2 iteme din fiecare)
            marime = 15;
            matrice = new char*[marime];
            for(int i = 0; i < marime; i++) {
                matrice[i] = new char[marime];
                for(int j = 0; j < marime; j++) matrice[i][j] = '0';
            }

            /// Setam punctul de sosire
            sosire.x = marime-1;
            sosire.y = marime-1;
            matrice[sosire.y][sosire.x] = 'F';

            ///Punem itemele pe harta
            srand(time(NULL));
            Item iteme[3] = {POTIUNE_VEDERE, POTIUNE_INVINCIBILITATE, PAPUCI_SALTARETI};
            int random_x, random_y;
            bool item_plasat;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 2; j++) {
                    item_plasat = false;
                    while(!item_plasat) {
                        random_x = rand() % marime;
                        random_y = rand() % marime;
                        if(matrice[random_y][random_x] == '0') {
                            matrice[random_y][random_x] = iteme[i];
                            item_plasat = true;
                        } else item_plasat = false;
                    }
                }
            }

        }

        Harta(int m, Punct s) {
            /// Setam marimea si alocam dinamic spatiu pentru matrice
            if(m < 15) marime = 15;
            else marime = m;
            matrice = new char*[marime];
            for(int i = 0; i < marime; i++) {
                matrice[i] = new char[marime];
                for(int j = 0; j < marime; j++) matrice[i][j] = '0';
            }

            /// Setam punctul de sosire
            sosire = s;
            matrice[sosire.y][sosire.x] = 'F';

            ///Punem itemele pe harta
            srand(time(NULL));
            Item iteme[3] = {POTIUNE_VEDERE, POTIUNE_INVINCIBILITATE, PAPUCI_SALTARETI};
            int random_x, random_y;
            bool item_plasat;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 2; j++) {
                    item_plasat = false;
                    while(!item_plasat) {
                        random_x = rand() % marime;
                        random_y = rand() % marime;
                        if(matrice[random_y][random_x] == '0') {
                            matrice[random_y][random_x] = iteme[i];
                            item_plasat = true;
                        } else item_plasat = false;
                    }
                }
            }
        }

        Harta(const Harta &h) {
            /// Copiem marimea, alocam spatiu pt o noua matrice si copiem
            /// continutul din obiectul de copiat
            marime = h.marime;
            matrice = new char*[marime];
            for(int i = 0; i < marime; i++) {
                matrice[i] = new char[marime]();
            }
            for(int i = 0; i < marime; i++)
                for(int j = 0; j < marime; j++)
                    matrice[i][j] = h.matrice[i][j];
            sosire = h.sosire;
        }

        ~Harta() {
            /// Dealocam memoria pentru matrice
            for(int i = 0; i < marime; i++)
                delete [] matrice[i];
            delete [] matrice;
            /// Egalam cu 0 toate celelalte variabile
            marime = 0;
            sosire.x = 0;
            sosire.y = 0;
        }


        char* operator[](int i) {
            if(i > marime) return NULL;
            return matrice[i];
        }

        Harta& operator=(const Harta& h) {
            /// Procedura din constructorul de copiere
            marime = h.marime;
            matrice = new char*[marime];
            for(int i = 0; i < marime; i++) {
                matrice[i] = new char[marime]();
            }
            for(int i = 0; i < marime; i++)
                for(int j = 0; j < marime; j++)
                    matrice[i][j] = h.matrice[i][j];
            sosire = h.sosire;
            return *this;
        }

        void Afisare() {
            for(int i = 0; i < marime; i++)
            {
                for(int j = 0; j < marime; j++)
                    std::cout<<matrice[i][j]<<' ';
                std::cout<<'\n';
            }
        }

        int GetMarime() { return marime; }
        void SetMarime(int m) { marime = m; }
        Punct GetSosire() { return sosire; }
        void SetSosire(Punct s) { sosire = s; }
};

#endif // HARTA_H_INCLUDED
