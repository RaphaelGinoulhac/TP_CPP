#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Node of a tree containing an integer at each node
class IntTree {
    // Node information
    int data;
    // Sequence of sons (empty if none)
    std::vector<IntTree*> sons;
public:
    // Create a node with given information
    IntTree(int d);
    // Destruct a node and all its descendants
    ~IntTree();
    // Return information of this node
    int getData();
    // Set information of this node
    void setData(int d);
    // Return the number of sons of this node
    int nbSons();
    // Return the son at position pos, if any (considering left-most son is at position 0)
    IntTree* getSon(int pos);
    // Replace the exisiting son at position pos with newSon (left-most son at position 0) 
    void setSon(int pos, IntTree* newSon);
    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(IntTree* newSon);
    // Remove right-most son of this node
    void removeLastSon();
    //displays the tree
    void display(string prefix="",string indent=" ");
};

template<typename T>
class Tree {
    // Node information
    T data;
    // Sequence of sons (empty if none)
    std::vector<Tree*> sons;
public:
    // Create a node with given information
    Tree(T d);
    // Destruct a node and all its descendants
    ~Tree();
    // Return information of this node
    int getData();
    // Set information of this node
    void setData(T d);
    // Return the number of sons of this node
    int nbSons();
    // Return the son at position pos, if any (considering left-most son is at position 0)
    Tree* getSon(int pos);
    // Replace the exisiting son at position pos with newSon (left-most son at position 0)
    void setSon(int pos, Tree* newSon);
    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(Tree* newSon);
    // Remove right-most son of this node
    void removeLastSon();
    //displays the tree
    void display(string prefix="",string indent=" ");
    //Insert extra son at position pos, if pos exists
    //void addSon(int pos, Tree<T>* son){
   //     vector<Tree*>::iterator it;
   //     it=sons.begin();
  //      sons.insert(it+pos,son);
   // }
    //Remove son at position pos, thus reducing nbSons
   // void removeSon(int pos){
   //     vector<Tree*>::iterator it;
   //     it=sons.begin();
   //     sons.erase(it+pos);
   // }
};
