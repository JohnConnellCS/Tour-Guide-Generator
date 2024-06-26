#ifndef GEO_DATABASE
#define GEO_DATABASE

#include <string>

#include "base_classes.h"
#include "hashmap.h"
#include "geotools.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	void insertOrUpdate(GeoPoint g1, GeoPoint g2); //returns a string with all of the geopoints concatonated
	void addPOI(std::string line, GeoPoint mid);
	HashMap<std::vector<GeoPoint>> streetPairMap;
	HashMap<std::string> streetNameMap;
	HashMap<GeoPoint> pointsOfInterestMap;
};


#endif