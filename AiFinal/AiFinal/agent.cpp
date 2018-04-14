#include "agent.h"
#include <iostream>
using namespace std;


agent::agent(point pos, double health, double maxspeed, double maxforce, float food, float poison){
	m_pos = pos;
	m_health = health;
	m_maxspeed = maxspeed;
	m_maxforce = maxforce;
	m_foodfactor = food;
	m_poisonfactor = poison;
	m_size = 15;
	m_vel = myvec(1, 1).norm();
}

void agent::doSteering(point target){
	m_desired = myvec(target.m_xpos - m_pos.m_xpos, target.m_ypos - m_pos.m_ypos).norm();
	m_desired=m_desired.sprod(m_maxspeed);
	m_acc = m_desired.sub(m_vel);
	if (m_acc.m_length > m_maxforce) {
		m_acc = m_acc.norm().sprod(m_maxforce);
	}
	m_vel = m_vel.add(m_acc);
	m_vel.norm().sprod(m_maxspeed);
	m_pos = m_pos.add(m_vel);

}

void agent::eat(std::vector<item>* items){
	double record = numeric_limits<double>::infinity();//distance of closest food;
	int closest = -1;//index of closest food;
	for (int i = 0; i < items->size(); i++) {
		double dist=myvec((*items)[i].getPos().m_xpos - m_pos.m_xpos, (*items)[i].getPos().m_ypos - m_pos.m_ypos).m_length;
		if (dist < record) {
			record = dist;
			cout << "record: " << record << endl;
			closest = i;
		}
	}
	if (record < m_vel.m_length) {
		items->erase(items->begin() + closest);
	}
	doSteering((*items)[closest].getPos());
}
void agent::draw() {
	double angle = atan2(m_vel.m_y, m_vel.m_x);
	m_pos.plot();
	ngon body(3, m_pos.m_xpos, m_pos.m_ypos, m_size, angle);
	glPointSize(4);
	glColor3f(1.0, 1.0, 1.0);
	body.plot(GL_LINE_LOOP);
}

