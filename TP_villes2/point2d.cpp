#include "point2d.h"

//
// Display 2D point
//
ostream &operator<<(ostream &os, Point2D const &pt) {
    return os << "(" << pt.x() << "," << pt.y() << ")";
}
ostream &operator<<(ostream &os, Point2D* const &p) {
    return os << *p;
}
