// Raphael GINOULHAC
#ifndef eleve_H
#define eleve_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Eleve {
public:
    string nom;
    int note;

    //constructeur
    Eleve(string Nom, int Note);

};

class CompareNom {
public:
    int *ptr;

    CompareNom(int *compteur);

    bool operator()(Eleve a, Eleve b) const {
        (*ptr)++;
        return a.nom < b.nom;
    }
};

class CompareNote {
public:
    int *ptr;

    CompareNote(int *compteur);

    bool operator()(Eleve a, Eleve b) const {
        (*ptr)++;
        return a.note > b.note;
    }
};

#endif
