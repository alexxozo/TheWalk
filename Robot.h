#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "Harta.h"
enum Directie { Stanga, Sus, Dreapta, Jos };

class Robot {
    protected:
    Punct pozitie;
    Harta mapa;

    public:
        Robot(Harta m): mapa(m) {
            /// Incepem din coltul stanga sus
            pozitie.x = 0;
            pozitie.y = 0;
        }

        void Misca(Directie dir) {
            /// Citim directia in care dorim deplasarea
            int marime_mapa = mapa.GetMarime();
            switch(dir) {
                case Stanga:
                    if(pozitie.x == 0) { std::cout<<"Nu se poate!\n"; return ; }
                    pozitie.x--;
                    break;
                case Dreapta:
                    if(pozitie.x == marime_mapa - 1) { std::cout<<"Nu se poate!\n"; return ; }
                    pozitie.x++;
                    break;
                case Sus:
                    if(pozitie.y == 0) { std::cout<<"Nu se poate!\n"; return ; }
                    pozitie.y--;
                    break;
                case Jos:
                    if(pozitie.y == marime_mapa - 1) { std::cout<<"Nu se poate!\n"; return ; }
                    pozitie.y++;
                    break;
            }
        }

        void Afisare() {
            /// Afisam mapa si pozitia robotului
            int marime_mapa = mapa.GetMarime();
            for(int i = 0; i < marime_mapa; i++)
            {
                ///maybe needs refactoring
                for(int j = 0; j < marime_mapa; j++) {
                    if((i == pozitie.y + 4 || i == pozitie.y + 3 || i == pozitie.y + 2 || i == pozitie.y + 1) && j == pozitie.x)
                        std::cout<<mapa[i][j]<<' ';
                    else if((i == pozitie.y - 4 || i == pozitie.y - 3 || i == pozitie.y - 2 || i == pozitie.y - 1) && j == pozitie.x)
                        std::cout<<mapa[i][j]<<' ';
                    else if((j == pozitie.x + 4 || j == pozitie.x + 3 || j == pozitie.x + 2 || j == pozitie.x + 1) && i == pozitie.y)
                        std::cout<<mapa[i][j]<<' ';
                    else if((j == pozitie.x - 4 || j == pozitie.x - 3 || j == pozitie.x - 2 || j == pozitie.x - 1) && i == pozitie.y)
                        std::cout<<mapa[i][j]<<' ';
                    else if(i == pozitie.y && j == pozitie.x) std::cout<<"X ";
                    else std::cout<<"?"<<' ';
                }
                std::cout<<'\n';
            }
        }

        void SetPozitie(int x, int y) { pozitie.x = x; pozitie.y = y; }
        Punct GetPozitie() { return pozitie; }
};

class Ultra : public Robot{
    char nume;
    public:
        Ultra(): Robot(mapa){
            nume = 'U';
        }
};

#endif // ROBOT_H_INCLUDED
