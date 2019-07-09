#include "eleve.h"

Eleve::Eleve(string Nom, int Note){
    nom=Nom;
    note=Note;
}

CompareNom::CompareNom(int* compteur) {
    this->ptr = compteur;
}

CompareNote::CompareNote(int* compteur) {
    this->ptr = compteur;
}
