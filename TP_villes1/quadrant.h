/*
 * A simple class to operate on quadrants
 */

#pragma once

#include "point2d.h"
#include "square.h"
#include "../quadtree/quadtree.h"

//
// A quadrant at direction dir, corresponding to a sub-square of some
// larger square
//
class Quadrant {
public:
    // Direction of the quadrant, as defined in quadtree.h
    int dir;
    // Corresponding sub-square
    Square ssq;
public:
    // Construct the quadrant of point p in square s, i.e., the
    // quadrant direction 'dir' in which p can be found in s, as well
    // as the corresponding sub-square 'ssq' of s
    Quadrant(Square s, Point_2D p);
};
