#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

// Node of a tree containing an integer at each node
class IntTree {
    // Node information
    int data;
    // Sequence of sons (empty if none)
    vector<IntTree *> sons;
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
    //* @throws vector::_M_range_check if pos is not a valid position (between 0 and nbSons-1) and returns this
    IntTree *getSon(int pos);

    // Replace the existing son at position pos with newSon (left-most son at position 0)
    //* @throws out_of_range if pos is not a valid position (between 0 and nbSons-1)
    void setSon(int pos, IntTree *newSon);

    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(IntTree *newSon);

    // Remove right-most son of this node
    //* @throws domain_error if the tree doesn't have any son
    void removeLastSon();

    //displays the tree
    void display(string prefix = "", string indent = " ");
};
