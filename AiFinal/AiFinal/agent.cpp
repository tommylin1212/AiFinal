#include "agent.h"
#include <iostream>
using namespace std;
int maxF = 5;//max attraction
int maxS = 150;//max sight
int minS = 10;//min sight
double M_PI = 3.145989;
agent::agent(){
	
	m_health = 1;
	m_maxspeed = 5;
	m_maxforce = 0.8;
	m_size = 15;
	m_counter = 0;
	m_vel = myvec(1, 1).norm();
	m_wandering = false;
	m_wander= point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0);
}

agent::agent(point pos){
	m_pos = pos;
	m_health = 1;
	m_maxspeed = 5;
	m_maxforce = 0.8;
	m_size = 15;
	m_counter = 0;
	m_vel = myvec(1, 1).norm();
	m_wandering = false;
	m_wander = point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0);
	//no dna need to create
	m_dna.push_back((rand() % (2 * maxF))-maxF + 0.1);//food attractiveness
	m_dna.push_back((rand() % (2 * maxF)) - maxF + 0.1);//poison attractiveness
	m_dna.push_back((rand() % (maxS-minS)) + minS);//food sight
	m_dna.push_back((rand() % (maxS - minS)) + minS);//poison sight
	//cout << "food: " << m_dna[0] << " poison: " << m_dna[1] << " fs: "<<m_dna[2]<<" ps: "<<m_dna[3]<<endl;
}

agent::agent(point pos,vector<double> dna){
	m_pos = pos;
	m_health = 1;
	m_maxspeed = 5;
	m_maxforce = 0.8;
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
void agent::setHealth(double h){
	m_health = h; 

}
bool agent::outOfBounds() {
	int border = 100;
	double xmax = glutGet(GLUT_WINDOW_WIDTH);
	double ymax = glutGet(GLUT_WINDOW_HEIGHT);
	double xpos=this->m_pos.m_xpos;
	double ypos = this->m_pos.m_ypos;
	if ((border > xpos) || (xpos > xmax-border)) {
		reCenter();
		return true;
	}
	if ((border > ypos) || (ypos > ymax-border)) {
		reCenter();
		return true;
	}
	return false;
}


void agent::doSteering(point target,bool type){
	if (outOfBounds()) {
		return;
	}
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

void agent::reCenter(){
	double maxxpos = glutGet(GLUT_WINDOW_WIDTH);
	double maxypos = glutGet(GLUT_WINDOW_HEIGHT);
	m_desired = myvec(maxxpos/2 - m_pos.m_xpos, maxypos/2 - m_pos.m_ypos).norm();

	m_desired = m_desired.sprod(m_maxspeed);
	m_acc = m_desired.sub(m_vel);
	
	if (m_acc.m_length > m_maxforce) {
		m_acc = m_acc.norm().sprod(m_maxforce);
	}
	m_vel = m_vel.add(m_acc);

	m_vel = m_vel.norm().sprod(m_maxspeed);//go as fast as possible in that direction
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
	body.plot(GL_POLYGON);
}

point agent::getPos(){
	return m_pos;
}
void agent::setPos(point p){
	m_pos = p;
}

void agent::health(double num){
	m_health += num;
}

double agent::getHealth(){
	return m_health;
}

std::vector<double> agent::getDNA(){
	return m_dna;
}

void agent::age(int i){
	m_counter += i;
}



int agent::getAge(){
	return m_counter;
}

player::player(point pos){
	m_pos = pos;
	m_size = 15;
	m_health = 2;
}

void player::steer(int rln){
	heading += rln;
	heading = (int)floor(heading)% 360;
}

point player::deadReckon(){
	double x0, y0, x1, y1;
	x0 = m_pos.m_xpos;
	y0 = m_pos.m_ypos;
	x1 = sin((heading*(M_PI / 180)));
	y1 = cos((heading*(M_PI / 180)));
	x0 += (x1*m_maxspeed);
	y0 += (y1*m_maxspeed);
	point next_desired = point(x0, y0,0);
	return next_desired;
}

void player::doSteering(point pos){
	m_desired = myvec(pos.m_xpos - m_pos.m_xpos, pos.m_ypos - m_pos.m_ypos).norm();

	m_desired = m_desired.sprod(m_maxspeed);
	m_acc = m_desired.sub(m_vel);

	if (m_acc.m_length > m_maxforce) {
		m_acc = m_acc.norm().sprod(m_maxforce);
	}
	m_vel = m_vel.add(m_acc);

	m_vel = m_vel.norm().sprod(m_maxspeed);//go as fast as possible in that direction
	m_pos = m_pos.add(m_vel);
}

void player::draw(){
	double angle = atan2(m_vel.m_y, m_vel.m_x);
	glColor3f(1 - (m_health), m_health, 0);
	//m_pos.plot();
	ngon body(5, m_pos.m_xpos, m_pos.m_ypos, m_size, angle);
	glPointSize(4);
	body.plot(GL_POLYGON);
}
void player::eat(std::vector<item>* items) {
	double record = numeric_limits<double>::infinity();//distance of closest food;
	int closest = -1;//index of closest food;
	for (int i = 0; i < items->size(); i++) {
		double dist = myvec((*items)[i].getPos().m_xpos - m_pos.m_xpos, (*items)[i].getPos().m_ypos - m_pos.m_ypos).m_length;
		if (dist < record) {
			record = dist;
			closest = i;
		}
	}
	if (record < m_size) {//if we are close enough to eat, let's eat
		if ((*items)[closest].getType()) {
			health(0.1);
			m_counter++;
		}
		else {
			health(-1);
		}
		items->erase(items->begin() + closest);
	}
	doSteering(deadReckon());
}