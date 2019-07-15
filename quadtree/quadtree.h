/***************************************************************************
 * Basic datatypes to construct a quadtree
 *
 * Author: Renaud Marlet (c) 2011-2018
 ***************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Compatibility with old C++ compilers
#if __cplusplus < 201103L
#ifndef NULL
#define NULL 0
#endif
#ifndef nullptr
#define nullptr NULL
#endif
#endif

/*--------------------------------------------------------------------------*
 * The quadrant directions
 *--------------------------------------------------------------------------*/

// The 4 quadrant directions
const int NW = 0; // North-West
const int NE = 1; // North-East
const int SE = 2; // South-East
const int SW = 3; // South-West
// The number of directions
const int nQuadDir = 4;

// Forward declarations (so that the class names can be used in QuadTree)
template <typename T> class QuadLeaf; // The type of a QuadTree leaf
template <typename T> class QuadNode; // The type of a QuadTree node

/*--------------------------------------------------------------------------*
 * Abstract class for quadtrees, whose leaves contain a value of type T
 * 
 * Note that this class cannot be instantiated.  Only the QuadLeaf and QuadNode
 * classes can be instantiated.  However, generic methods can be defined
 * at the level of this superclass.
 *--------------------------------------------------------------------------*/
template <typename T>
class QuadTree {
public:
    // Constructors are defined in each subclass

    // Destruct this node or leaf and, recursively, subtrees
    // Note: deletion of quad-dag (quadtree with node sharing) is not supported
    virtual ~QuadTree() {}

    // Tell if this quadtree is a leaf
    virtual bool isLeaf() const = 0; // This makes QuadTree an abstract class

    // Tell if this quadtree is a node
    inline virtual bool isNode() const { return !isLeaf();}

    // Return the number of leaves in this qtree
    virtual int nLeaves() const = 0;

    // Return the number of nodes in this qtree (excluding leaves)
    virtual int nNodes() const = 0;

    // Return the number of (sub)trees in this qtree (nodes and leaves)
    virtual int nTrees() const = 0;

    // Flag to indicate whether leaves should be excluded from deletion
    // when a (recursive) destruction is invoke on a tree
    static bool protect_leaves_from_destruction;

    ///// QuadLeaf methods

    // Return the value of this QuadTree 
    // Throw domain_error if not a QuadLeaf
    virtual const T value() const = 0;

    // Return a reference to the value of this QuadLeaf (for assignments)
    // Throw domain_error if not a QuadLeaf
    virtual T& value() = 0;

    ///// QuadNode methods

    // Return the son of this quadtree in direction d
    // Throw domain_error if not a QuadNode
    virtual QuadTree<T>* const& son(int d) const = 0;

    // Return a reference to the son of this quadtree in direction d
    // Throw domain_error if not a QuadNode
    virtual QuadTree<T>*& son(int d) = 0;

};

// Flag to indicate whether leaves should be excluded from deletion
// when a (recursive) destruction is invoke on a tree -- defaults to false
template <typename T>
bool QuadTree<T>::protect_leaves_from_destruction = false;


/*--------------------------------------------------------------------------*
 * A leaf of a quadtree, containing a value of type T
 *--------------------------------------------------------------------------*/
template <typename T>
class QuadLeaf : public QuadTree<T>
{
    // The value contained in this leaf
    T val;

public:
    // Tell if this quadtree is a leaf
    inline bool isLeaf() const { return true; }

    // Construct a QuadLeaf with the given value
    QuadLeaf(T value) : val(value) {}

    // Return the number of leaves in this qtree
    inline int nLeaves() const { return 1; }

    // Return the number of nodes in this qtree (excluding leaves)
    inline int nNodes() const { return 0; }

    // Return the number of (sub)trees in this qtree (nodes and leaves)
    inline int nTrees() const { return 1; }

    ///// QuadLeaf methods

    // Return the value of this QuadLeaf
    inline const T value() const { return val; }

    // Return a reference to the value of this QuadLeaf (for assignments)
    inline T& value() { return val; }

    ///// QuadNode methods

    // Supposed to return the son of this quadtree in direction d
    // But throw domain_error as not a QuadNode
    inline QuadTree<T>* const& son(int d) const {
	throw new std::domain_error("Not a QuadNode"); }

    // Supposed to return a reference to the son of this quadtree in direction d
    // But throw domain_error as not a QuadNode
    inline QuadTree<T>*& son(int d) {
	throw new std::domain_error("Not a QuadNode"); }

};



