#include <iostream>
#include <cstdlib>

#include "plateau.h"
#include "joueur.h"
#include "case.h"
#include "placement.h"
#include "vol.h"





void boucleDeJeu(Plateau& monPlateau) {
    Joueur h,j;
    do {

        h = Creation_Joueur();
        j = Creation_Joueur();
    }while(h==j);
        monPlateau.AfficherPlateau();

        Joueur final_1 = Phase_De_Placement(h, j);

        monPlateau.AfficherPlateau();

        if (final_1 == h)
            Phase_Deplacement(monPlateau, h, j);

        if (final_1 == j)
            Phase_Deplacement(monPlateau, j, h);

        monPlateau.AfficherPlateau();
}

