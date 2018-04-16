#include "world.h"

world::world(){

}

void world::init(int xsize,int ysize, int agents, int food, int poison){
	for (int i = 0; i < agents; i++) {
		m_agents.push_back(agent(point(rand() % xsize, rand() % ysize, 0)));
	}
	for (int i = 0; i < food + poison; i++) {
		if (i > food) {
			m_items.push_back(item(point(rand() % xsize, rand() % ysize, 0), false));//poison
		}
		else {
			m_items.push_back(item(point(rand() % xsize, rand() % ysize, 0),true));//food
		}
	}
}

void world::update(){
	if (m_agents.size()>0) {
		for (int i = 0; i < m_agents.size(); i++) {
			if (m_items.size() < 1000) {
				if (rand() % 50 == 0) {
					m_items.push_back(item(point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0), true));//food
				}
				if (rand() % 250 == 0) {
					m_items.push_back(item(point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0), false));//poison
				}
			}
			if (m_agents[i].getHealth() > 0) {
				//m_agents[i].age(1);
				if (m_agents[i].getAge() == 10) {
					m_agents.push_back(agent(m_agents[i].getPos(),
						m_agents[i].getDNA()));
					m_agents[i].age(-10);
				}
				m_agents[i].eat(&m_items);
				m_agents[i].health(-0.002);//decaying health
			}
			else {
				m_items.push_back(item(m_agents[i].getPos(), true));//food
				m_agents.erase(m_agents.begin() + i);
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			//m_agents.push_back(agent(point(rand() % glutGet(GLUT_WINDOW_WIDTH), rand() % glutGet(GLUT_WINDOW_HEIGHT), 0)));
		}
	}
}

void world::draw(){
	for (int i = 0; i < m_items.size(); i++) {
		m_items[i].draw();
	}
	for (int i = 0; i < m_agents.size(); i++) {
		m_agents[i].draw();
	}
}
