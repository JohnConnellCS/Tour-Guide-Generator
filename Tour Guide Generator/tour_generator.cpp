#include "tour_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
{
	data = &geodb;
	this->router = &router;
}
TourGenerator::~TourGenerator() {}
std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
	std::vector<TourCommand> cmdVec;
	GeoPoint curLocation;
	string poiName;
	string poiDesc;
	string streetName;
	double lineAngle;
	string currentDir;
	for (int i = 0; i < stops.size(); i++) {
		stops.get_poi_data(i, poiName, poiDesc);
		if (i != 0) {
			GeoPoint desiredLocation;
			if (!data->get_poi_location(poiName, desiredLocation)) {
				std::vector<TourCommand> emptyVec;
				return emptyVec;
			}
			vector<GeoPoint> pathToNext = router->route(curLocation, desiredLocation);
			if (pathToNext.empty()) {
				std::vector<TourCommand> emptyVec;
				return emptyVec;
			}
			for (int j = 0; j < pathToNext.size() - 1; j++) {
				streetName = data->get_street_name(pathToNext[j], pathToNext[j + 1]);
				TourCommand proceedCmd;
				lineAngle = angle_of_line(pathToNext[j], pathToNext[j + 1]);
				currentDir = getDirec(lineAngle);
				proceedCmd.init_proceed(currentDir, streetName, distance_earth_miles(pathToNext[j], pathToNext[j + 1]), pathToNext[j], pathToNext[j + 1]);
				cmdVec.push_back(proceedCmd);
				if (j != pathToNext.size() - 2 && streetName != data->get_street_name(pathToNext[j + 1], pathToNext[j + 2]) && angle_of_turn(pathToNext[j], pathToNext[j + 1], pathToNext[j + 2]) >= 1 && angle_of_turn(pathToNext[j], pathToNext[j + 1], pathToNext[j + 2]) <= 359) {
					double turnAngle = angle_of_turn(pathToNext[j], pathToNext[j + 1], pathToNext[j + 2]);
					TourCommand turnCmd;
					if (turnAngle >= 1 && turnAngle < 180) {
						turnCmd.init_turn("left", data->get_street_name(pathToNext[j + 1], pathToNext[j + 2]));
					}
					else {
						turnCmd.init_turn("right", data->get_street_name(pathToNext[j + 1], pathToNext[j + 2]));
					}
					cmdVec.push_back(turnCmd);
				}
			}
		}
		TourCommand cmd;
		if (!data->get_poi_location(poiName, curLocation)) {
			std::vector<TourCommand> emptyVec;
			return emptyVec;
		}
		cmd.init_commentary(poiName, poiDesc);
		cmdVec.push_back(cmd);
	}
	return cmdVec;
}

string TourGenerator::getDirec(double angle) const {
	if (0 <= angle && angle < 22.5) {
		return "east";
	}
	else if (22.5 <= angle && angle < 67.5) {
		return "northeast";
	}
	else if (67.5 <= angle && angle < 112.5) {
		return "north";
	}
	else if (112.5 <= angle && angle < 157.5) {
		return "northwest";
	}
	else if (157.5 <= angle && angle < 202.5) {
		return "west";
	}
	else if (202.5 <= angle && angle < 247.5) {
		return "southwest";
	}
	else if (247.5 <= angle && angle < 292.5) {
		return "south";
	}
	else if (292.5 <= angle && angle < 337.5) {
		return "southeast";
	}
	else if (angle >= 337.5) {
		return "east";
	}
	return "east";
}