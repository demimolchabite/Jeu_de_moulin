#include <iostream>
#include <limits>
#include <random>
#include <cstdlib>
#include <ctime>

#include "joueur.h"
#include "plateau.h"
#include "case.h"
#include "voisinage.h"
#include "alignement.h"
#include "deplacement.h"

using namespace std;

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

const Coord triplets[8][3] = {
    {{'A','A'}, {'D','A'}, {'G','A'}},
    {{'B','B'}, {'D','B'}, {'F','B'}},
    {{'C','C'}, {'D','C'}, {'E','C'}},
    {{'A','D'}, {'B','D'}, {'C','D'}},
    {{'E','D'}, {'F','D'}, {'G','D'}},
    {{'C','E'}, {'D','E'}, {'E','E'}},
    {{'B','F'}, {'D','F'}, {'F','F'}},
    {{'A','G'}, {'D','G'}, {'G','G'}}
};

// Vérifie si une case est dans un alignement donné
bool caseDansAlignement(const Coord& c, const Coord triplet[3]) {
    for (int i = 0; i < 3; ++i) {
        if (c.col == triplet[i].col && c.lig == triplet[i].lig) {
            return true;
        }
    }
    return false;
}

// Vérifie si un alignement est actif (trois pions du même joueur)
bool alignementActif(const Plateau& plateau, const Coord triplet[3], const Joueur& j) {
    return (plateau.getCase(triplet[0].col, triplet[0].lig).getJoueur() == j &&
            plateau.getCase(triplet[1].col, triplet[1].lig).getJoueur() == j &&
            plateau.getCase(triplet[2].col, triplet[2].lig).getJoueur() == j);
}

void deprotegerLignes(Plateau& plateau, const Coord& coord, const Joueur& j) {
    // Parcourir la ligne horizontale (même lig)
    for (char col = 'A'; col <= 'G'; ++col) {
        Coord candidate{col, coord.lig};
        Case& caseH = plateau.getCase(candidate.col, candidate.lig);

        if (caseH.getEtat() == Case::Protege && caseH.getJoueur() == j) {
            // On vérifie combien d'alignements actifs cette case satisfait
            int nbAlignementsActifs = 0;
            for (int i = 0; i < 8; ++i) {
                const Coord* triplet = triplets[i];
                if (caseDansAlignement(candidate, triplet) && alignementActif(plateau, triplet, j)) {
                    nbAlignementsActifs++;
                }
            }

            // Si moins de 2 alignements actifs, on déprotège la case
            if (nbAlignementsActifs < 2) {
                caseH.setEtat(Case::NonProtege);
            }
        }
    }

    // Parcourir la ligne verticale (même col)
    for (char lig = 'A'; lig <= 'G'; ++lig) {
        Coord candidate{coord.col, lig};
        Case& caseV = plateau.getCase(candidate.col, candidate.lig);

        if (caseV.getEtat() == Case::Protege && caseV.getJoueur() == j) {
            int nbAlignementsActifs = 0;
            for (int i = 0; i < 8; ++i) {
                const Coord* triplet = triplets[i];
                if (caseDansAlignement(candidate, triplet) && alignementActif(plateau, triplet, j)) {
                    nbAlignementsActifs++;
                }
            }

            if (nbAlignementsActifs < 2) {
                caseV.setEtat(Case::NonProtege);
            }
        }
    }

    // Déprotéger la case d'origine à la fin
    Case& caseC = plateau.getCase(coord.col, coord.lig);
    if (caseC.getEtat() == Case::Protege && caseC.getJoueur() == j) {
        caseC.setEtat(Case::NonProtege);
    }
}



Coord demanderCoordonnees() {
    Coord c;
    cout << "Entrez la colonne (A-G) : ";
    cin >> c.col;
    c.col = toupper(c.col);
    while (c.col < 'A' || c.col > 'G') {
        cout << "Colonne invalide. Reessayez (A-G) : ";
        cin >> c.col;
        c.col = toupper(c.col);
    }

    cout << "Entrez la ligne (A-G) : ";
    cin >> c.lig;
    c.lig = toupper(c.lig);
    while (c.lig < 'A' || c.lig > 'G') {
        cout << "Ligne invalide. Reessayez (A-G) : ";
        cin >> c.lig;
        c.lig = toupper(c.lig);
    }

    return c;
}

bool estAlignement(const Plateau& plateau, const Coord& c1, const Coord& c2, const Coord& c3, const Joueur& j) {
    return (plateau.getCase(c1.col, c1.lig).getJoueur() == j &&
            plateau.getCase(c2.col, c2.lig).getJoueur() == j &&
            plateau.getCase(c3.col, c3.lig).getJoueur() == j);
}

