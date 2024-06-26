#include "geodb.h"
#include "geopoint.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GeoDatabase::GeoDatabase() {}
GeoDatabase::~GeoDatabase() {}
bool GeoDatabase::load(const std::string& map_data_file) {
	ifstream infile(map_data_file);
	if (!infile) {
		return false;
	}
	string infoHolder;
	string streetName;
	string latitudeHold;
	string longitudeHold;
	int numPOI;
	while (getline(infile, infoHolder)) {
		streetName = infoHolder;
		getline(infile, infoHolder);
		istringstream iss(infoHolder);
		string lat1;
		string long1;
		string lat2;
		string long2;
		if (!(iss >> lat1 >> long1 >> lat2 >> long2))
			cerr << "bad input detected";
		char dummy;
		if (iss >> dummy)
			cerr << "ignoring whitespace";
		GeoPoint g1(lat1, long1);
		GeoPoint g2(lat2, long2);
		string key = g1.to_string() + g2.to_string();
		insertOrUpdate(g1, g2);
		streetNameMap.insert(key, streetName);

		getline(infile, infoHolder);
		numPOI = stoi(infoHolder);
		for (int i = 0; i < numPOI; i++) {
			GeoPoint g3 = midpoint(g1, g2);
			if (i == 0) {
				insertOrUpdate(g1, g3);
				insertOrUpdate(g2, g3);
				string segKey = g1.to_string() + g3.to_string();
				streetNameMap.insert(segKey, streetName);
				segKey = g2.to_string() + g3.to_string();
				streetNameMap.insert(segKey, streetName);
			}
			getline(infile, infoHolder);
			addPOI(infoHolder, g3);
		}

	}
	return true; //WRONG
}

void GeoDatabase::insertOrUpdate(GeoPoint g1, GeoPoint g2) {
	vector<GeoPoint>* existOne = streetPairMap.find(g1.to_string());
	if (existOne == nullptr) {
		//make a new vector, push the GeoPoint onto that vector, insert the vector into the streetPairMap
		vector<GeoPoint> newBucketOne;
		newBucketOne.push_back(g2);
		streetPairMap.insert(g1.to_string(), newBucketOne);
	}
	else {
		//if the geopoint already has a vector, push onto that vector
		existOne->push_back(g2);
	}

	vector<GeoPoint>* existTwo = streetPairMap.find(g2.to_string());
	if (existTwo == nullptr) {
		//make a new vector, push the GeoPoint onto that vector, insert the vector into the streetPairMap
		vector<GeoPoint> newBucketTwo;
		newBucketTwo.push_back(g1);
		streetPairMap.insert(g2.to_string(), newBucketTwo);
	}
	else {
		//if the geopoint already has a vector, push onto that vector
		existTwo->push_back(g1);
	}
}

void GeoDatabase::addPOI(string line, GeoPoint mid) {
	istringstream iss(line);
	string POIname;
	getline(iss, POIname, '|');
	string lat, lon;
	if (!(iss >> lat >> lon)) {
		cerr << "error processing in addPOI";
		return;
	}
	GeoPoint g1(lat, lon);
	streetNameMap.insert(g1.to_string() + mid.to_string(), "a path");
	pointsOfInterestMap.insert(POIname, g1);
	insertOrUpdate(g1, mid);
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
	const GeoPoint* g1 = pointsOfInterestMap.find(poi);
	if (g1 == nullptr)
		return false;
	point = *g1;
	return true;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
	vector<GeoPoint> g1;
	string key = pt.to_string();
	if (streetPairMap.find(key) != nullptr) {
		g1 = *streetPairMap.find(key);
	}
	return g1;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
	string keyOne = pt1.to_string() + pt2.to_string();
	string keyTwo = pt2.to_string() + pt1.to_string();
	if (streetNameMap.find(keyOne) == nullptr && streetNameMap.find(keyTwo) == nullptr)
		return "";
	if (streetNameMap.find(keyOne) != nullptr) {
		return *streetNameMap.find(keyOne);
	}
	return *streetNameMap.find(keyTwo);
}