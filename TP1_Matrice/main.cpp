#include "matrice.h"
#include <cstdlib>
#include <ctime>


//Raphael GINOULHAC
//Le main comprend des tests simples montrant que la multiplication, l'accès aux éléments et la shallow copy fonctionnent bien



//coefficients aléatoires entre 0 et 4 pour simplifier
Matrice matrice_aleatoire(int m, int n) {
    Matrice M(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            M(i, j) = rand() % 5;
        }
    }
    return M;
}


int main() {
    srand(time(0));
    cout << "On va generer et multiplier 2 matrices aleatoires, de taille 2x3 et 3x2 (taille qu'on pourrait changer)" << endl;
    Matrice M = matrice_aleatoire(2, 3);
    Matrice N = matrice_aleatoire(3, 2);
    Matrice O = M * N;
    Matrice P(O);
    cout << "Affichage de M" << endl;
    M.affiche();
    cout << "Affichage de N" << endl;
    N.affiche();
    cout << "Affichage de O=M*N" << endl;
    O.affiche();
    cout << "Affichage de P, qui est une shallow copy de O" << endl;
    P.affiche();

    O(0, 1) = 99; //on modifie O
    cout << "Affichage de O modifiee" << endl;
    O.affiche();
    cout << "Affichage de P, qui est une shallow copy de O (on voit que le meme coefficient a ete modifie)" << endl;
    P.affiche();


    return 0;
}
