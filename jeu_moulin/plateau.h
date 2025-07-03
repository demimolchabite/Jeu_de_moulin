#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include <iostream>
#include "decoration.h"
#include "joueur.h"
#include "placement.h"
#include "case.h"






class Plateau {
private:
     int couleur;
     static Case table[8][3];

public:
Plateau(int color) : couleur(color) {
    char mapping[8][3][2] = {
        { {'A','A'}, {'A','D'}, {'A','G'} },
        { {'B','B'}, {'B','D'}, {'B','F'} },
        { {'C','C'}, {'C','D'}, {'C','E'} },
        { {'D','A'}, {'D','B'}, {'D','C'} },
        { {'D','E'}, {'D','F'}, {'D','G'} },
        { {'E','C'}, {'E','D'}, {'E','E'} },
        { {'F','B'}, {'F','D'}, {'F','F'} },
        { {'G','A'}, {'G','D'}, {'G','G'} }
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            table[i][j].setJoueur(j_vide);
            table[i][j].sethorizontal(mapping[i][j][0]);
            table[i][j].setvertical(mapping[i][j][1]);
        }
    }
}
bool coordExiste(char abs, char ord) const;

friend void afficherCoordonneesPlateau(const Plateau&);

static Case& getCase(char abs, char ord) {
    for(int i=0; i<8; i++) {
        for(int j=0; j<3; j++) {
            if(abs == table[i][j].gethorizontal() && ord == table[i][j].getvertical()) {
                return table[i][j];  // renvoyer une référence sur la case trouvée
            }
        }
    }
    static Case caseVide;  // case vide statique pour retourner en cas d'erreur
    return caseVide;
}


void mettreAJourNbPions(Joueur &j) {
    int compteur = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j2 = 0; j2 < 3; ++j2) {
            if (table[i][j2].getJoueur() == j) {
                compteur++;
            }
        }
    }
    j.setNbPions(compteur);
    //cout << "mise a jour joueur : "<<j.getnom()<<"\nNB_Pion : "<<j.getNbPions()<<endl;
}


    void modifierCase(Joueur J, char abs, char ord){
        int i,j;
        Case C = getCase(abs,ord);
        for(i=0; i<8; i++){
            for(j =0; j<3;j++){
                if(table[i][j] == C){
                    table[i][j].setJoueur(J);
                    return;
                }
            }
        }
}


