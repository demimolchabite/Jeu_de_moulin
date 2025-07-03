#ifndef DEPLACEMENT_H_INCLUDED
#define DEPLACEMENT_H_INCLUDED

#include "alignement.h"

// Mapping des coordonnées du plateau (8 colonnes x 3 lignes)
extern char mapping[8][3][2];

// Tableau des alignements verticaux/horizontaux
extern const Coord triplets[8][3];

bool caseDansAlignement(const Coord& c, const Coord triplet[3]);
bool alignementActif(const Plateau& plateau, const Coord triplet[3], const Joueur& j);
void deprotegerLignes(Plateau& plateau, const Coord& coord, const Joueur& j);
Coord demanderCoordonnees();
bool estAlignement(const Plateau& plateau, const Coord& c1, const Coord& c2, const Coord& c3, const Joueur& j);
void verifierEtDeproteger(Plateau& plateau, const Joueur& j, const Coord& coord);
Case Retirer(Plateau& plateau, const Joueur& j);
Coord Prendre(Plateau& plateau, const Joueur& J);
void Poser(Plateau& plateau, const Joueur& J, const Coord& depart);


#endif // DEPLACEMENT_H_INCLUDED
