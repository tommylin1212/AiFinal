#ifndef NGON_H
#define NGON_H
#include "Utils.h"
#include "globalgl.h"

class ngon {
public:
	ngon();
	ngon(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
	void plot(int);
private:
	GLint m_sides;
	GLdouble m_xpos;
	GLdouble m_ypos;
	GLdouble m_radius;
	GLdouble m_angle;
};
#endif
