#include "ngon.h"

#define _USE_MATH_DEFINES
#include <math.h>
ngon::ngon() {
	m_sides = -1;
	m_xpos = 0;
	m_ypos = 0;
	m_radius = 0;
	m_angle = 0;
}

ngon::ngon(GLint sides, GLdouble xpos, GLdouble ypos, GLdouble radius, GLdouble angle) {
	m_sides = sides;
	m_xpos = xpos;
	m_ypos = ypos;
	m_radius = radius;
	m_angle = angle;
}

void ngon::plot(int style) {
	GLdouble rpp = 2 * M_PI / m_sides;
	glBegin(style);
	for (int i = 0; i < m_sides; i++) {
		glVertex2d(m_xpos + (m_radius*cos((m_angle + (rpp*i)))),
			m_ypos + (m_radius*sin((m_angle + (rpp*i)))));
	}
	glEnd();
}

void ngon::rosette() {
	GLdouble rpp = 2 * M_PI / m_sides;
	glBegin(GL_LINES);
	for (int i = 0; i <= m_sides; i++) {
		for (int j = 0; j <= m_sides; j++) {
			glVertex2d(m_xpos + (m_radius*cos((m_angle + (rpp*i)))),
				m_ypos + (m_radius*sin((m_angle + (rpp*i)))));
			glVertex2d(m_xpos + (m_radius*cos((m_angle + (rpp*j)))),
				m_ypos + (m_radius*sin((m_angle + (rpp*j)))));
		}
	}
	glEnd();
}