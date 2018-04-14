#ifndef AGENT_H
#define AGENT_H
#include"point.h"
#include "myvec.h"
#include "item.h"
#include <vector>
#include "ngon.h"
#include <limits>
class agent {
public:
	agent(point pos,double health,double maxspeed, double maxforce,float food, float poison);
	void doSteering(point target);
	void eat(std::vector<item>*);
	void draw();
private:
	point m_pos;//pos +=vel
	myvec m_vel;//old acc
	myvec m_acc;//(desired-vel).limit(maxforce) 
	myvec m_desired; //targetpos-locationpos normalize then mult by max speed;
	double m_health;
	float m_foodfactor;
	float m_poisonfactor;
	double m_maxspeed;
	double m_maxforce;
	int m_size=10;

};



#endif // !AGENT_H
