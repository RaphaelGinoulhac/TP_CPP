//
// Classes to represent a point in a 2D euclidean space
//

#include "point2d.h"
#include <iostream>
using std::ostream;
using std::cout;

//
// Display 2D point
//
ostream &operator<<(ostream &os, Point_2D const &p) {
    return os << "(" << p.x() << "," << p.y() << ")";
}
ostream &operator<<(ostream &os, Point_2D* const &p) {
    return os << *p;
}

//
// Return the squared euclidean distance between (x1,y1) and (x2,y2)
//
float distance2(float x1, float y1, float x2, float y2) {
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}
//
// Return the euclidean distance between (x1,y1) and (x2,y2)
//
float distance(float x1, float y1, float x2, float y2) {
    return sqrt(distance2(x1, y1, x2, y2));
}
