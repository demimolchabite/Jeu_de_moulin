#ifndef VOL_H_INCLUDED
#define VOL_H_INCLUDED
#include "deplacement.h"


void PoserVol(Plateau& plateau, const Joueur& J, const Coord& depart);
bool deplacementNormal(Plateau& plateau, Joueur& joueur, Joueur& adversaire);
bool deplacementVol(Plateau& plateau, Joueur& volant, Joueur& normal);
void Phase_Deplacement(Plateau& plateau, Joueur& J1, Joueur& J2);
void afficherCasesProtegees(const Plateau& plateau);

#endif // VOL_H_INCLUDED
