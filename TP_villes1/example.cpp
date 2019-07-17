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
    QuadTree<Point2D<float> > *ql;
    ql = new QuadNode<Point2D<float> >(0, 0, 0, 0);
    insert(ql, Square(0, 0, 10000), Point2D<float>(town1.x(), town1.y(), 3.5));
    insert(ql, Square(0, 0, 15000), Point2D<float>(town2.x(), town2.y(), 4.5));

    display(ql);


    return 0;
}