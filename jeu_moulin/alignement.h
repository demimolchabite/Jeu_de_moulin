#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H

#include "plateau.h"
#include "joueur.h"

struct Coord {
    char col;  // ex: 'A'
    char lig;  // ex: 'A'
};



bool LigneProtegee(const Case& c1, const Case& c2, const Case& c3);

bool verifierAlignementHorizontal(Plateau& plateau, const Joueur& joueur);

bool verifierAlignementVertical(Plateau& plateau, const Joueur& joueur);

bool verifierAlignementHorizontalSurCase(Plateau& plateau, const Case& c, const Joueur& joueur);

bool verifierAlignementVerticalSurCase(Plateau& plateau, const Case& c, const Joueur& joueur);

std::pair<Case*, Case*> getAlignementHorizontalCases(Plateau& plateau, const Case& c, const Joueur& joueur);

std::pair<Case*, Case*> getAlignementVerticalCases(Plateau& plateau, const Case& c, const Joueur& joueur);


#endif // ALIGNEMENT_H
