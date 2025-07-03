#include <iostream>
#include <limits>
#include <random>
#include <cstdlib>
#include <ctime>

#include "joueur.h"
#include "plateau.h"
#include "case.h"
#include "alignement.h"
#include "deplacement.h"
#include "vol.h"

using namespace std;
extern Plateau monPlateau;

void clearConsole() {
    system("cls"); // Nettoyage console Windows
}



// Création d'un joueur avec gestion correcte du nom (copie profonde à prévoir dans Joueur)
Joueur Creation_Joueur(){
    char nom[10];
    int couleur;
    char caractere;

    cout << "Entrez le nom du joueur : ";
    cin.getline(nom,10);

    cout << "Entrez la couleur du joueur (nombre entier) : ";
    cin >> couleur;

    cout << "Entrez le caractere d'affichage du joueur : ";
    cin >> caractere;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Joueur j(couleur, caractere, nom);
    return j;
}

// Tirage aléatoire entre a et b (retourne soit a soit b)
int tirage(int a, int b) {
    int r = rand() % 2; // 0 ou 1
    return r == 0 ? a : b;
}




void Jouer_un_Coup(Joueur J) {
    char abs, ord;

    while (true) {
        cout << "____ Joueur " << J.getnom() << ", C'est a toi de jouer ____" << endl;
        cout << "Entrez l'abscisse (A-G ou N) : ";
        cin >> abs;
        abs = toupper(abs);

        cout << "Entrez l'ordonnee (A-G ou O) : ";
        cin >> ord;
        ord = toupper(ord);

        bool abscisseValide = (abs >= 'A' && abs <= 'G') || abs == 'N';
        bool ordonneeValide = (ord >= 'A' && ord <= 'G') || ord == 'O';

        if (!(abscisseValide && ordonneeValide)) {
            cout << "Coordonnees hors plage. Abscisse = A-G ou N, Ordonnee = A-G ou O.\n";
            continue;
        }

        if (abs == 'N' && ord == 'O') return;

        if (!monPlateau.coordExiste(abs, ord)) {
            cout << "Cette combinaison n'existe pas sur le plateau. Reessayez.\n";
            continue;
        }

        if (!monPlateau.getCase(abs, ord).Case_Vide()) {
            cout << "Cette case est occupee, choisis-en une autre\n";
            continue;
        }

        break;
    }
    monPlateau.mettreAJourNbPions(J);
    monPlateau.modifierCase(J, abs, ord);
}

Joueur Phase_De_Placement(Joueur J1, Joueur J2){
    srand(time(nullptr));

    // On choisit qui commence aléatoirement
    int debut = tirage(J1.getNumero(), J2.getNumero());
    monPlateau.AfficherPlateau();

    if(debut == J1.getNumero()){
        for(int i = 0; i < 9; i++){
            Jouer_un_Coup(J1);

            monPlateau.AfficherPlateau();
            afficherCasesProtegees(monPlateau);  // DEBUG cases protégées

            if(verifierAlignementHorizontal(monPlateau,J1) | verifierAlignementVertical(monPlateau,J1)){
                cout << "Alignement detecte : "<<endl;
                Retirer(monPlateau,J2);

                afficherCasesProtegees(monPlateau);  // DEBUG cases protégées après retrait

                system("Pause");
            }

            Jouer_un_Coup(J2);
            monPlateau.AfficherPlateau();
            afficherCasesProtegees(monPlateau);  // DEBUG cases protégées

            if(verifierAlignementHorizontal(monPlateau,J2) | verifierAlignementVertical(monPlateau,J2)){
                cout << "Alignement detecte : "<<endl;
                Retirer(monPlateau,J1);

                afficherCasesProtegees(monPlateau);  // DEBUG cases protégées après retrait

                system("Pause");
            }
        }
        return J1;
    }
    else {
        for(int i = 0; i < 9; i++){
            Jouer_un_Coup(J2);
            monPlateau.AfficherPlateau();
            afficherCasesProtegees(monPlateau);  // DEBUG cases protégées

            if(verifierAlignementHorizontal(monPlateau,J2) | verifierAlignementVertical(monPlateau,J2)){
                cout << "Alignement detecte : "<<endl;
                Retirer(monPlateau,J1);

                afficherCasesProtegees(monPlateau);  // DEBUG cases protégées après retrait

                system("Pause");
            }

            Jouer_un_Coup(J1);
            monPlateau.AfficherPlateau();
            afficherCasesProtegees(monPlateau);  // DEBUG cases protégées

            if(verifierAlignementHorizontal(monPlateau,J1) | verifierAlignementVertical(monPlateau,J1)){
                cout << "Alignement detecte : "<<endl;
                Retirer(monPlateau,J2);

                afficherCasesProtegees(monPlateau);  // DEBUG cases protégées après retrait

                system("Pause");
            }

        }
        return J2;
    }
}