/*--------------------------------------------------------------------------*
 * A branching node of a quadtree, whose leaves contain a value of type T
 *--------------------------------------------------------------------------*/
template <typename T>
class QuadNode : public QuadTree<T>
{
    // The sons of this node for the 4 quadrant directions
    QuadTree<T>* sons[nQuadDir];

public:
    // Tell if this quadtree is a leaf
    inline bool isLeaf() const { return false; }

    // Construct a new branching node given an array of 4 quadtrees 
    QuadNode(QuadTree<T>* qtrees[])
    {
	// Assign sons
        for (int i = 0; i < nQuadDir; i++)
	    sons[i] = qtrees[i];
    }

    // Construct a new branching node with empty (null) sons
    QuadNode()
    {
	// Assign sons
        for (int i = 0; i < nQuadDir; i++)
	    sons[i] = nullptr;
    }

    // Construct a new branching node given 4 sons
    QuadNode(QuadTree<T>* son0,
	     QuadTree<T>* son1,
	     QuadTree<T>* son2,
	     QuadTree<T>* son3)
    {
	// Assign sons
	sons[0] = son0;
	sons[1] = son1;
	sons[2] = son2;
	sons[3] = son3;
    }

    // Destruct this QuadNode and, recursively, subtrees
    // Note: deletion of quad-dag (quadtree with node sharing) is not supported
    ~QuadNode()
    {
	// For each direction
        for (int i = 0; i < nQuadDir; i++)
	    // Delete the corresponding son
	    if (sons[i] && !(sons[i]->isLeaf() && QuadTree<T>::protect_leaves_from_destruction))
		delete sons[i];
    }

    // Return the number of leaves in this qtree
    inline int nLeaves() const
    {
      int n = 0;
      for (int i = 0; i < nQuadDir; i++)
	if (sons[i] != nullptr)
	  n += sons[i]->nLeaves();
      return n;
    }

    // Return the number of nodes in this qtree (excluding leaves)
    inline int nNodes() const
    {
      int n = 1;
      for (int i = 0; i < nQuadDir; i++)
	if (sons[i] != nullptr)
	  n += sons[i]->nNodes();
      return n;
    }

    // Return the number of (sub)trees in this qtree (nodes and leaves)
    inline int nTrees() const
    {
      int n = 1;
      for (int i = 0; i < nQuadDir; i++)
	if (sons[i] != nullptr)
	  n += sons[i]->nTrees();
      return n;
    }

    ///// QuadLeaf methods

    // Supposed to return the value of this QuadTree 
    // But throw a domain_error as it is not a QuadLeaf
    inline const T value() const { throw new std::domain_error("Not a QuadLeaf"); }

    // Supposed to return a reference to the value of this QuadTree
    // But throw a domain_error as it is not a QuadLeaf
    inline T& value() { throw new std::domain_error("Not a QuadLeaf"); }

    ///// QuadNode methods

    // Return the son of this quadtree in direction d 
    inline QuadTree<T>* const& son(int d) const
    {
	// Make sure the direction makes sense
	if(!(0 <= d && d < nQuadDir)) {
	    std::ostringstream oss; oss << d;
	    throw new std::out_of_range("Not a valid direction: "+oss.str());
	}
	// Yield son
	return sons[d];
    }

    // Return a reference to the son of this quadtree in direction d
    inline QuadTree<T>*& son(int d)
    {
	// Make sure the direction makes sense */
	if (!(0 <= d && d < nQuadDir)) {
	    std::ostringstream oss; oss << d;
	    throw new std::out_of_range("Not a valid direction: "+oss.str());
	}
	// Return son reference
	return sons[d];
    }
};


// For debugging

/*
 * Display a quadtree on standard output
 */
template <typename T>
void display(QuadTree<T>* qt, std::string prefix = "", void(*prt)(T) = nullptr)
{
    // If tree is not null
    if (qt != nullptr)
    {
	// If tree is leaf
	if (qt->isLeaf()) {
	    // Output its value
	    std::cout << prefix << " = ";
	    if (prt)
		(*prt)(qt->value());
	    else
		std::cout << qt->value();
	    std::cout << std::endl;
	}
	// Otherwise if tree is a branch node
	else
	    // For each direction
	    for (int d = 0; d < nQuadDir; d++) {
		// Get direction name
		std::string dirName[] = {"NW", "NE", "SE", "SW"};
		// Dump son in this direction
		display(qt->son(d),prefix+"-"+dirName[d]);
	    }
    }
    // Otherwise, if tree is null pointer
    else
	// Output empty tree
	std::cout << prefix << " ." << std::endl;
}
