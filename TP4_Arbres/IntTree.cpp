#include "IntTree.h"

IntTree::IntTree(int d) {
    data = d;
}

IntTree::~IntTree() {
    for (int i = 0; i < sons.size(); i++) {
        delete sons[i];
    }
}

int IntTree::getData() {
    return data;
}

void IntTree::setData(int d) {
    data = d;
}

int IntTree::nbSons() {
    return sons.size();
}

//Cas d'erreur : pos n'est pas entre 0 et nbSons-1, on veut alors acceder a un element qui n'est pas dans le vecteur
IntTree *IntTree::getSon(int pos) {
    try {
        IntTree *fils = sons.at(pos);
        return fils;
    }
    //Si on a indique une mauvaise position ou bien si le noeud n'a aucun fils, on retourne le noeud lui-meme
    catch (exception const &e) {
        cerr << "Erreur : " << e.what() << ", le fils demande n'existe pas, un arbre avec le noeud 0 est retourne " <<endl;
        return new IntTree(0);
    }

}

//idem
void IntTree::setSon(int pos, IntTree *newSon) {

    if (pos < 0 || nbSons() <= pos)
        throw out_of_range("Mauvaise valeur de pos, newSon n'a pas ete place");
    delete sons[pos];
    sons[pos] = newSon;

}


void IntTree::addAsLastSon(IntTree *newSon) {
    sons.push_back(newSon);
}

//erreur s'il n'y a pas de fils
void IntTree::removeLastSon() {

    if (nbSons() <= 0)
        throw domain_error("Cet arbre n'a pas de fils");
    sons.pop_back();

}


void IntTree::display(string prefix, string indent) {
    cout << prefix << indent << data << endl;
    for (int k = 0; k < nbSons(); k++) {
        sons[k]->display(prefix, indent + indent);
    }
}
