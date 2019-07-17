//
// Created by rginoulhac on 17/07/19.
//

#include "square.h"

Square Square::subsquare(int dir) {
    switch (dir) {
        case 0:
            return Square(x, y + w / 2, w / 2);
        case 1:
            return Square(x + w / 2, y + w / 2, w / 2);
        case 2:
            return Square(x + w / 2, y, w / 2);
        case 3:
            return Square(x, y, w / 2);
        default:
            return Square(x, y, w);
    }
}