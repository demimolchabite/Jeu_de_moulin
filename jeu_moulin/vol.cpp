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





void PoserVol(Plateau& plateau, const Joueur& J, const Coord& depart) {
    Coord c;

    do {
        c = demanderCoordonnees();

        if (plateau.getCase(c.col, c.lig).getJoueur() != j_vide) {
            std::cout << "Impossible de poser ici, case occupee par "
                      << plateau.getCase(c.col, c.lig).getJoueur().getnom() << ". Reessayez.\n";
            continue;
        }

        if (c.col == depart.col && c.lig == depart.lig) {
            std::cout << "Vous devez deplacer le pion a un autre emplacement. Reessayez.\n";
            continue;
        }

        break;

    } while (true);

    plateau.modifierCase(J, c.col, c.lig);
}

void afficherCasesProtegees(const Plateau& plateau) {
    cout << "Cases protégées sur le plateau :\n";
    for (char col = 'A'; col <= 'G'; ++col) {
        for (char lig = 'A'; lig <= 'G'; ++lig) {
            const Case& c = plateau.getCase(col, lig);
            if (c.getEtat() == Case::Protege) {
                cout << "Case " << col << lig
                     << " protégée, appartient à : " << c.getJoueur().getnom() << "\n";
            }
        }
    }
}


bool deplacementNormal(Plateau& plateau, Joueur& joueur, Joueur& adversaire) {
    Coord depart = Prendre(plateau, joueur);
    plateau.AfficherPlateau();

    Poser(plateau, joueur, depart);
    plateau.AfficherPlateau();

    if (verifierAlignementHorizontal(plateau, joueur) | verifierAlignementVertical(plateau, joueur)) {
        std::cout << "Alignement detecte pour " << joueur.getnom() << " !\n";
        Retirer(plateau, adversaire);
        system("Pause");

        plateau.mettreAJourNbPions(adversaire);
        plateau.AfficherPlateau();

        if (adversaire.getNbPions() <= 3) {
            std::cout << "\n" << adversaire.getnom() << " n'a plus que " << adversaire.getNbPions()
                 << " pions ! Passage a la phase suivante...\n";
            return true;
        }
    }
    return false;
}

bool deplacementVol(Plateau& plateau, Joueur& volant, Joueur& normal) {
    Coord depart = Prendre(plateau, volant);
    plateau.AfficherPlateau();

    PoserVol(plateau, volant, depart);
    plateau.AfficherPlateau();

    if (verifierAlignementHorizontal(plateau, volant) | verifierAlignementVertical(plateau, volant)) {
        std::cout << "Alignement detecte pour " << volant.getnom() << " !\n";
        Retirer(plateau, normal);
        system("Pause");

        plateau.mettreAJourNbPions(normal);
        plateau.AfficherPlateau();

        if (normal.getNbPions() <= 3) {
            std::cout << "\n" << normal.getnom() << " n'a plus que " << normal.getNbPions()
                 << " pions !\n";
            return true;
        }
    }
    return false;
}

void Phase_Deplacement(Plateau& plateau, Joueur& J1, Joueur& J2) {
    while (true) {
        plateau.mettreAJourNbPions(J1);
        plateau.mettreAJourNbPions(J2);

        if (J1.getNbPions() > 3) {
            std::cout << "\nTour de " << J1.getnom() << " (deplacement normal)" << std::endl;

            std::cout << "[DEBUG] Cases protegees avant deplacement de " << J1.getnom() << " :\n";
            afficherCasesProtegees(plateau);

            if (deplacementNormal(plateau, J1, J2)) {
                std::cout << "[DEBUG] Cases protegees avant retrait apres alignement de " << J1.getnom() << " :\n";
                afficherCasesProtegees(plateau);
            }

            std::cout << "[DEBUG] Cases protegees apres deplacement de " << J1.getnom() << " :\n";
            afficherCasesProtegees(plateau);
        } else {
            std::cout << "\nTour de " << J1.getnom() << " (deplacement en vol)" << std::endl;

            std::cout << "[DEBUG] Cases protegees avant deplacement de " << J1.getnom() << " :\n";
            afficherCasesProtegees(plateau);

            if (deplacementVol(plateau, J1, J2)) {
                std::cout << "[DEBUG] Cases protegees avant retrait apres alignement de " << J1.getnom() << " :\n";
                afficherCasesProtegees(plateau);
            }

            std::cout << "[DEBUG] Cases protegees apres deplacement de " << J1.getnom() << " :\n";
            afficherCasesProtegees(plateau);
        }

        plateau.mettreAJourNbPions(J1);
        plateau.mettreAJourNbPions(J2);

        if (J1.getNbPions() == 2) {
            std::cout << "\n" << J1.getnom() << " n'a plus que 2 pions. Partie terminee !" << std::endl;
            std::cout << "Victoire de " << J2.getnom() << " !" << std::endl;
            break;
        }
        if (J2.getNbPions() == 2) {
            std::cout << "\n" << J2.getnom() << " n'a plus que 2 pions. Partie terminee !" << std::endl;
            std::cout << "Victoire de " << J1.getnom() << " !" << std::endl;
            break;
        }

        plateau.mettreAJourNbPions(J1);
        plateau.mettreAJourNbPions(J2);

        if (J2.getNbPions() > 3) {
            std::cout << "\nTour de " << J2.getnom() << " (deplacement normal)" << std::endl;

            std::cout << "[DEBUG] Cases protegees avant deplacement de " << J2.getnom() << " :\n";
            afficherCasesProtegees(plateau);

            if (deplacementNormal(plateau, J2, J1)) {
                std::cout << "[DEBUG] Cases protegees avant retrait apres alignement de " << J2.getnom() << " :\n";
                afficherCasesProtegees(plateau);
            }

            std::cout << "[DEBUG] Cases protegees apres deplacement de " << J2.getnom() << " :\n";
            afficherCasesProtegees(plateau);
        } else {
            std::cout << "\nTour de " << J2.getnom() << " (deplacement en vol)" << std::endl;

            std::cout << "[DEBUG] Cases protegees avant deplacement de " << J2.getnom() << " :\n";
            afficherCasesProtegees(plateau);

            if (deplacementVol(plateau, J2, J1)) {
                std::cout << "[DEBUG] Cases protegees avant retrait apres alignement de " << J2.getnom() << " :\n";
                afficherCasesProtegees(plateau);
            }

            std::cout << "[DEBUG] Cases protegees apres deplacement de " << J2.getnom() << " :\n";
            afficherCasesProtegees(plateau);
        }

        plateau.mettreAJourNbPions(J1);
        plateau.mettreAJourNbPions(J2);

        if (J1.getNbPions() == 2) {
            std::cout << "\n" << J1.getnom() << " n'a plus que 2 pions. Partie terminee !" << std::endl;
            std::cout << "Victoire de " << J2.getnom() << " !" << std::endl;
            break;
        }
        if (J2.getNbPions() == 2) {
            std::cout << "\n" << J2.getnom() << " n'a plus que 2 pions. Partie terminee !" << std::endl;
            std::cout << "Victoire de " << J1.getnom() << " !" << std::endl;
            break;
        }
    }
}
