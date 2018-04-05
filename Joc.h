#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED

#include "Harta.h"
#include "Robot.h"

class Joc {

    Harta harta;
    Robot robo;
    int runda;
    bool joc_terminat;

    public:
        Joc():harta(), robo(harta){ runda = 0; joc_terminat = false; };
        Joc(int marime, Punct sosire) : harta(marime, sosire),
                                        robo(harta) { runda = 0; joc_terminat = false; };

        void Joaca() {
            while(!joc_terminat) {

                runda++;
                if(runda == 1) robo.Afisare();

                std::cout<<"Runda: "<<runda<<'\n';

                /// jucam runda
                JoacaRunda();

            }
            std::cout<<"Ai terminat jocul in "<<runda<<" de runde";
        }

        void JoacaRunda() {

            char dir;
            bool miscare_inregistrata = false;
            Punct pozitie_curenta = robo.GetPozitie();
            Punct sosire = harta.GetSosire();

            while(!miscare_inregistrata) {
                std::cin>>dir;
                switch(dir) {
                    case 'a':
                        robo.Misca(Stanga);
                        miscare_inregistrata = true;
                        break;
                    case 'd' :
                        robo.Misca(Dreapta);
                        miscare_inregistrata = true;
                        break;
                    case 'w' :
                        robo.Misca(Sus);
                        miscare_inregistrata = true;
                        break;
                    case 's' :
                        robo.Misca(Jos);
                        miscare_inregistrata = true;
                        break;
                    default :
                        miscare_inregistrata = false;
                        std::cout<<"Va rugam sa introduceti una dintre literele w a s d\n";
                        break;
                }
                if(miscare_inregistrata) break;
            }

            robo.Afisare();
            pozitie_curenta = robo.GetPozitie();
            if(pozitie_curenta.x == sosire.x &&
               pozitie_curenta.y == sosire.y) {
                    joc_terminat = true;
               }

        }

};

#endif // JOC_H_INCLUDED
