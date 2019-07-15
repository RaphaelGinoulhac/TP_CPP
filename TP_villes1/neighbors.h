#pragma once

#include <vector>
using std::vector;
#include <cmath>

#include "point2d.h"
#include "square.h"
#include "quadrant.h"
#include "../quadtree/quadtree.h"

//
// Add point p in the quadtree representing the points in square s
//
template <typename T>
void insert(QuadTree< Point2D<T> >* &qtree, Square s, Point2D<T> p);

//
// Add in vector neighbors the points q in quadtree qtree representing
// points in square s at euclidean distance less than r from point p
//
// Set only the nearest point if nearest is true
//
// Return the number of nodes visited
//
template <typename T>
int search(vector< Point2D<T> > &neighbors,
	   QuadTree< Point2D<T> >* qtree, Square s,
	   Point2D<T> p, float& r, bool nearest = false);

//
// Add in vector neighbors the nearest point of p in the quadtree qtree
// representing the points in square s
//
// Return the number of nodes visited
//
template <typename T>
int search(vector< Point2D<T> > &neighbors,
	   QuadTree< Point2D<T> >* qtree, Square s,
	   Point2D<T> p);

