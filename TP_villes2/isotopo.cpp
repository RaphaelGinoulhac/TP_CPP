#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "point2d.h"
#include "town.h"

#include <set>
#include <map>
#include <algorithm>


using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";


map<string, int> histogram_of_name_repetitions(const vector<Town> &towns) {
    map<string, int> town_names;
    for (int i = 0; i < towns.size(); i++)
        town_names[towns[i].name()]++;

    map<int, int> histogram;
    for (auto it = town_names.begin(); it != town_names.end(); it++)
        histogram[it->second]++;

    cout << "Histogram of the repetitions of town names : " << endl;
    for (auto it = histogram.begin(); it != histogram.end(); it++)
        cout << "Number of town names used by " << it->first << " towns exactly : " << it->second << endl;

    return town_names;
}


map<Point2D, int> histogram_of_coordinate_repetitions(const vector<Town> &towns) {
    map<Point2D, int> town_coordinates;
    for (int i = 0; i < towns.size(); i++)
        town_coordinates[towns[i].point()]++;

    map<int, int> histogram;
    for (auto it = town_coordinates.begin(); it != town_coordinates.end(); it++)
        histogram[it->second]++;

    cout << "Histogram of the repetitions of town coordinates : " << endl;
    for (auto it = histogram.begin(); it != histogram.end(); it++)
        cout << "Number of town coordinates used by " << it->first << " towns exactly : " << it->second << endl;
    return town_coordinates;
}


set<Town> q3(const vector<Town> &towns, const map<string, int> &town_names, const map<Point2D, int> &town_coordinates) {
    set<Town> N, C, intersect;
    cout << "Creating the set N of towns whose name is repeated at least once, and C of towns whose coordinates are "
            "repeated at least once" << endl;
    //On calcule a la volee la taille de N et C car calculer la taille du set est une operation qui coute O(n)
    int size_of_N = 0, size_of_C = 0;

    for (int i = 0; i < towns.size(); i++) {
        if (town_names.at(towns[i].name()) > 1) {
            N.insert(towns[i]);
            size_of_N++;
        }
        if (town_coordinates.at(towns[i].point()) > 1) {
            C.insert(towns[i]);
            size_of_C++;
        }
    }

    cout << "Size of N : " << size_of_N << endl;
    cout << "Size of C : " << size_of_C << endl;

    auto end = set_intersection(N.begin(), N.end(), C.begin(), C.end(), inserter(intersect, intersect.begin()));

    auto size_of_intersect = distance(intersect.begin(), intersect.end());

    cout << "The intersection of N and C has " << size_of_intersect << " elements" << endl;
    return intersect;
}


void q4(const set<Town> &intersect) {
    int counter = 0;
    //Selon l'enonce, les villes v1, v2, v3, v4 sont toutes dans N intersect C.
    //On fait alors une recherche exhaustive dans l'ensemble intersect, et on gagne du temps en initialisant les iterateurs
    //de chaque boucle au successeur de l'iterateur de la boucle precedente.
    for (auto it = intersect.begin(); it != intersect.end(); it++) {
        for (auto it2 = next(it, 1); it2 != intersect.end(); it2++) {
            for (auto it3 = next(it2, 1); it3 != intersect.end(); it3++) {
                for (auto it4 = next(it3, 1); it4 != intersect.end(); it4++) {
                    if (it->point() == it2->point() && it->name() == it3->name() && it3->point() == it4->point() &&
                        it2->name() == it4->name())
                        counter++;
                }
            }
        }
    }
    cout << "The number of towns where we can be mistaken by hearing about a town A close to a town B is : " << counter
         << endl;
}


/*
 * Study French isotoponyms
 */
int main() {
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
        cout << "Error while reading file" << endl;
        return 2;
    }
    if (nb_towns == 0) {
        cout << "No town found" << endl;
        return 1;
    }
    // Initialize random seed
    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
         << ((float) (time2 - time1) / CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
         << towns.size() /* same as nb_towns */ << endl;
    cout << "A random town, using format \"name[lat,lon](x,y)\": "
         << towns[rand() % towns.size()] << endl;


    //Q1
    map<string, int> town_names = histogram_of_name_repetitions(towns);

    //Q2
    map<Point2D, int> town_coordinates = histogram_of_coordinate_repetitions(towns);

    //Q3
    set<Town> intersect = q3(towns, town_names, town_coordinates);

    //Q4
    q4(intersect);

    // That's all folks
    return 0;
}
