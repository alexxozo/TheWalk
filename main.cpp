#include <iostream>
#include "Robot.h"
#include "Harta.h"
#include "Joc.h"

using namespace std;

void Meniu_Principal() {
    cout << "TheWalk\n";
    cout << "Explore your surroundings...\n";
    cout << "Bine ai venit!\n";
    cout << "Scopul jocului este de a ajunge din pozitia de start in cea finala in cat mai putine  runde\n";
    cout << "posibil. Exista 3 tipuri de roboti din care poti alege ULTRA/MEGA/GIGA fiecare poate folosi un singur tip de item \n";
    cout << "cu scopul de a cauta finalul traseului si de a scapa de capcane ce apar la fiecare pas.\n";
    cout << "Capcanele ce vor aparea pe harta sunt:\n ";
    cout << "- groapa (marcata cu '#' te va omora)\n";
    cout << "- intoarcere in timp (marcata cu '~' te va intoarce la pozitia initiala)\n";
    cout << "- capcana de urs (marcata cu '!' te va omora)\n";
    cout << "Controalele sunt foarte simple, vom utiliza literele w a s d pentru a misca robotul pe harta. Dupa afisarea hartii in fiecare runda vei putea introduce comanda iar apoi trebuie sa apesi enter pentru a fi inregistrata.\n";
    cout << "Alege robotul si haide sa incepem!\n";
    cout << "1.Ultra - poate folosi itemul: Potiune de invincibilitate marcat cu litera 'i' pe harta(vei fi invincibil pentru urmatoarele 8 runde)\n";
    cout << "2.Mega - poate folosi itemul: Papuci saltareti marcat cu litera 's' pe harta(vei putea sari peste urmatorul obstacol intalnit)\n";
    cout << "3.Giga - poate folosi itemul: Potiune de vedere marcat cu litera 'v' pe harta(vei putea vedea la 8 casute in jurul tau pentru 8 runde)\n";

    /// Setup
    Robot robot;
    int optiuneRobot, marimeHarta, optiuneMod;

    INTRARE_ROBOT:
    cin >> optiuneRobot;

    switch (optiuneRobot) {
        case 1: {
            robot = Ultra();
            break;
        }
        case 2: {
            robot = Mega();
            break;
        }
        case 3: {
            robot = Giga();
            break;
        }
        default: {
            cout << "Te rugam sa introduci o optiune valida (1-2-3)";
            goto INTRARE_ROBOT;
        }
    }


    cout << "\nAlege cat de mare sa fie harta (marime minima 15 lungime/latime)";
    cin >> marimeHarta;

    INTRARE_MOD:
    cout << "\nMod de joc:\n";
    cout << "1.Joc normal\n";
    cout << "2.Joc simulat de calculator\n";
    cin >> optiuneMod;

    Joc joc(marimeHarta, robot);

    switch(optiuneMod) {
        case 1: {
            joc.Joaca(NORMAL);
            break;
        }
        case 2: {
            joc.Joaca(SIMULARE);
            break;
        }
        default: {
            cout << "Te rugam sa introduci o optiune valida (1-2)";
            goto INTRARE_MOD;
        }
    }
}

int main() {

    Meniu_Principal();
    return 0;
}
