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
	agent(point pos);
	agent(point pos, std::vector<double> dna);
	void doSteering(point target,bool type);
	void eat(std::vector<item>*);
	void draw();
	point getPos();
	void health(double);
	double getHealth();
	std::vector<double> getDNA();
	void age(int);
	int getAge();

private:
	point m_pos;//pos +=vel
	myvec m_vel;//old acc
	myvec m_acc;//(desired-vel).limit(maxforce) 
	myvec m_desired; //targetpos-locationpos normalize then mult by max speed;
	double m_health;
	std::vector<double> m_dna;
	double m_maxspeed;
	double m_maxforce;
	int m_size=10;
	bool m_wandering;
	point m_wander;
	int m_counter;

};



#endif // !AGENT_H
