#include "IntTree.h"

IntTree::IntTree(int d){
    data=d;
}

IntTree::~IntTree(){
    sons.clear();
}

int IntTree::getData(){
    return data;
}

void IntTree::setData(int d){
    data=d;
}

int IntTree::nbSons(){
    return sons.size();
}

//Cas d'erreur : pos n'est pas entre 0 et nbSons-1, on veut alors acceder a un element qui n'est pas dans le vecteur
IntTree* IntTree::getSon(int pos){
    try {
        if (pos<0 || nbSons()<=pos)
            throw "Mauvaise valeur de pos";
        return sons[pos];
    }
    catch (char* exn){
        cout << exn;
    }
}

//idem
void IntTree::setSon(int pos,IntTree *newSon){
    try{
        if (pos<0 || nbSons()<=pos)
            throw "Mauvaise valeur de pos";
        delete sons[pos];
        sons[pos]=newSon;
        }
    catch (char* exn){
        cout << exn;
    }
}


void IntTree::addAsLastSon(IntTree *newSon){
    sons.push_back(newSon);
}

//erreur s'il n'y a pas de fils
void IntTree::removeLastSon(){
    try{
        if (nbSons()<=0)
            throw "Cet arbre n'a pas de fils";
        sons.pop_back();
        }
    catch (char* exn){
        cout << exn;
    }
}


void IntTree::display(string prefix, string indent){
    cout << prefix << indent << data << endl;
    for (int k=0;k<nbSons();k++){
        sons[k]->display(prefix,indent+indent);
    }
}
