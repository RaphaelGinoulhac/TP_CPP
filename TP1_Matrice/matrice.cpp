#include "matrice.h"

Matrice::Matrice(int lig, int col) {
    m = lig;
    n = col;
    tab = new double[lig * col];

    compteur = new int;
    *compteur = 1;
    cout << "Construction" << endl;
}

Matrice::Matrice(const Matrice &A) {
    m = A.m;
    n = A.n;
    tab = A.tab; //shallow copy
    compteur = A.compteur;
    ++*compteur;
    cout << "Construction par copie" << endl;
}

void Matrice::operator=(const Matrice &A) {
    delete[] tab;
    m = A.m;
    n = A.n;
    tab = new double[m * n];
    for (int i = 0; i < m * n; i++) {
        tab[i] = A.tab[i];
    }
}

Matrice::~Matrice() {
    --*compteur;
    if (*compteur == 0) {
        delete[] tab;
        delete compteur;
        cout << "Destruction" << endl;
    }
}

Matrice Matrice::operator*(const Matrice &B) {
    assert(n == B.m);
    Matrice C(m, B.n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < B.n; j++) {
            C.tab[i + C.m * j] = 0;
            for (int k = 0; k < n; k++) {
                C.tab[i + C.m * j] += tab[i + m * k] * B.tab[k + B.m * j];
            }
        }
    }
    return C;
}

void Matrice::affiche() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << tab[i + m * j] << " ";
        }
        cout << endl;
    }
}

double &Matrice::operator()(int i, int j) {
    assert(0 <= i && i < m && 0 <= j && j < n);
    return tab[i + m * j];
}

double Matrice::operator()(int i, int j) const {
    assert(0 <= i && i < m && 0 <= j && j < n);
    return tab[i + m * j];
}
