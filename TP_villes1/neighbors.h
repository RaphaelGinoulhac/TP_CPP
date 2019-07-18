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
template<typename T>
void insert(QuadTree<Point2D<T> > *&qtree, Square s, Point2D<T> p) {
    Quadrant Q = Quadrant(s, p);
    Square S = Q.ssq;
    int next_dir = Q.dir;

    //On atteint une feuille
    if (qtree->son(next_dir) == nullptr || qtree->son(next_dir)->isLeaf()) {
        //Si la case est vide
        if (qtree->son(next_dir) == nullptr) qtree->son(next_dir) = new QuadLeaf<Point2D<T> >(p);
            // Si la case est deja occupee par un point different (si c'est le meme point, on n'effectue pas d'insertion)
        else if (qtree->son(next_dir)->value() != p) {
            Point2D<T> previous_leaf_value = qtree->son(next_dir)->value();
            qtree->son(next_dir) = new QuadNode<Point2D<T>>(nullptr, nullptr, nullptr, nullptr);
            insert(qtree->son(next_dir), S, previous_leaf_value);
            insert(qtree->son(next_dir), S, p);
        }
    } else {
        insert(qtree->son(next_dir), S, p);
    }

}

//
// Add in vector neighbors the points q in quadtree qtree representing
// points in square s at euclidean distance less than r from point p
//
// Set only the nearest point if nearest is true
//
// Return the number of nodes visited
//
template<typename T>
int search(vector<Point2D<T> > &neighbors,
           QuadTree<Point2D<T> > *qtree, Square s,
           Point2D<T> p, float &r, bool nearest = false) {
    int visited = 0;
    for (int d = 0; d < nQuadDir; d++) {
        QuadTree<Point2D<T> > *f = qtree->son(d);
        if (f && f->isLeaf()) {
            visited++;
            if (f->value().dist2(p) <= pow(r, 2)) {
                if (nearest) {
                    r = f->value().dist(p);
                    if (!neighbors.empty()) neighbors.pop_back();
                }
                neighbors.push_back(f->value());
            }
        } else if (f && s.subsquare(d).intersects_disk(p, r)) {
            visited++;
            visited += search(neighbors, f, s.subsquare(d), p, r, nearest);
        }
    }
    return visited;
}

//
// Add in vector neighbors the nearest point of p in the quadtree qtree
// representing the points in square s
//
// Return the number of nodes visited
//
template<typename T>
int search(vector<Point2D<T> > &neighbors,
           QuadTree<Point2D<T> > *qtree, Square s,
           Point2D<T> p) {
    float r = INFINITY;

    return search(neighbors, qtree, s, p, r, true);

}

