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


//Toutes les "validations" des questions 2-4 sont regroupees dans cette fonction
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


//Question 8
pair<float, float>
nearest_neighbor_time(const vector<Town> &towns, QuadTree<Point2D<Town> > *q_tree, Square s, int num_trials = 100) {
    float time1 = 0, time2 = 0;
    vector<Point2D<Town> > neighbors;

    for (int j = 0; j < num_trials; j++) {
        //Recherche du plus proche voisin dans le QuadTree
        Town town = towns[rand() % towns.size()];

        clock_t t1 = clock();
        search(neighbors, q_tree, s, Point2D<Town>(town.x(), town.y(), town));
        clock_t t2 = clock();
        time1 += ((float) (t2 - t1) / CLOCKS_PER_SEC);
        neighbors.clear();

        //Recherche du plus proche voisin dans un vecteur
        float min_distance = INFINITY, current_distance;
        t1 = clock();
        for (int i = 0; i < towns.size(); i++) {
            if (towns[i] != town) {
                current_distance = distance(towns[i].x(), towns[i].y(), town.x(), town.y());
                if (current_distance < min_distance) min_distance = current_distance;
            }
        }
        t2 = clock();
        time2 += ((float) (t2 - t1) / CLOCKS_PER_SEC);
    }
    return make_pair(time1 / num_trials, time2 / num_trials);

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
    t1 = clock();
    //Insertion de toutes les villes
    for (int i = 0; i < towns.size(); i++) {
        insert(q_tree, S_france, Point2D<Town>(towns[i].x(), towns[i].y(), towns[i]));
    }
    t2 = clock();
    float time_construct_quad = ((float) (t2 - t1) / CLOCKS_PER_SEC);
    cout << "QuadTree constructed in " << time_construct_quad << " s" << endl;

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
                               Point2D<Town>(x_y_ponts.first, x_y_ponts.second, Town("Ponts", lat_ponts, lon_ponts)));

    cout << "Closest town to Ponts : " << neighbors[0].info().name() << ", distance : "
         << distance(x_y_ponts.first, x_y_ponts.second, neighbors[0].info().x(), neighbors[0].info().y()) << endl;
    cout << nodes_visited << " nodes visited during this nearest neighbor search" << endl;


    //Pour un parcours lineaire du vecteur de villes, il faut visiter chaque ville une fois,
    // donc on a 35.181 visites (car il n'y a pas d'ordre particulier dans le vecteur)

    pair<float, float> times = nearest_neighbor_time(towns, q_tree, S_france);
    cout << "Mean time of the nearest neighbor search using a QuadTree : " << times.first << " s" << endl;
    cout << "Mean time of the nearest neighbor search using a vector : " << times.second << " s" << endl;

    cout << "Mean number of nearest neighbor searches to make so that the construction of the QuadTree is profitable : "
         << time_construct_quad / (times.second - times.first) << endl;

    delete q_tree;

    return 0;
}