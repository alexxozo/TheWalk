#include <iostream>
#include "Harta.h"
#include "Robot.h"
#include "Joc.h"
#include <fstream>
using namespace std;


int main() {

    Robot *r;
    Ultra u;
    Giga g;
    r = &g;
    Joc joc(15, r);
    joc.Joaca(NORMAL);




    return 0;
}