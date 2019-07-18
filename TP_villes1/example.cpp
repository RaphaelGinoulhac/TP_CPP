#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cmath>
#include <limits>

using namespace std;

#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";

#include "town.h"
#include "neighbors.h"


void testing() {


    //Test insert
    QuadTree<Point2D<float> > *ql;
    ql = new QuadNode<Point2D<float> >(0, 0, 0, 0);
    Square S = Square(0, 0, 10000);
    //insert(ql, S, Point2D<float>(town1.x(), town1.y(), 3.5));
    //insert(ql, S, Point2D<float>(town2.x(), town2.y(), 4.5));
    insert(ql, S, Point2D<float>(500, 40, 4.5));
    insert(ql, S, Point2D<float>(9500, 9700, 5.5));
    insert(ql, S, Point2D<float>(9400, 9700, 6.5));
    insert(ql, S, Point2D<float>(1000, 60, 7.5));
    insert(ql, S, Point2D<float>(1000, 60, 8.5));
    cout << "Test insert" << endl;
    display(ql);

    //Test intersects_disk
    cout << "Test intersects disk" << endl;
    cout << S.intersects_disk(Point_2D(100, 100), 100) << endl;
    cout << S.intersects_disk(Point_2D(10050, 10050), 100) << endl;
    cout << S.intersects_disk(Point_2D(10070, 700), 100) << endl;
    cout << S.intersects_disk(Point_2D(20000, 100), 100) << endl;

    //Test search
    cout << "Test search" << endl;
    vector<Point2D<float> > neighbors_test;
    float r = 10000;
    cout << search(neighbors_test, ql, S, Point2D<float>(1000, 40, 9.5), r, false) << " nodes visited" << endl;

    for (int i = 0; i < neighbors_test.size(); i++) {
        cout << neighbors_test[i].info() << endl;
    }

    //Test plus proche voisin
    cout << "Test nearest neighbor" << endl;
    neighbors_test.clear();
    cout << search(neighbors_test, ql, S, Point2D<float>(1000, 40, 9.5)) << " nodes visited" << endl;
    for (int i = 0; i < neighbors_test.size(); i++) {
        cout << neighbors_test[i].info() << endl;
    }

    delete ql;
}

/*
 * Example of use of "town.h" and "villes.txt":
 * - read file of metropolitan French towns with coordinates
 * - display reading time and number of towns read
 * - ask for town name
 * - lookup for town coordinates with this name and display them
 * - display distance between two random towns
 */
int main() {
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Prepare limits
    float xmin = std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::min();
    float ymax = std::numeric_limits<float>::min();
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t t1 = clock();
    int nb_towns = Town::read_file(townFile, towns, xmin, ymin, xmax, ymax);
    clock_t t2 = clock();
    // Say how many towns have been read
    if (nb_towns < 0) {
        cout << "No town found" << endl;
        return 1;
    }
    cout << "File read in " << ((float) (t2 - t1) / CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: " << nb_towns << endl;
    cout << "Bounding box: (" << xmin << "," << ymin << ")-("
         << xmax << "," << ymax << ")" << endl;

    /////
    ///// Operate on quadtree
    /////
    // Ask for a town to look for
    string name;
    cout << "What town are you interested in ? ";
    // Read town name, including spaces
    getline(cin, name); // Read whole line including spaces 
    // Note that "cin >> name;" would read only the first word, stopping
    // at the first blank (space or tab)
    //
    // Look for towns with this name
    vector<Town> ntowns = Town::towns_with_name(towns, name);
    // Say how many towns were found with this name
    cout << "Number of towns with this name: " << ntowns.size() << endl;
    // Display their coordinates
    for (vector<Town>::iterator it_ntown = ntowns.begin();
         it_ntown != ntowns.end(); ++it_ntown)
        cout << "  (lat=" << it_ntown->lat()
             << ",lon=" << it_ntown->lon() << ")" << endl;

    // Make sure rand() draws different random numbers each time the
    // program is run
    srand(clock());
    // Draw two random towns
    Town town1 = towns[rand() % towns.size()];
    Town town2 = towns[rand() % towns.size()];
    Town town3 = towns[rand() % towns.size()];
    // Compute distance
    cout << "By the way, did you know that " << town1.name()
         << " was " << town1.dist(town2)
         << " km away from " << town2.name() << " ?" << endl;

    cout << town1.x() << "  " << town1.y() << endl;

    /////
    ///// Debut du TP
    /////

    cout << "Constructing a QuadTree containing the towns of France : " << endl;
    QuadTree<Point2D<Town> > *q_tree;
    q_tree = new QuadNode<Point2D<Town> >(0, 0, 0, 0);
    //Plus petit carre contenant la France
    Square S_france = Square(xmin, ymin, max(xmax - xmin, ymax - ymin));
    //Insertion de toutes les villes
    for (int i = 0; i < towns.size(); i++) {
        insert(q_tree, S_france, Point2D<Town>(towns[i].x(), towns[i].y(), towns[i]));
    }

    //Taille du QuadTree
    cout << "Number of leaves : " << q_tree->nLeaves() << endl;
    cout << "Number of nodes : " << q_tree->nNodes() << endl;
    cout << "Number of trees : " << q_tree->nTrees() << endl;

    //Ville la plus proche de Ponts
    vector<Point2D<Town> > neighbors;
    float lat_ponts = 48.702080;
    float lon_ponts = -1.345950;
    pair<float, float> x_y_ponts = geoToLambert93(lat_ponts, lon_ponts);

    int nodes_visited = search(neighbors, q_tree, S_france,
                               Point2D<Town>(x_y_ponts.first, x_y_ponts.second, Town("", lat_ponts, lon_ponts)));

    cout << "Closest town to Ponts : " << neighbors[0].info().name() << endl;
    cout << nodes_visited << " nodes visited during this nearest neighbor search" << endl;


    delete q_tree;

    return 0;
}