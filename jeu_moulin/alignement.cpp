#include "alignement.h"
#include "case.h"    // pour avoir accès à la classe Case complète
#include "plateau.h"
#include "joueur.h"



bool LigneProtegee(const Case& c1, const Case& c2, const Case& c3) {
    return (c1.getEtat() == Case::Protege &&
            c2.getEtat() == Case::Protege &&
            c3.getEtat() == Case::Protege);
}


const Coord triplets[8][3] = {
    {{'A','A'}, {'A','D'}, {'A','G'}},
    {{'B','B'}, {'B','D'}, {'B','F'}},
    {{'C','C'}, {'C','D'}, {'C','E'}},
    {{'D','A'}, {'D','B'}, {'D','C'}},
    {{'E','D'}, {'E','F'}, {'E','G'}},
    {{'F','B'}, {'F','D'}, {'F','F'}},
    {{'G','A'}, {'G','D'}, {'G','G'}},
    {{'D','E'}, {'D','F'}, {'D','G'}}
};


// verifierAlignementHorizontal : utilise triplets (actuellement “horizontal” selon ta liste)
bool verifierAlignementHorizontal(Plateau& plateau, const Joueur& joueur) {
    int aligne = 0;

    for (int i = 0; i < 8; ++i) {
        const Coord& c1 = triplets[i][0];
        const Coord& c2 = triplets[i][1];
        const Coord& c3 = triplets[i][2];

        Case& case1 = plateau.getCase(c1.col, c1.lig);
        Case& case2 = plateau.getCase(c2.col, c2.lig);
        Case& case3 = plateau.getCase(c3.col, c3.lig);

        if (case1.getJoueur() == joueur &&
            case2.getJoueur() == joueur &&
            case3.getJoueur() == joueur &&
            !LigneProtegee(case1, case2, case3)) {

            case1.setEtat(Case::Protege);
            case2.setEtat(Case::Protege);
            case3.setEtat(Case::Protege);
            aligne++;
        }
    }

    return aligne > 0;
}

const Coord mapping[8][3] = {
    {{'A','A'}, {'D','A'}, {'G','A'}},
    {{'B','B'}, {'D','B'}, {'F','B'}},
    {{'C','C'}, {'D','C'}, {'E','C'}},
    {{'A','D'}, {'B','D'}, {'C','D'}},
    {{'E','D'}, {'F','D'}, {'G','D'}},
    {{'C','E'}, {'D','E'}, {'E','E'}},
    {{'B','F'}, {'D','F'}, {'F','F'}},
    {{'A','G'}, {'D','G'}, {'G','G'}}
};

bool verifierAlignementVertical(Plateau& plateau, const Joueur& joueur) {
    int aligne = 0;

    for (int i = 0; i < 8; ++i) {
        const Coord& c1 = mapping[i][0];
        const Coord& c2 = mapping[i][1];
        const Coord& c3 = mapping[i][2];

        Case& case1 = plateau.getCase(c1.col, c1.lig);
        Case& case2 = plateau.getCase(c2.col, c2.lig);
        Case& case3 = plateau.getCase(c3.col, c3.lig);

        if (case1.getJoueur() == joueur &&
            case2.getJoueur() == joueur &&
            case3.getJoueur() == joueur &&
            !LigneProtegee(case1, case2, case3)) {

            case1.setEtat(Case::Protege);
            case2.setEtat(Case::Protege);
            case3.setEtat(Case::Protege);
            aligne++;
        }
    }

    return aligne > 0;
}




bool verifierAlignementHorizontalSurCase(Plateau& plateau, const Case& c, const Joueur& joueur) {
    for (int i = 0; i < 8; ++i) {
        const Coord& c1 = triplets[i][0];
        const Coord& c2 = triplets[i][1];
        const Coord& c3 = triplets[i][2];

        // Vérifie si la case c correspond à une des trois cases du triplet
        if (!((c.gethorizontal() == c1.col && c.getvertical() == c1.lig) ||
              (c.gethorizontal() == c2.col && c.getvertical() == c2.lig) ||
              (c.gethorizontal() == c3.col && c.getvertical() == c3.lig))) {
            continue;
        }

        Case& case1 = plateau.getCase(c1.col, c1.lig);
        Case& case2 = plateau.getCase(c2.col, c2.lig);
        Case& case3 = plateau.getCase(c3.col, c3.lig);

        if (case1.getJoueur() == joueur &&
            case2.getJoueur() == joueur &&
            case3.getJoueur() == joueur) {
            return true;
        }
    }
    return false;
}

