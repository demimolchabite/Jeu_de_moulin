#include  <iostream>
#include <cstring>
#include <string>

using namespace std;

void afficherBanniere() {
    cout << "\n";
    cout << "\t\t\t\t\t*********************************************\n";
    cout << "\t\t\t\t\t*                                           *\n";
    cout << "\t\t\t\t\t*          BIENVENUE SUR LE JEU !           *\n";
    cout << "\t\t\t\t\t*                                           *\n";
    cout << "\t\t\t\t\t*********************************************\n\n";
}


string couleurANSI(int couleur) {
    switch (couleur) {
        case 1: return "\033[31m"; // rouge
        case 2: return "\033[32m"; // vert
        case 3: return "\033[33m"; // jaune
        case 4: return "\033[34m"; // bleu
        case 5: return "\033[35m"; // magenta
        case 6: return "\033[36m"; // cyan
        default: return "\033[0m";  // reset / couleur normale
    }
}
