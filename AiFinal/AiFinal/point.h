#ifndef POINT_H
#define POINT_H
#include "Utils.h"
#include "globalgl.h"
#include "myvec.h"
class myvec;
class point {
public:
	point();
	point(GLdouble, GLdouble, GLdouble);
	void getPos(GLdouble&, GLdouble&, GLdouble&);
	//void setPos(GLdouble, GLdouble, GLdouble);
	myvec sub(point);
	GLdouble getDist(point);
	void plot();
	GLdouble m_xpos;
	GLdouble m_ypos;
	GLdouble m_zpos;
	point add(myvec);
private:
};

#endif