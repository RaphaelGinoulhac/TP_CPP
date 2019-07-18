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


bool Square::intersects_disk(Point_2D p, float r) {
    //distance entre le point p et le centre du carre, pour chaque direction
    float distance_x = fabs(p.x() - (x + w / 2));
    float distance_y = fabs(p.y() - (y + w / 2));

    //1er cas, le point p est trop loin du centre du carre pour qu'une intersection soit possible
    if (distance_x > (w / 2 + r) || distance_y > (w / 2 + r)) return false;

    //2eme cas, le point p est a l'interieur du carre donc il y a bien intersection du disque avec le carre
    if (distance_x <= (w / 2) || distance_y <= (w / 2)) return true;

    //3eme cas, le point p est a l'exterieur du carre, et on verifie qu'il est a une distance inferieure a r du coin
    //pour qu'il y ait intersection
    float distance_corner = pow((distance_x - w / 2), 2) + pow((distance_y - w / 2), 2);

    return (distance_corner <= pow(r, 2));
}