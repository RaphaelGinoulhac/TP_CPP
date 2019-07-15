/*
 * A simple class to operate on squares
 */

#pragma once

#include "point2d.h"
#include "../quadtree/quadtree.h"

//
// A square defined by bottom-left coordinates (x,y) and side size w,
// i.e., with vertex points (x,y), (x+w,y), (x+w,y+w), (x,y+w)
//
class Square {
public:
    // Bottom-left coordinates of the square
    float x, y;
    // Size of the square side
    float w;
    // Construct default square
    Square() {};
    // Construct a square from bottom-left coordinates (x,y) and a side size w
    Square(float _x, float _y, float _w) : x(_x), y(_y), w(_w) {};
    // Construct a new square which is a sub-square of this square, in
    // quadrant direction dir where dir is as defined in quadtree.h
    Square subsquare(int dir);
    // Return true iff this square intersects with disk at p with radius r
    bool intersects_disk(Point_2D p, float r);
};

