#include "polyline.h"
using namespace std;
polyline::polyline() {
	//nothing to do here :)
}

polyline::polyline(point po) {
	add(po);
}

void polyline::add(point po) {
	m_points.push_back(po);
}

void polyline::plot() {
	glColor3f(1.5f, 0.5f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (vector<point>::iterator i = m_points.begin(); i < m_points.end(); i++) {
		glVertex2d(i->m_xpos, i->m_ypos);
	}
	glEnd();
}