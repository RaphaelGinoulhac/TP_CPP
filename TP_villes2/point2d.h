/*
 * A simple class to operate on 2D points
 */

#pragma once

#include <iostream>

using std::ostream;


/*
 * A 2D point given by (x,y) coordinates
 */
class Point2D {
    // Coordinates
    float _x, _y;
public:
    // Create a new 2D point with given coordinates
    Point2D(float x, float y) : _x(x), _y(y) {}

    // Get coordinates
    inline float x() const { return _x; }

    inline float y() const { return _y; }

    //Operator< to get a total order
    bool operator<(const Point2D& b) const {
       return _x < b._x || ((_x==b._x ) && (_y<b._y));
    };
};

//
// Display 2D point
//
ostream &operator<<(ostream &os, Point2D const &pt);

ostream &operator<<(ostream &os, Point2D *const &p);


//Comparison operator for Point2D for the map used in histogram_of_coordinate_repetitions. The order is total
//That way we don't implement operator< directly in Point2D (as another order could be more natural between Point2D)
//struct comparePoint2D {//: binary_function<Point2D,Point2D,bool>{
//    bool operator()(const Point2D &a, const Point2D &b) const {
//        return a.x() < b.x() || ((a.x() == b.x()) && (a.y() < b.y()));
//    }
//};
//
//struct compareTown {//: binary_function<Point2D,Point2D,bool>{
//    bool operator()(const Town &a, const Town &b) const {
//        comparePoint2D compare;
//        return a.name() < b.name() || ((a.name() == b.name()) && (compare(a.point(), b.point())));
//    }
//};