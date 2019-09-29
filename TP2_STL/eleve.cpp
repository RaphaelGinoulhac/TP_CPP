#include "eleve.h"


Eleve::Eleve() {
    //Note entre 0 et 20
    note = rand() % 21;
    //Le nom est constitué d'une lettre majuscule suivi de 1 à 10 lettres minuscules
    //nombre de lettres minuscules
    int longueur_nom = rand() % 10 + 1;
    nom = string(longueur_nom + 1, 'a');
    nom[0] = 'A' + rand() % 26;
    for (int i = 0; i < longueur_nom; i++) {
        nom[i + 1] = 'a' + rand() % 26;
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
