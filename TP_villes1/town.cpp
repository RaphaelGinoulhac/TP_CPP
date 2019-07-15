/*
 * A class to group a town name with its coordinates
 */

#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cmath>
using std::sqrt;
using std::min;
using std::max;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "town.h"


// Construct a new town object given its name, latitude and longitude
Town::Town(string name, float lat, float lon)
    : _name(name), _lat(lat), _lon(lon)
{
    pair<float,float> coords = geoToLambert93(lat,lon);
    _x = coords.first;
    _y = coords.second;
}

// Return the distance to given town (in kilometers)
float Town::dist(const Town t) const
{
    return sqrt((_x-t._x)*(_x-t._x)+(_y-t._y)*(_y-t._y));
}

// Read file of town names and coordinates, and add them into a vector
// Return number of towns read, or negative value if some error occurred
int Town::read_file(string town_file, vector<Town> &towns,
		    float &xmin, float &ymin, float &xmax, float &ymax)
{
    // Open file stream
    ifstream townfs(town_file.c_str());
    // Check opening was OK
    if (!townfs.is_open()) {
	cerr << "Cannot open file: " << town_file << endl;
	return -1; // File not found, permission denied...
    }
    // Read file
    int nb_towns = 0;
    while (true) {
	// Read name (stopping at delimiting character tab)
	string name;
	getline(townfs, name, '\t');
	if (!townfs.good()) { // Break on error or end of file
	    if (name.empty()) townfs.clear(); // No error if end of file
	    else townfs >> name; // (Dummy) error is line not empty
	    break; }
	// Read coordinates
	float latitude;
	float longitude;
	townfs >> latitude >> longitude;
	if (townfs.fail()) break; // Break on error
	// Flush line
	string dummy;
	getline(townfs, dummy);
	if (townfs.fail()) break; // Break on error
	// Remember town
	Town town(name,latitude,longitude);
	towns.push_back(town);
	nb_towns++;
	xmin = min(town.x(),xmin);
	ymin = min(town.y(),ymin);
	xmax = max(town.x(),xmax);
	ymax = max(town.y(),ymax);
    }
    // In case an error occurred
    if (townfs.fail()) { 
	cerr << "Error while reading file " << town_file
	     << " at line: " << (nb_towns+1) << endl;
	return -2; // Bad line format
    }
    // Return the number of towns read
    return nb_towns;
}
int Town::read_file(string town_file, vector<Town> &towns)
{
    // Dummy variables
    float xmin, ymin, xmax, ymax;
    // Read file
    return Town::read_file(town_file, towns, xmin, ymin, xmax, ymax);
}


// Return a vector of towns with given name
vector<Town>
Town::towns_with_name(const vector<Town> towns, string name)
{
    vector<Town> found;
    for (vector<Town>::const_iterator
	     it = towns.begin(); it != towns.end(); ++it)
	if (it->name() == name)
	    found.push_back(*it);
    return found;
}

// Return a vector of towns with given Lambert 93 (x,y) coordinates
vector<Town>
Town::towns_with_x_y(const vector<Town> towns, float x, float y)
{
    vector<Town> found;
    for (vector<Town>::const_iterator
	     it = towns.begin(); it != towns.end(); ++it)
	if (it->x() == x && it->y() == y)
	    found.push_back(*it);
    return found;
}

// Return a vector of towns with given geographic coordinates
// (latitude, longitude)
vector<Town>
Town::towns_with_lat_lon(const vector<Town> towns, float lat, float lon)
{
    vector<Town> found;
    for (vector<Town>::const_iterator
	     it = towns.begin(); it != towns.end(); ++it)
	if (it->lat() == lat && it->lon() == lon)
	    found.push_back(*it);
    return found;
}



/*
 * Lambert93 projection utilities
 */

#include <cmath>
using std::cos;
using std::exp;
using std::log;
using std::pow;
using std::sin;
using std::sqrt;
using std::tan;
#include <utility>
using std::make_pair;

//
// Constants used for the Lambert 93 projection
//
inline float degreeToRadian(float deg){ return deg/180*M_PI; }
const float a = 6378137;       // semi-major axis of the ellipsoid
const float e = 0.08181919106; // first eccentricity of the ellipsoid
const float lc = degreeToRadian(3.f);
const float l0 = degreeToRadian(3.f);
const float phi1 = degreeToRadian(44.f); // 1st automecoic parallel
const float phi2 = degreeToRadian(49.f); // 2nd automecoic parallel
const float phi0 = degreeToRadian(46.5f);// latitude of origin
const float X0 =  700000; // x coordinate at origin
const float Y0 = 6600000; // y coordinate at origin
// Normals
const float gN1 = a/sqrt(1-e*e*sin(phi1)*sin(phi1));
const float gN2 = a/sqrt(1-e*e*sin(phi2)*sin(phi2));
// Isometric latitudes
const float gl1=log(tan(M_PI/4+phi1/2)*pow((1-e*sin(phi1))/(1+e*sin(phi1)),e/2));
const float gl2=log(tan(M_PI/4+phi2/2)*pow((1-e*sin(phi2))/(1+e*sin(phi2)),e/2));
const float gl0=log(tan(M_PI/4+phi0/2)*pow((1-e*sin(phi0))/(1+e*sin(phi0)),e/2));
// Projection exponent
const float n = (log((gN2*cos(phi2))/(gN1*cos(phi1))))/(gl1-gl2);
// Projection constant
const float c = ((gN1*cos(phi1))/n)*exp(n*gl1);
// Coordinate
const float ys = Y0 + c*exp(-n*gl0);

// Convert geographic coordinates (latitude, longitude in degrees) into
// cartesian coordinates (in kilometers) using the Lambert 93 projection.
pair<float,float> geoToLambert93(float latitude,float longitude)
{
    float phi = degreeToRadian(latitude);
    float l   = degreeToRadian(longitude);
    float gl  = log(tan(M_PI/4+phi/2)*pow((1-e*sin(phi))/(1+e*sin(phi)),e/2));
    float x93 = X0 + c*exp(-n*gl)*sin(n*(l-lc));
    float y93 = ys - c*exp(-n*gl)*cos(n*(l-lc));
    return make_pair(x93/1000,y93/1000);
}