void AfficherPlateau() const {
    clearConsole();
    afficherBanniere();
    cout << "\n\n\t\t\t       A       B     C         D        E     F       G\n";

    for (int i = 0; i <= 15; i++) {
        if (i == 0) {
            cout << "\n\t\t\t   A   "
                 << couleurANSI(table[0][0].getJoueur().getCouleur())
                 << table[0][0].getJoueur().getCaractere() << "\033[0m"
                 << " --------------------- "
                 << couleurANSI(table[0][1].getJoueur().getCouleur())
                 << table[0][1].getJoueur().getCaractere() << "\033[0m"
                 << " -------------------- "
                 << couleurANSI(table[0][2].getJoueur().getCouleur())
                 << table[0][2].getJoueur().getCaractere() << "\033[0m";
        }
        else if (i == 8) {
            cout << "\n\t\t\t   D   "
                 << couleurANSI(table[3][0].getJoueur().getCouleur())
                 << table[3][0].getJoueur().getCaractere() << "\033[0m"
                 << "-----  "
                 << couleurANSI(table[3][1].getJoueur().getCouleur())
                 << table[3][1].getJoueur().getCaractere() << "\033[0m"
                 << "  ---"
                 << couleurANSI(table[3][2].getJoueur().getCouleur())
                 << table[3][2].getJoueur().getCaractere() << "\033[0m"
                 << "                  "
                 << couleurANSI(table[4][0].getJoueur().getCouleur())
                 << table[4][0].getJoueur().getCaractere() << "\033[0m"
                 << "---  "
                 << couleurANSI(table[4][1].getJoueur().getCouleur())
                 << table[4][1].getJoueur().getCaractere() << "\033[0m"
                 << " ----- "
                 << couleurANSI(table[4][2].getJoueur().getCouleur())
                 << table[4][2].getJoueur().getCaractere() << "\033[0m";
        }
        // Même principe pour tous les autres cas...
        // Juste entourer chaque getCaractere() par couleurANSI() et "\033[0m"
        else if (i == 3) {
            cout << "\n\t\t\t   B   |       "
                 << couleurANSI(table[1][0].getJoueur().getCouleur())
                 << table[1][0].getJoueur().getCaractere() << "\033[0m"
                 << " ------------- "
                 << couleurANSI(table[1][1].getJoueur().getCouleur())
                 << table[1][1].getJoueur().getCaractere() << "\033[0m"
                 << " -------------"
                 << couleurANSI(table[1][2].getJoueur().getCouleur())
                 << table[1][2].getJoueur().getCaractere() << "\033[0m"
                 << "       |";
        }
        else if (i == 6) {
            cout << "\n\t\t\t   C   |       |      "
                 << couleurANSI(table[2][0].getJoueur().getCouleur())
                 << table[2][0].getJoueur().getCaractere() << "\033[0m"
                 << "------- "
                 << couleurANSI(table[2][1].getJoueur().getCouleur())
                 << table[2][1].getJoueur().getCaractere() << "\033[0m"
                 << " ------"
                 << couleurANSI(table[2][2].getJoueur().getCouleur())
                 << table[2][2].getJoueur().getCaractere() << "\033[0m"
                 << "      |       |";
        }
        else if ((i == 1) || (i == 2) || (i == 14) || (i == 15)) {
            cout << "\n\t\t\t       |                       |                      |";
        }
        else if ((i == 4) || (i == 5) || (i == 11) || (i == 12)) {
            cout << "\n\t\t\t       |       |               |              |       |";
        }
        else if (i == 10) {
            cout << "\n\t\t\t   E   |       |      "
                 << couleurANSI(table[5][0].getJoueur().getCouleur())
                 << table[5][0].getJoueur().getCaractere() << "\033[0m"
                 << "------- "
                 << couleurANSI(table[5][1].getJoueur().getCouleur())
                 << table[5][1].getJoueur().getCaractere() << "\033[0m"
                 << " ------"
                 << couleurANSI(table[5][2].getJoueur().getCouleur())
                 << table[5][2].getJoueur().getCaractere() << "\033[0m"
                 << "      |       |";
        }
        else if (i == 13) {
            cout << "\n\t\t\t   F   |       "
                 << couleurANSI(table[6][0].getJoueur().getCouleur())
                 << table[6][0].getJoueur().getCaractere() << "\033[0m"
                 << " ------------- "
                 << couleurANSI(table[6][1].getJoueur().getCouleur())
                 << table[6][1].getJoueur().getCaractere() << "\033[0m"
                 << " -------------"
                 << couleurANSI(table[6][2].getJoueur().getCouleur())
                 << table[6][2].getJoueur().getCaractere() << "\033[0m"
                 << "       |";
        }
        else if ((i == 7) || (i == 9)) {
            cout << "\n\t\t\t       |       |     |                  |     |       |";
        }
    }

    cout << "\n\t\t\t   G   "
         << couleurANSI(table[7][0].getJoueur().getCouleur())
         << table[7][0].getJoueur().getCaractere() << "\033[0m"
         << " --------------------- "
         << couleurANSI(table[7][1].getJoueur().getCouleur())
         << table[7][1].getJoueur().getCaractere() << "\033[0m"
         << " -------------------- "
         << couleurANSI(table[7][2].getJoueur().getCouleur())
         << table[7][2].getJoueur().getCaractere() << "\033[0m"
         << "\n";
}

};




void afficherCoordonneesPlateau(const Plateau& plateau);

#endif // PLATEAU_H_INCLUDED
