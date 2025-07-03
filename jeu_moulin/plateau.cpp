#include <iostream>
#include "plateau.h"
#include "joueur.h"
#include "case.h"
#include "placement.h"


void afficherCoordonneesPlateau(const Plateau& plateau) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            char abs = plateau.table[i][j].gethorizontal();  // ou getAbscisse()
            char ord = plateau.table[i][j].getvertical();    // ou getOrdonnee()
            std::cout << "Case [" << i << "][" << j << "] -> Abscisse: " << abs << ", Ordonnee: " << ord << std::endl;
        }
    }
}

bool Plateau::coordExiste(char abs, char ord) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (table[i][j].gethorizontal() == abs &&
                table[i][j].getvertical() == ord) {
                return true;
            }
        }
    }
    return false;
}

