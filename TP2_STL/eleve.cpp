#include "eleve.h"


Eleve::Eleve() {
    note = rand() % 21;
    int longueur_nom = rand() % 5 + 3;
    nom = string(longueur_nom, 'a');
    for (int i = 0; i < longueur_nom; i++) {
        nom[i] = 'a' + rand() % 26;
    }
}

Eleve::Eleve(string Nom, int Note) {
    nom = Nom;
    note = Note;
}

CompareNom::CompareNom(int *compteur) {
    this->ptr = compteur;
}

CompareNote::CompareNote(int *compteur) {
    this->ptr = compteur;
}
