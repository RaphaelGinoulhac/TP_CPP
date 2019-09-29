// Raphael GINOULHAC
#ifndef matrice_H
#define matrice_H

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class Matrice {
private:
    int m, n;
    double *tab;
    int *compteur;

public:
    //constructeur
    Matrice(int lig, int col);

    //constructeur par copie
    Matrice(const Matrice &A);

    //destructeur
    ~Matrice();

    //affectation
    Matrice& operator=(const Matrice &A);

    //multiplication
    Matrice operator*(const Matrice &B);

    //set
    double &operator()(int i, int j);

    //get
    double operator()(int i, int j) const;

    void affiche();
};


#endif
