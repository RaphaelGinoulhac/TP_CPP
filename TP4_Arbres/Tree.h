//
// Created by rginoulhac on 11/07/19.
//

#ifndef TP4_ARBRES_TREE_H
#define TP4_ARBRES_TREE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


template<typename T>

class Tree {
    // Node information
    T data;
    // Sequence of sons (empty if none)
    std::vector<Tree *> sons;
public:
    // Create a node with given information
    Tree(T d);

    // Destruct a node and all its descendants
    ~Tree();

    // Return information of this node
    T getData();

    // Set information of this node
    void setData(T d);

    // Return the number of sons of this node
    int nbSons();

    // Return the son at position pos, if any (considering left-most son is at position 0)
    Tree *getSon(int pos);

    // Replace the existing son at position pos with newSon (left-most son at position 0)
    void setSon(int pos, Tree *newSon);

    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(Tree *newSon);

    // Remove right-most son of this node
    void removeLastSon();

    //displays the tree
    void display(string prefix = "", string indent = " ");

    //Insert extra son at position pos, if pos exists
    void addSon(int pos, Tree<T> *son);

    //Remove son at position pos, thus reducing nbSons
    void removeSon(int pos);
};


template<typename T>


Tree<T>::Tree(T d) {
    data = d;
}

template<typename T>

Tree<T>::~Tree() {
    for (int i = 0; i < sons.size(); i++) {
        delete sons[i];
    }
}

template<typename T>

T Tree<T>::getData() {
    return data;
}

template<typename T>

void Tree<T>::setData(T d) {
    data = d;
}


template<typename T>

int Tree<T>::nbSons() {
    return sons.size();
}

template<typename T>

Tree<T> *Tree<T>::getSon(int pos) {
    try {
        if (pos < 0 || nbSons() <= pos)
            throw string("Mauvaise valeur de pos");
        return sons[pos];
    }
    catch (string const &chaine) {
        cerr << chaine << endl;
    }
}


template<typename T>

void Tree<T>::setSon(int pos, Tree<T> *newSon) {
    try {
        if (pos < 0 || nbSons() <= pos)
            throw string("Mauvaise valeur de pos");
        delete sons[pos];
        sons[pos] = newSon;
    }
    catch (string const &chaine) {
        cerr << chaine << endl;
    }
}

// Add newSon as supplementary right-most son of this node
template<typename T>

void Tree<T>::addAsLastSon(Tree<T> *newSon) {
    sons.push_back(newSon);
}

// Remove right-most son of this node
template<typename T>

void Tree<T>::removeLastSon() {
    try {
        if (nbSons() <= 0)
            throw string("Cet arbre n'a pas de fils");
        sons.pop_back();
    }
    catch (string const &chaine) {
        cerr << chaine << endl;
    }
}

template<typename T>

void Tree<T>::display(string prefix, string indent) {
    cout << prefix << indent << data << endl;
    for (int k = 0; k < nbSons(); k++) {
        sons[k]->display(prefix, indent + indent);
    }
}


template<typename T>
void Tree<T>::addSon(int pos, Tree<T> *son) {
    try {
        if (pos < 0 || nbSons() <= pos)
            throw string("Mauvaise valeur de pos");
        sons.insert(sons.begin() + pos, son);
    }
    catch (string const &chaine) {
        cerr << chaine << endl;
    }
}


template<typename T>
void Tree<T>::removeSon(int pos) {
    try {
        if (pos < 0 || nbSons() <= pos)
            throw string("Mauvaise valeur de pos");
        sons.erase(sons.begin() + pos);
    }
    catch (string const &chaine) {
        cerr << chaine << endl;
    }
}

#endif //TP4_ARBRES_TREE_H
