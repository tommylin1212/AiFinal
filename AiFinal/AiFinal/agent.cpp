#include "agent.h"
#include <iostream>
using namespace std;
int maxF = 5;//max attraction
int maxS = 100;//max sight
int minS = 10;//min sight

agent::agent(point pos){
	m_pos = pos;
	m_health = 1;
	m_maxspeed = 5;
	m_maxforce = 0.9;
	m_size = 15;
	m_counter = 0;
	m_vel = myvec(1, 1).norm();
	m_wandering = false;
	m_wander= point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0);
	//no dna need to create
	m_dna.push_back((rand() % (2 * maxF))-maxF + 0.1);//food attractiveness
	m_dna.push_back((rand() % (2 * maxF)) - maxF + 0.1);//poison attractiveness
	m_dna.push_back((rand() % (maxS-minS)) + minS);//food sight
	m_dna.push_back((rand() % (maxS - minS)) + minS);//poison sight
	cout << "food: " << m_dna[0] << " poison: " << m_dna[1] << " fs: "<<m_dna[2]<<" ps: "<<m_dna[3]<<endl;
}

agent::agent(point pos,vector<double> dna){
	m_pos = pos;
	m_health = 1;
	m_maxspeed = 5;
	m_maxforce = 0.5;
	m_size = 15;
	m_vel = myvec(1, 1).norm();
	m_dna = dna;
	m_counter = 0;
	m_wandering = false;
	m_wander = point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0);
	//got dna passed down maybe mutate 1/10
	for (int i = 0; i < m_dna.size(); i++) {
		if (rand() % 10 < 1) {
			if (i < 2) {//adjust repulsion
				m_dna[i] = m_dna[i] + ((rand() % maxF) - maxF/2.0) / 10.0;//+- a maximum of 5%
			}
			else {//adjust sight
				m_dna[i] = m_dna[i] + ((rand() % maxS) - maxS/2.0) / 10.0;//+- a maximum of 5%
			}
		}
	}
}

void agent::doSteering(point target,bool type){
	m_desired = myvec(target.m_xpos - m_pos.m_xpos, target.m_ypos - m_pos.m_ypos).norm();
	
	m_desired=m_desired.sprod(m_maxspeed);
	m_acc = m_desired.sub(m_vel);
	if (!type) {//poison
		m_acc=m_acc.sprod(m_dna[1]);//poison attractiveness
	}
	else {//food
		m_acc = m_acc.sprod(m_dna[0]);//food attractiveness
	}
	if (m_acc.m_length > m_maxforce) {
		m_acc = m_acc.norm().sprod(m_maxforce);
	}
	m_vel = m_vel.add(m_acc);
	
	m_vel=m_vel.norm().sprod(m_maxspeed);//go as fast as possible in that direction
	m_pos = m_pos.add(m_vel);
}

void agent::eat(std::vector<item>* items){
	double record = numeric_limits<double>::infinity();//distance of closest food;
	int closest = -1;//index of closest food;
	for (int i = 0; i < items->size(); i++) {
		double dist=myvec((*items)[i].getPos().m_xpos - m_pos.m_xpos, (*items)[i].getPos().m_ypos - m_pos.m_ypos).m_length;
		if (dist < record) {
			if (dist < m_dna[2] && (*items)[i].getType()) {//food
				record = dist;
				closest = i;
			}
			else if (dist < m_dna[3]&&!(*items)[i].getType()) {//poison
				record = dist;
				closest = i;
			}
			else {
				//cant see it
			}
		}
	}
	if (record < m_vel.m_length) {//if we are close enough to eat, let's eat
		
		if ((*items)[closest].getType()) {
			health(0.1);
			m_counter++;
		}
		else {
			health(-1);
		}
		items->erase(items->begin() + closest);
	}
	else if(closest != -1) {//if we found something seek it
		doSteering((*items)[closest].getPos(), (*items)[closest].getType());
		m_wandering = false;
	}
	else {//wander
		if (!m_wandering) {
			m_wandering = true;
			m_wander = point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0);
		}
		doSteering(m_wander, true);
	}
}
void agent::draw() {
	double angle = atan2(m_vel.m_y, m_vel.m_x);
	glColor3f(1-(m_health),m_health, 0);
	//m_pos.plot();
	ngon body(3, m_pos.m_xpos, m_pos.m_ypos, m_size, angle);
	glPointSize(4);
	body.plot(GL_LINE_LOOP);
}

point agent::getPos()
{
	return m_pos;
}

void agent::health(double num){
	m_health += num;
}

double agent::getHealth()
{
	return m_health;
}

std::vector<double> agent::getDNA()
{
	return m_dna;
}

void agent::age(int i){
	m_counter += i;
}

int agent::getAge()
{
	return m_counter;
}

