#ifndef POLYLINE_H
#define POLYLINE_H
#include "Utils.h"
#include "globalgl.h"
#include "point.h"
#include <vector>

class polyline {
public:
	polyline();
	polyline(point);
	void add(point);
	void plot();
	std::vector<point> m_points;
private:
};

#endif