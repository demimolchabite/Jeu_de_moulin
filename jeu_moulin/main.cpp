#include <iostream>
#include <cstdlib>
#include "plateau.h"
#include "jeu.h"

using namespace std;


Joueur j_vide(0, ' ', "vide",0);
Case Plateau::table[8][3];
Plateau monPlateau(1);

int main() {

    cout << "\t\t\t\t\t=== JEU DE PLATEAU ===" << endl;

    boucleDeJeu(monPlateau);



    return 0;
}


