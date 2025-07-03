#include <iostream>
#include <map>
#include <vector>
#include "alignement.h"




bool operator<(const Coord& lhs, const Coord& rhs) {
    if (lhs.col != rhs.col)
        return lhs.col < rhs.col;
    return lhs.lig < rhs.lig;
}

bool operator==(const Coord& lhs, const Coord& rhs) {
    return lhs.col == rhs.col && lhs.lig == rhs.lig;
}


// Table des voisins
const std::map<Coord, std::vector<Coord>> voisins = {
    {{'A','A'}, {{'A','D'}, {'D','A'}}},
    {{'A','D'}, {{'A','A'}, {'A','G'}, {'B','D'}}},
    {{'A','G'}, {{'A','D'}, {'D','G'}}},

    {{'B','B'}, {{'B','D'}, {'D','B'}}},
    {{'B','D'}, {{'B','B'}, {'B','F'}, {'A','D'}, {'C','D'}}},
    {{'B','F'}, {{'B','D'}, {'D','F'}}},

    {{'C','C'}, {{'C','D'}, {'D','C'}}},
    {{'C','D'}, {{'C','C'}, {'C','E'}, {'B','D'}}},
    {{'C','E'}, {{'C','D'}, {'D','E'}}},

    {{'D','A'}, {{'A','A'}, {'D','B'}, {'G','A'}}},
    {{'D','B'}, {{'B','B'}, {'D','A'}, {'D','C'}, {'F','B'}}},
    {{'D','C'}, {{'C','C'}, {'D','B'}, {'E','C'}}},
    {{'D','E'}, {{'C','E'}, {'D','F'}, {'E','E'}}},
    {{'D','F'}, {{'B','F'}, {'D','E'}, {'D','G'}, {'F','F'}}},
    {{'D','G'}, {{'A','G'}, {'D','F'}, {'G','G'}}},

    {{'E','C'}, {{'E','D'}, {'D','C'}}},
    {{'E','D'}, {{'E','C'}, {'E','E'}, {'F','D'}}},
    {{'E','E'}, {{'E','D'}, {'D','E'}}},

    {{'F','B'}, {{'F','D'}, {'D','B'}}},
    {{'F','D'}, {{'F','B'}, {'F','F'}, {'E','D'}, {'G','D'}}},
    {{'F','F'}, {{'F','D'}, {'D','F'}}},

    {{'G','A'}, {{'D','A'}, {'G','D'}}},
    {{'G','D'}, {{'G','A'}, {'G','G'}, {'F','D'}}},
    {{'G','G'}, {{'D','G'}, {'G','D'}}}
};

// Fonction pour vérifier si deux cases sont voisines
bool CasesVoisines(const Coord& c1, const Coord& c2) {
    auto it = voisins.find(c1);
    if (it == voisins.end()) return false;
    const auto& listeVoisins = it->second;
    for (const auto& voisin : listeVoisins) {
        if (voisin == c2) return true;
    }
    return false;
}
