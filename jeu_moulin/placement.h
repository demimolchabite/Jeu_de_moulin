#ifndef PLACEMENT_H_INCLUDED
#define PLACEMENT_H_INCLUDED

class Plateau;

Joueur Phase_De_Placement(Joueur J1, Joueur J2);
Joueur Creation_Joueur();
void clearConsole();

int tirerAleatoirementUnDesDeux(int a, int b);

void Jouer_un_Coup(Joueur J);

void afficherCoordonneesPlateau(const Plateau& plateau);


#endif // PLACEMENT_H_INCLUDED
