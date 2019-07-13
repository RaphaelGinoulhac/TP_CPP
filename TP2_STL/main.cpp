#include "eleve.h"
#include <cstdlib>
#include <ctime>

//Raphael GINOULHAC

std::ostream &operator<<(std::ostream &o, const Eleve &e) {
    return o << e.nom << " " << e.note;
}

template<class T>
void print(const vector<T> &V) {
    typename vector<T>::const_iterator it = V.begin();
    for (; it != V.end(); ++it) {
        cout << *it << endl;
    }
}


int main() {
    srand(time(0));
    int compteur = 0;
    int compteur2 = 0;
    int num_eleves = rand() % 10 + 5;
    vector<Eleve> v;
    //v.push_back(Eleve("Raphael", 20));
    //v.push_back(Eleve("Theo", 16));
    // v.push_back(Eleve("Guillaume", 18));
    // v.push_back(Eleve("Louis", 12));

    for (int i = 0; i < num_eleves; i++) {
        v.push_back(Eleve());
    }
    cout << "Nombre d'eleves : " << num_eleves << endl;

    sort(v.begin(), v.end(), CompareNom(&compteur));
    cout << "Tri par nom" << endl;
    print(v);
    cout << "Nombre de comparaisons pour trier par nom : " << compteur << endl;

    sort(v.begin(), v.end(), CompareNote(&compteur2));
    cout << "Tri par note" << endl;
    print(v);
    cout << "Nombre de comparaisons pour trier par note : " << compteur2 << endl;


    return 0;
}
