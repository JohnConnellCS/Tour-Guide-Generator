#ifndef TOUR_GEN
#define TOUR_GEN

#include "base_classes.h"
#include "geotools.h"

class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
	std::string getDirec(double angle) const;
	const GeoDatabaseBase* data;
	const RouterBase* router;
};


#endif