//
// Created by rginoulhac on 17/07/19.
//

#include "quadrant.h"

Quadrant::Quadrant(Square s, Point_2D p) {
    if (p.x() < s.x + s.w / 2) {
        if (p.y() < s.y + s.w / 2) {
            dir = 3;
        } else dir = 0;
    } else {
        if (p.y() < s.y + s.w / 2) {
            dir = 2;
        } else dir = 1;
    }
    ssq = s.subsquare(dir);
}