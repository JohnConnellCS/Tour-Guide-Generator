#include "router.h"
#include "geotools.h"
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db) {
	data = &geo_db;
}
Router::~Router() {}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
	bool foundPointTwo = false;
	HashMap<GeoPoint> pathing;
	priority_queue<PathData, vector<PathData>, greater<PathData>> pointChecker;
	pointChecker.push(PathData(pt1, 0));
	while (!pointChecker.empty()) {
		PathData cur = pointChecker.top();
		if (pointChecker.top().geoPt.latitude == pt2.latitude && pointChecker.top().geoPt.longitude == pt2.longitude) {
			foundPointTwo = true;
			break;
		}
		vector<GeoPoint> v = data->get_connected_points(pointChecker.top().geoPt);
		for (int i = 0; i < v.size(); i++) {
			double distFromSource = distance_earth_miles(cur.geoPt, v[i]);
			double totalDist = cur.distance + distFromSource;
			if (pathing.find(v[i].to_string()) == nullptr) {
				pointChecker.push(PathData(v[i], totalDist));
				pathing.insert(v[i].to_string(), pointChecker.top().geoPt);
			}
		}
		pointChecker.pop();
	}
	vector<GeoPoint> path;
	if (foundPointTwo) {
		GeoPoint pathTrack = pt2;
		while (pathTrack.latitude != pt1.latitude || pathTrack.longitude != pt1.longitude) {
			path.push_back(pathTrack);
			pathTrack = *pathing.find(pathTrack.to_string());
		}
		path.push_back(pt1);
		reverse(path.begin(), path.end());
	}
	return path;
}



