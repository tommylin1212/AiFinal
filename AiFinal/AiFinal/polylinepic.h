#ifndef POLYLINEPIC_H
#define POLYLINEPIC_H
#include "Utils.h"
#include "globalgl.h"
#include "point.h"
#include "polyline.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
class polylinepic {
public:
	polylinepic();
	polylinepic(std::string);
	void add(polyline);
	void plot();
	void openfile(std::string);
	GLdouble m_left;
	GLdouble m_right;
	GLdouble m_top;
	GLdouble m_bottom;
private:
	std::vector<polyline> m_polylines;
};
#endif