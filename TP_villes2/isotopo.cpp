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


set<Town>
q3(const vector<Town> &towns, const map<string, int> &town_names, const map<Point2D, int> &town_coordinates) {
    set<Town> N, C, intersect;
    cout << "Creating the set N of towns whose name is repeated at least once, and C of towns whose coordinates are "
            "repeated at least once" << endl;

    for (int i = 0; i < towns.size(); i++) {
        if (town_names.at(towns[i].name()) > 1) {
            N.insert(towns[i]);
        }
        if (town_coordinates.at(towns[i].point()) > 1) {
            C.insert(towns[i]);
        }
    }

    cout << "Size of N : " << N.size() << endl;
    cout << "Size of C : " << C.size() << endl;

    auto end = set_intersection(N.begin(), N.end(), C.begin(), C.end(), inserter(intersect, intersect.begin()));

    //auto size_of_intersect = distance(intersect.begin(), intersect.end());

    cout << "The intersection of N and C has " << intersect.size() << " elements" << endl;
    return intersect;
}


void q4_naive(const set<Town> &intersect) {
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


void q4(const set<Town> &intersect) {
    int counter = 0;
    //Selon l'enonce, les villes v1, v2, v3, v4 sont toutes dans N intersect C.
    //On cree d'abord deux maps, une des villes qui ont le meme nom, l'autre des villes qui ont les memes coordonnees
    map<string, set<Town>> towns_same_name;
    map<Point2D, set<Town>> towns_same_coord;
    for (auto it = intersect.begin(); it != intersect.end(); it++) {
        towns_same_name[it->name()].insert(*it);
        towns_same_coord[it->point()].insert(*it);
    }

    // Premiere boucle sur toutes les villes de N inter C
    for (auto it1 = intersect.begin(); it1 != intersect.end(); it1++) {
        Point2D coordinates_v1 = it1->point();
        string name_v1 = it1->name();

        // Boucle sur les villes v2 de memes coordonnees que v1 (4 possibilites max)
        for (auto it2 = towns_same_coord[coordinates_v1].begin();
             it2 != towns_same_coord[coordinates_v1].end(); it2++) {
            if (*it1 != *it2) {    //On enleve le cas v1=v2

                // Boucle sur les villes v3 de meme nom que v1 (9 possibilites max)
                for (auto it3 = towns_same_name[name_v1].begin(); it3 != towns_same_name[name_v1].end(); it3++) {
                    if (*it1 != *it3) {        //On enleve le cas v1=v3

                        // On cherche v4 de memes coordonnees que v3 et de meme nom que v2
                        set<Town> same_name_v2 = towns_same_name[it2->name()];
                        set<Town> same_coord_v3 = towns_same_coord[it3->point()];
                        set<Town> test_v4;
                        auto it4 = set_intersection(same_name_v2.begin(), same_name_v2.end(),
                                                    same_coord_v3.begin(), same_coord_v3.end(),
                                                    inserter(test_v4, test_v4.begin()));

                        if (!test_v4.empty()) {
                            counter += test_v4.size();
                        }
                    }
                }
            }
        }
    }

    counter /= 4; //On compte chaque quadruplet 4 fois

    cout << "The number of towns where we can be mistaken by hearing about a town A close to a town B is : " << counter
         << endl;
    //On fait au maximum 207*4*9 = 7452 iterations
    //La methode naive implementee au dessus fait 4 parmi 210 (4 boucles et 207 elements dans l'ensemble) = environ 78 Millions d'iterations
    //Le gain de temps est d'un facteur 10.000
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
    //q4_naive(intersect);

    // That's all folks
    return 0;
}