bool verifierAlignementVerticalSurCase(Plateau& plateau, const Case& c, const Joueur& joueur) {
    // mapping vertical corrigé (colonnes fixes)
    char mapping[3][8][2] = {
        { {'A','A'}, {'A','D'}, {'A','G'}, {'B','B'}, {'B','D'}, {'B','F'}, {'C','C'}, {'C','D'} },
        { {'C','E'}, {'D','A'}, {'D','B'}, {'D','C'}, {'D','E'}, {'D','F'}, {'D','G'}, {'E','C'} },
        { {'E','D'}, {'E','E'}, {'F','B'}, {'F','D'}, {'F','F'}, {'G','A'}, {'G','D'}, {'G','G'} }
    };

    for (int col = 0; col < 8; ++col) {
        bool caseTrouvee = false;
        for (int row = 0; row < 3; ++row) {
            if (c.gethorizontal() == mapping[row][col][0] &&
                c.getvertical() == mapping[row][col][1]) {
                caseTrouvee = true;
                break;
            }
        }
        if (!caseTrouvee) continue;

        bool toutesCasesJoueur = true;
        for (int row = 0; row < 3; ++row) {
            Case& caseX = plateau.getCase(mapping[row][col][0], mapping[row][col][1]);
            if (caseX.getJoueur() != joueur) {
                toutesCasesJoueur = false;
                break;
            }
        }
        if (toutesCasesJoueur) return true;
    }
    return false;
}


std::pair<Case*, Case*> getAlignementHorizontalCases(Plateau& plateau, const Case& c, const Joueur& joueur) {
    for (int i = 0; i < 8; ++i) {
        const Coord& c1 = triplets[i][0];
        const Coord& c2 = triplets[i][1];
        const Coord& c3 = triplets[i][2];

        // Vérifie si la case c correspond à une des cases du triplet
        if (!((c.gethorizontal() == c1.col && c.getvertical() == c1.lig) ||
              (c.gethorizontal() == c2.col && c.getvertical() == c2.lig) ||
              (c.gethorizontal() == c3.col && c.getvertical() == c3.lig))) {
            continue;
        }

        Case& case1 = plateau.getCase(c1.col, c1.lig);
        Case& case2 = plateau.getCase(c2.col, c2.lig);
        Case& case3 = plateau.getCase(c3.col, c3.lig);

        // Vérifie que les 3 cases appartiennent au joueur
        if (case1.getJoueur() == joueur &&
            case2.getJoueur() == joueur &&
            case3.getJoueur() == joueur) {

            // Identifie la position de la case c dans le triplet
            if (c.gethorizontal() == c1.col && c.getvertical() == c1.lig) {
                return { &case2, &case3 };
            } else if (c.gethorizontal() == c2.col && c.getvertical() == c2.lig) {
                return { &case1, &case3 };
            } else {
                return { &case1, &case2 };
            }
        }
    }
    return { nullptr, nullptr };
}

std::pair<Case*, Case*> getAlignementVerticalCases(Plateau& plateau, const Case& c, const Joueur& joueur) {
    char mapping[3][8][2] = {
        { {'A','A'}, {'A','D'}, {'A','G'}, {'B','B'}, {'B','D'}, {'B','F'}, {'C','C'}, {'C','D'} },
        { {'C','E'}, {'D','A'}, {'D','B'}, {'D','C'}, {'D','E'}, {'D','F'}, {'D','G'}, {'E','C'} },
        { {'E','D'}, {'E','E'}, {'F','B'}, {'F','D'}, {'F','F'}, {'G','A'}, {'G','D'}, {'G','G'} }
    };

    for (int col = 0; col < 8; ++col) {
        int pos = -1;
        // Trouve la position de la case c dans la colonne verticale
        for (int row = 0; row < 3; ++row) {
            if (c.gethorizontal() == mapping[row][col][0] && c.getvertical() == mapping[row][col][1]) {
                pos = row;
                break;
            }
        }
        if (pos == -1) continue;

        Case& case1 = plateau.getCase(mapping[0][col][0], mapping[0][col][1]);
        Case& case2 = plateau.getCase(mapping[1][col][0], mapping[1][col][1]);
        Case& case3 = plateau.getCase(mapping[2][col][0], mapping[2][col][1]);

        if (case1.getJoueur() == joueur &&
            case2.getJoueur() == joueur &&
            case3.getJoueur() == joueur) {

            if (pos == 0) return { &case2, &case3 };
            else if (pos == 1) return { &case1, &case3 };
            else /* pos == 2 */ return { &case1, &case2 };
        }
    }
    return { nullptr, nullptr };
}
