#ifndef MYVEC_H
#define MYVEC_H
#include "Utils.h"
#include "globalgl.h"
#include "point.h"
#include <math.h>
class myvec {
public:
	myvec();

	myvec(GLdouble, GLdouble);
	myvec norm();
	myvec perp();
	GLdouble dprod(myvec);
	myvec sprod(GLdouble);
	myvec add(myvec);
	myvec sub(myvec);
	GLdouble m_x;
	GLdouble m_y;
	GLdouble m_length;
private:
};

#endif