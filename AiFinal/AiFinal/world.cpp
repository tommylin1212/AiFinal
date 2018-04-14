#include "world.h"

world::world(){

}

void world::init(int xsize,int ysize, int agents, int food, int poison){
	for (int i = 0; i < agents; i++) {
		m_agents.push_back(agent(point(rand() % xsize, rand() % ysize, 0), 1, 5, 0.5, 1, 1));
	}
	for (int i = 0; i < food + poison; i++) {
		if (i > food) {
			m_items.push_back(item(point(rand() % xsize, rand() % ysize, 0)));//poison
		}
		else {
			m_items.push_back(item(point(rand() % xsize, rand() % ysize, 0)));//food
		}
	}
}

void world::update(){
	for (int i = 0; i < m_agents.size(); i++) {
		m_agents[i].eat(&m_items);
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
