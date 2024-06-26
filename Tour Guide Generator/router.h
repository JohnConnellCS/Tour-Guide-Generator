#ifndef ROUTER
#define ROUTER

#include <queue>
#include <algorithm>

#include "base_classes.h"
#include "hashmap.h"
#include "geotools.h"

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	const GeoDatabaseBase* data;
	struct PathData {
		PathData(GeoPoint geo, double dist) :geoPt(geo), distance(dist) {}
		//defined greater than for priority queue
		bool operator>(const PathData& other) const {
			return this->distance >= other.distance;
		}
		GeoPoint geoPt;
		double distance;
	};
};

#endif