#include "point.h"

point::point(GLdouble xpos, GLdouble ypos, GLdouble zpos) {
	m_xpos = xpos;
	m_ypos = ypos;
	m_zpos = zpos;
}

point::point() {
	m_xpos = -1;
	m_ypos = -1;
	m_zpos = -1;
}

void point::getPos(GLdouble& x, GLdouble& y, GLdouble& z) {
	x = m_xpos;
	y = m_ypos;
	z = m_zpos;
}

void point::plot() {
	glBegin(GL_POINTS);
	glVertex3d(m_xpos, m_ypos, m_zpos);
	glEnd();
}

point point::add(myvec a) {
	return point((m_xpos + a.m_x), (m_ypos + a.m_y), 0);
}

myvec point::sub(point p)
{
	return myvec(p.m_xpos - m_xpos, p.m_ypos - m_ypos).norm();
}

GLdouble point::getDist(point p) {
	return	sqrt((m_xpos - p.m_xpos)*(m_xpos - p.m_xpos)
		+ (m_ypos - p.m_ypos)*(m_ypos - p.m_ypos));
}