void verifierEtDeproteger(Plateau& plateau, const Joueur& j, const Coord& coord) {
    Case& caseC = plateau.getCase(coord.col, coord.lig);

    // Récupérer les deux autres cases des alignements horizontal et vertical
    auto [hCase1, hCase2] = getAlignementHorizontalCases(plateau, caseC, j);
    auto [vCase1, vCase2] = getAlignementVerticalCases(plateau, caseC, j);

    // Fonction lambda pour vérifier la double appartenance à un alignement
    auto verifieDoubleAlignement = [&](Case* c) -> bool {
        if (!c) return false; // nullptr -> pas d'alignement
        bool horiz = verifierAlignementHorizontalSurCase(plateau, *c, j);
        bool vert = verifierAlignementVerticalSurCase(plateau, *c, j);
        return horiz && vert;
    };

    // Vérifier et déprotéger cases dans alignement horizontal (autres que caseC)
    if (hCase1 && hCase1->getEtat() == Case::Protege && hCase1->getJoueur() == j) {
        if (!verifieDoubleAlignement(hCase1)) {
            hCase1->setEtat(Case::NonProtege);
        }
    }
    if (hCase2 && hCase2->getEtat() == Case::Protege && hCase2->getJoueur() == j) {
        if (!verifieDoubleAlignement(hCase2)) {
            hCase2->setEtat(Case::NonProtege);
        }
    }

    // Vérifier et déprotéger cases dans alignement vertical (autres que caseC)
    if (vCase1 && vCase1->getEtat() == Case::Protege && vCase1->getJoueur() == j) {
        if (!verifieDoubleAlignement(vCase1)) {
            vCase1->setEtat(Case::NonProtege);
        }
    }
    if (vCase2 && vCase2->getEtat() == Case::Protege && vCase2->getJoueur() == j) {
        if (!verifieDoubleAlignement(vCase2)) {
            vCase2->setEtat(Case::NonProtege);
        }
    }

    // Enfin, déprotéger la case concernée
    if (caseC.getEtat() == Case::Protege && caseC.getJoueur() == j) {
        caseC.setEtat(Case::NonProtege);
    }
}


void verifierEtDeprotegerSimple(Plateau& plateau, const Joueur& j, const Coord& coord) {
    Case& caseC = plateau.getCase(coord.col, coord.lig);

    // Vérifier si la case est protégée et appartient au joueur
    if (caseC.getEtat() == Case::Protege && caseC.getJoueur() == j) {
        // Vérifier s'il y a au moins un alignement actif qui contient cette case
        bool alignementExiste = false;
        for (int i = 0; i < 8; ++i) {
            const Coord* triplet = triplets[i];
            if (caseDansAlignement(coord, triplet) && alignementActif(plateau, triplet, j)) {
                alignementExiste = true;
                break;
            }
        }
        // Si aucun alignement actif, on déprotège la case
        if (!alignementExiste) {
            caseC.setEtat(Case::NonProtege);
        }
    }
}





Case Retirer(Plateau& plateau, const Joueur& j) {
    cout << " ===== Retrait des pions du joueur : " << j.getnom() << "====" << endl;
    Coord c;
    Case* cible;

    do {
        c = demanderCoordonnees();
        cible = &plateau.getCase(c.col, c.lig);

        if (cible->getJoueur() != j) {
            cout << "Cette case ne vous appartient pas ou est vide. Veuillez reessayer." << endl;
            continue;
        }

        if (cible->getEtat() == Case::Protege) {
            cout << "Ce pion est protege. Impossible de le retirer. Veuillez reessayer." << endl;
            continue;
        }

        break;

    } while (true);

    // Suppression du pion
    plateau.modifierCase(j_vide, c.col, c.lig);

    // Mise à jour des protections des alignements affectés par la case c
    verifierEtDeproteger(plateau, j, c);

    return plateau.getCase(c.col, c.lig);
}


Coord Prendre(Plateau& plateau, const Joueur& J) {
    Coord c;
    Case* cible = nullptr;

    do {
        c = demanderCoordonnees();
        cible = &plateau.getCase(c.col, c.lig);

        if (cible->getJoueur() != J) {
            cout << "Ce pion ne vous appartient pas." << endl;
            continue;
        }

        break;
    } while (true);

    // Déprotéger avec la nouvelle règle plus souple
    verifierEtDeprotegerSimple(plateau, J, c);

    // Vider la case
    plateau.modifierCase(j_vide, c.col, c.lig);

    return c;
}


void Poser(Plateau& plateau, const Joueur& J, const Coord& depart) {
    Coord c;

    do {
        c = demanderCoordonnees();

        if (plateau.getCase(c.col, c.lig).getJoueur() != j_vide) {
            cout << "Impossible de poser ici, case occupee par "<<plateau.getCase(c.col,c.lig).getJoueur().getnom()<<" Reessayez." << endl;
            continue;
        }

        if (!CasesVoisines(depart, c)) {
            cout << "Impossible de poser ici, ce n'est pas une case voisine. Reessayez." << endl;
            continue;
        }

        break;

    } while (true);

    plateau.modifierCase(J, c.col, c.lig);
}

/*Joueur Phase_De_Deplacement(Plateau& plateau, Joueur J1, Joueur J2) {
    while (true) {
        // Tour de J1
        Coord depart = Prendre(plateau, J1);
        plateau.AfficherPlateau();

        Poser(plateau, J1, depart);
        plateau.AfficherPlateau();

        if (verifierAlignementHorizontal(plateau, J1) || verifierAlignementVertical(plateau, J1)) {
            cout << "Alignement detecte pour " << J1.getnom() << " !\n";
            Retirer(plateau, J2);
            system("Pause");

            plateau.mettreAJourNbPions(J2);
            plateau.AfficherPlateau();

            if (J2.getNbPions() == 3) {
                cout << "\n" << J2.getnom() << " n'a plus que 3 pions ! Passage à la phase suivante...\n";
                return J2;
            }
        }

        // Tour de J2
        depart = Prendre(plateau, J2);
        plateau.AfficherPlateau();

        Poser(plateau, J2, depart);
        plateau.AfficherPlateau();

        if (verifierAlignementHorizontal(plateau, J2) || verifierAlignementVertical(plateau, J2)) {
            cout << "Alignement detecte pour " << J2.getnom() << " !\n";
            Retirer(plateau, J1);
            system("Pause");

            plateau.mettreAJourNbPions(J1);
            plateau.AfficherPlateau();

            if (J1.getNbPions() == 3) {
                cout << "\n " << J1.getnom() << " n'a plus que 3 pions ! Passage à la phase suivante...\n";
                return J1;
            }
        }
    }
}*/
