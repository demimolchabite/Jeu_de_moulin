#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include <cstring>
#include <iostream>
using namespace std;

class Joueur {
    int numero;
    int couleur;
    char caractere;
    char *nom;
    int nbPions;

public:
    // Constructeur par défaut
    Joueur() {
        numero = 0;
        couleur = 0;
        caractere = ' ';
        nom = new char[1];
        nom[0] = '\0';
        nbPions = 9;
    }

    // Constructeur avec paramètres
    Joueur(int color, char c, const char *name, int number = 0) {
        couleur = color;
        caractere = c;
        nom = new char[strlen(name) + 1];
        strcpy(nom, name);
        numero = number;
        nbPions = 9;
    }

    // Constructeur par recopie
    Joueur(const Joueur &j) {
        numero = j.numero;
        couleur = j.couleur;
        caractere = j.caractere;
        nom = new char[strlen(j.nom) + 1];
        strcpy(nom, j.nom);
        nbPions = j.nbPions;
    }

    // Opérateur d’affectation
    Joueur& operator=(const Joueur &j) {
        if (this != &j) {
            numero = j.numero;
            couleur = j.couleur;
            caractere = j.caractere;
            delete[] nom;
            nom = new char[strlen(j.nom) + 1];
            strcpy(nom, j.nom);
            nbPions = j.nbPions;
        }
        return *this;
    }

    bool operator==(const Joueur& other) const {
    return numero == other.numero &&
           couleur == other.couleur &&
           caractere == other.caractere &&
           strcmp(nom, other.nom) == 0;
}


    bool operator!=(const Joueur& other) const {
        return !(*this == other);
    }

    // Méthode d'affichage
    void afficher_info() const {
        cout << " ____ AFFICHAGE DE JOUEUR ____" << endl;
        cout << "\tNumero = " << numero << "\tCouleur = " << couleur
             << "\n\tCaractere = " << caractere << "\n\tNom = " << nom
             << "\n\tPions restants = " << nbPions << endl;
    }

    int getCouleur() const { return couleur; }

    char getCaractere() const { return caractere; }

    char* getnom() const { return nom; }

    int getNumero() const { return numero; }

    int getNbPions() const { return nbPions; }

    void setNbPions(int nb) { nbPions = nb; }

    void decrementerPion() { if (nbPions > 0) --nbPions; }

    // Destructeur
    ~Joueur() {
        delete[] nom;
    }
};

// Déclaration externe pour une instance "vide"
extern Joueur j_vide;

#endif // JOUEUR_H_INCLUDED
