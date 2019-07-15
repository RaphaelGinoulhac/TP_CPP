/*
 * A class to represent a point in a 2D euclidean space, with some
 * information attached
 */

#pragma once

#include <cmath>
using std::sqrt;
#include <iostream>
using std::ostream;


// Return the squared euclidean distance between (x1,y1) and (x2,y2)
float distance2(float x1, float y1, float x2, float y2);

// Return the euclidean distance between (x1,y1) and (x2,y2)
float distance(float x1, float y1, float x2, float y2);

//
// A class representing a 2D point in |R^2, defined by its coordinates
//
// The coordinates cannot be modified after the point is created
//
class Point_2D 
{
protected:
    // Coordinates
    float _x, _y;
public:
    // Create new 2D point with given coordinates
    Point_2D(float x, float y) : _x(x), _y(y) {}
    // Get coordinates
    inline float x() const { return _x; }
    inline float y() const { return _y; }
    // Equality test
    bool operator==(const Point_2D &p) const { return _x==p._x && _y==p._y; }
    bool operator!=(const Point_2D &p) const { return _x!=p._x || _y!=p._y; }
    // Squared euclidean distance between this point and another one
    float dist2(const Point_2D &p) const { return distance2(_x,_y,p._x,p._y); }
    // Euclidean distance between this point and another one
    float dist(const Point_2D &p) const { return sqrt(dist2(p)); }
};

// Display 2D point
ostream &operator<<(ostream &os, Point_2D const &p);
ostream &operator<<(ostream &os, Point_2D* const &p);


//
// Class to represent a 2D Point in |R^2, with attached information of
// arbitrary type
//
// The coordinates cannot be modified after the point is created, but the
// information can
//
template <typename T>
class Point2D : public Point_2D
{
    // Attached information 
    T _info;
public:
    Point2D() {}
    Point2D(float x, float y) : Point_2D(x,y) {}
    // Create new 2D point with given coordinates and information
    Point2D(float x, float y, T info) : Point_2D(x,y), _info(info) {}
    // Get information
    // It can be used both to get or set the value: p.info() = newValue;
    inline T& info() { return _info; }
};

