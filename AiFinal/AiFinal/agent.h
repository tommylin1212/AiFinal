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
	agent();
	agent(point pos);
	agent(point pos, std::vector<double> dna);
	void doSteering(point target,bool type);
	void reCenter();
	void setPos(point p);
	void eat(std::vector<item>*);
	void setHealth(double h);
	void draw();
	point getPos();
	void health(double);
	double getHealth();
	std::vector<double> getDNA();
	void age(int);
	bool outOfBounds();
	
	int getAge();
protected:
	point m_pos;//pos +=vel
	myvec m_vel;//old acc
	myvec m_acc;//(desired-vel).limit(maxforce) 
	myvec m_desired; //targetpos-locationpos normalize then mult by max speed;
	double m_health;
	double m_maxspeed;
	double m_maxforce;
	int m_size=10;
	int m_counter;
private:
	std::vector<double> m_dna;
	bool m_wandering;
	point m_wander;
	
};

class player : public agent {
public:
	player(point pos);
	void steer(int rln);//left is - right is + nothing is 0
	point deadReckon();
	void doSteering(point pos);
	void draw();
	void eat(std::vector<item>* items);
private:
	double heading;
};





#endif // !AGENT_H
