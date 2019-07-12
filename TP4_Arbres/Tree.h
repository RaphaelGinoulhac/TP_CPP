//
// Created by rginoulhac on 11/07/19.
//

#ifndef TP4_ARBRES_TREE_H
#define TP4_ARBRES_TREE_H

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stdexcept>

using namespace std;


template<typename T>

class Tree {
    // Node information
    T data;
    // Sequence of sons (empty if none)
    vector<Tree *> sons;
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
    //* @throws vector::_M_range_check if pos is not a valid position (between 0 and nbSons-1) and returns a tree with the same data as the father
    Tree *getSon(int pos);

    // Replace the existing son at position pos with newSon (left-most son at position 0)
    //* @throws out_of_range if pos is not a valid position (between 0 and nbSons-1)
    void setSon(int pos, Tree *newSon);

    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(Tree *newSon);

    // Remove right-most son of this node
    //* @throws domain_error if the tree doesn't have any son
    void removeLastSon();

    //displays the tree
    void display(string prefix = "* ", string indent = " ");

    //Insert extra son at position pos, if pos exists
    //* @throws out_of_range if pos is not a valid position (between 0 and nbSons-1)
    void addSon(int pos, Tree *son);

    //Remove son at position pos, thus reducing nbSons
    //* @throws out_of_range if pos is not a valid position (between 0 and nbSons-1)
    void removeSon(int pos);

    //Parcours d'arbre
    void breadthFirst();

    void depthFirstDescending();

    void depthFirstAscending();

    //Profondeurs max et min
    int maxDepth();

    int minDepth();
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
        Tree *fils = sons.at(pos);
        return fils;
    }
        //Si on a indique une mauvaise position ou bien si le noeud n'a aucun fils, on retourne le noeud lui-meme
    catch (exception const &e) {
        cerr << "Erreur : " << e.what() << ", le fils demande n'existe pas,  un arbre avec le meme noeud que le pere est retourne " <<endl;
        //On ne peut pas renvoyer un Tree(0) comme avec IntTree, on renvoit donc un Tree contenant data
        return new Tree(data);
    }
}


template<typename T>

void Tree<T>::setSon(int pos, Tree<T> *newSon) {

    if (pos < 0 || nbSons() <= pos)
        throw out_of_range("Mauvaise valeur de pos, newSon n'a pas ete place");
    delete sons[pos];
    sons[pos] = newSon;

}

// Add newSon as supplementary right-most son of this node
template<typename T>

void Tree<T>::addAsLastSon(Tree<T> *newSon) {
    sons.push_back(newSon);
}

// Remove right-most son of this node
template<typename T>

void Tree<T>::removeLastSon() {

    if (nbSons() <= 0)
        throw domain_error("Cet arbre n'a pas de fils");
    sons.pop_back();

}

template<typename T>

void Tree<T>::display(string prefix, string indent) {
    cout << prefix << indent << data << endl;
    for (int k = 0; k < nbSons(); k++) {
        sons[k]->display(prefix, indent + indent);
    }
}


template<typename T>
void Tree<T>::addSon(int pos, Tree *son) {

    if (pos < 0 || nbSons() <= pos)
        throw out_of_range("Mauvaise valeur de pos, le fils n'a pas ete ajoute");
    sons.insert(sons.begin() + pos, son);

}


template<typename T>
void Tree<T>::removeSon(int pos) {

    if (pos < 0 || nbSons() <= pos)
        throw out_of_range("Mauvaise valeur de pos, aucun fils n'a ete supprime");
    sons.erase(sons.begin() + pos);

}

template<typename T>
void Tree<T>::breadthFirst() {
    queue<Tree *> q;
    q.push(this);

    while (!q.empty()) {
        Tree *next = q.front();
        cout << next->data << endl;
        for (int i = 0; i < next->nbSons(); i++) {
            q.push(next->getSon(i));
        }
        q.pop();
    }
}

template<typename T>
void Tree<T>::depthFirstDescending() {
    cout << data << endl;
    for (int i = 0; i < sons.size(); i++) {
        sons[i]->depthFirstDescending();
    }
}

template<typename T>
void Tree<T>::depthFirstAscending() {
    for (int i = 0; i < sons.size(); i++) {
        sons[i]->depthFirstAscending();
    }
    cout << data << endl;
}

template<typename T>
int Tree<T>::maxDepth() {
    int maxi = 0;

    for (int i = 0; i < sons.size(); i++)
        maxi = max(maxi, sons[i]->maxDepth());

    return maxi + 1;

}

template<typename T>
int Tree<T>::minDepth() {
    queue<Tree *> q_tree;
    queue<int> q_count;

    q_tree.push(this);
    q_count.push(1);

    Tree *current;
    int count;

    while (!q_tree.empty()) {
        current = q_tree.front();
        count = q_count.front();

        if (current->nbSons() == 0) {
            return count;
        }

        for (int i = 0; i < current->nbSons(); i++) {
            q_tree.push(current->getSon(i));
            q_count.push(count + 1);
        }
        q_tree.pop();
        q_count.pop();
    }
}


#endif //TP4_ARBRES_TREE_H
