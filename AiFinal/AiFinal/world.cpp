#include "world.h"

world::world(){
	level = 0;
}

void world::init(int xsize,int ysize, int agents, int food, int poison){
	m_xsize = xsize;
	m_ysize = ysize;
	m_asize = agents;
	m_food = food;
	m_poison = poison;
	if (level == 10) {
		playerWin();
	}
	else {
		for (int i = 0; i < agents; i++) {
			m_agents.push_back(agent(point((rand() % (xsize - 200)) + 100, (rand() % (ysize - 200)) + 100, 0)));
		}
		for (int i = 0; i < food + poison; i++) {
			if (i > food) {
				m_items.push_back(item(point((rand() % (xsize - 200)) + 100, (rand() % (ysize - 200)) + 100, 0), false));//poison
			}
			else {
				m_items.push_back(item(point((rand() % (xsize - 200)) + 100, (rand() % (ysize - 200)) + 100, 0), true));//food
			}
		}
		level++;
	}
}

void world::update(){
	int reproduce = 15-level;
	if (m_agents.size()>0) {
		for (int i = 0; i < players.size(); i++) {
			players[i]->eat(&m_items);
		}
		for (int i = 0; i < m_agents.size(); i++) {
			if (m_items.size() < 1000) {
				if (rand() % 40 == 0) {
					m_items.push_back(item(point((rand() % (glutGet(GLUT_WINDOW_WIDTH)-200))+100, (rand() % (glutGet(GLUT_WINDOW_HEIGHT) - 200)) + 100, 0), true));//food
				}
				if (rand() % 300 == 0) {
					m_items.push_back(item(point((rand() % (glutGet(GLUT_WINDOW_WIDTH) - 200)) + 100, (rand() % (glutGet(GLUT_WINDOW_HEIGHT) - 200)) + 100, 0), false));//poison
				}
			}
			if (m_agents[i].getHealth() > 0) {
				
				if (m_agents[i].getAge() == reproduce) {
					m_agents.push_back(agent(m_agents[i].getPos(),m_agents[i].getDNA()));
					m_agents[i].age(-reproduce);
				}
				m_agents[i].eat(&m_items);
				m_agents[i].health(-0.005);//decaying health
			}
			else {
				m_items.push_back(item(m_agents[i].getPos(), true));//food
				m_agents.erase(m_agents.begin() + i);
			}
		}
	}
	else {
		init(m_xsize, m_ysize, m_asize+10, m_food+10, m_poison+10);
	}
}

void world::draw(){
	for (int i = 0; i < players.size(); i++) {
		players[i]->draw();
	}
	for (int i = 0; i < m_items.size(); i++) {
		m_items[i].draw();
	}
	for (int i = 0; i < m_agents.size(); i++) {
		m_agents[i].draw();
	}
}

void world::playerWin(){
	//do something
}

void world::getPlayer(player * play){
	players.push_back(play);
}
