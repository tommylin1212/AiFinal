#include "vehicle.h"
#include "mycolony.h"
using namespace std;
ant::ant()
{
	m_pos = point(0, 0, 0);
}

ant::ant(mycolony *colony) {
	m_view = colony->m_view;
	m_returning = false;
	m_pos = colony->m_pos;
	m_speed = colony->m_speed;
	m_colony = colony;
}

void ant::explore() {
	calcob();
	calcter();
	if (m_desire.m_length < 1) {
		territory();
	}
}

void ant::search(std::vector<point> *things) {
	bool found = false;
	if (m_returning) {
		headback();
		hasreturned();
	}
	else {
		look(things);
	}
	move();
	return;
}

void ant::calcdesire(point p) {
	m_desire = myvec(p.m_xpos - m_pos.m_xpos, p.m_ypos - m_pos.m_ypos).norm();
}

void ant::harvest() {
	headback();
}

void ant::calcob() {
	if (((m_pos.m_xpos < 0) ||
		(m_pos.m_xpos > glutGet(GLUT_WINDOW_WIDTH))) ||
		((m_pos.m_ypos < 0) ||
		(m_pos.m_ypos > glutGet(GLUT_WINDOW_HEIGHT))))
	{
		m_desire.m_length = 0;
	}
}

void ant::calcter() {
	if (((m_pos.m_xpos < m_colony->m_pos.m_xpos - m_colony->m_territory)
		|| (m_pos.m_xpos > m_colony->m_pos.m_xpos + m_colony->m_territory)) ||
		((m_pos.m_ypos < m_colony->m_pos.m_ypos - m_colony->m_territory) ||
		(m_pos.m_ypos > m_colony->m_pos.m_ypos + m_colony->m_territory)))
	{
		m_desire.m_length = 0;
	}
}

void ant::plotsize() {
	glPointSize(2);
}

void ant::plot() {
	plotsize();
	m_pos.plot();
}

void ant::dplot() {
	plotsize();
	plotsight();
	m_pos.plot();
}

void ant::hplot(){
	plotsize();
	glBegin(GL_LINE_STRIP);
	glVertex2d(m_pos.m_xpos, m_pos.m_ypos);
	glVertex2d(m_colony->m_pos.m_xpos, m_colony->m_pos.m_ypos);
	glEnd();
	m_pos.plot();
}

void ant::hasreturned() {
	if (m_pos.getDist(m_colony->m_pos) < m_speed) {
		m_colony->addfood(1);
		m_returning = false;
	}
}

void ant::headback() {
	calcdesire(m_colony->m_pos);
	m_returning = true;
}

bool ant::canharvest(double dist, std::vector<point>* things, int i) {
	if (dist < m_speed) {
		things->erase(things->begin() + i);
		harvest();
		return false;
	}
	return true;
}

void ant::plotsight() {
	ngon(8, m_pos.m_xpos,
		m_pos.m_ypos,
		m_view, 0).plot(GL_LINE_LOOP);
}

void ant::look(vector<point> *things) {
	double record = MAXINT;
	bool found = false;
	double temp;
	int pt;

	for (int i = things->size() - 1; i >= 0; i--) {
		 temp = m_pos.getDist((*things)[i]);
		if (canharvest(temp, things, i)) {
			if (temp < record) {
				record = temp;
				if ((record < m_view)) {
					calcdesire((*things)[i]);
					found = true;
				}
			}
		}
		else {
			return;
		}
	}
	if (!found)explore();
}

void ant::move() {
	m_pos = m_pos.add(m_desire.sprod(m_speed));
}

void ant::territory() {
	calcdesire(point(m_colony->m_parentpos.m_xpos
		+ rand() % (int)m_colony->m_territory
		- rand() % (int)m_colony->m_territory
		, m_colony->m_parentpos.m_ypos
		+ rand() % (int)m_colony->m_territory
		- rand() % (int)m_colony->m_territory, 0));
}