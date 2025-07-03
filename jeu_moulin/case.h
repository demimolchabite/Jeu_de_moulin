#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <iostream>
#include "joueur.h"

using namespace std;

class Case {
public:
    enum Etat {
        Protege,
        NonProtege
    };

private:
    char horizontal;
    char vertical;
    Joueur joueur;
    Etat etat;

public:
    Case() : horizontal(' '), vertical(' '), joueur(j_vide), etat(NonProtege) {}

    Case(char hor, char vert, Joueur j = j_vide) : horizontal(hor), vertical(vert), joueur(j), etat(NonProtege) {}

    Case& operator=(const Case &C) {
        horizontal = C.horizontal;
        vertical = C.vertical;
        joueur = C.joueur;
        etat = C.etat;
        return *this;
    }

    bool operator==(const Case& C) const {
        return (horizontal == C.horizontal &&
                vertical == C.vertical &&
                joueur == C.joueur &&
                etat == C.etat);
    }

    bool Case_Vide() const {
        return (joueur == j_vide);
    }

    void afficher_Case() const {
        cout << "\tAbscisse = " << horizontal << "\n\tOrdonnee = " << vertical << endl;
        joueur.afficher_info();
        cout << "\tEtat = " << (etat == Protege ? "Protege" : "NonProtege") << endl;
    }

    void setJoueur(Joueur j) {
        joueur = j;
    }

    Joueur getJoueur() const {
        return joueur;
    }

    char gethorizontal() const {
        return horizontal;
    }

    char getvertical() const {
        return vertical;
    }

    void sethorizontal(char h) {
        horizontal = h;
    }

    void setvertical(char v) {
        vertical = v;
    }

    void setEtat(Etat e) {
        etat = e;
    }

    Etat getEtat() const {
        return etat;
    }

    ~Case() {}
};

#endif // CASE_H_INCLUDED
