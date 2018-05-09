#ifndef WORLD_H
#define WOLRD_H
#include <vector>
#include "agent.h"
#include "item.h"
class world {
public:
	world();
	void init(int xsize, int ysize, int agents, int food, int poison);
	void init(int,int,int);
	void update();
	void draw();
	void playerWin();
	void playerLost();
	void doGame();
	void getPlayer(player* play);
private:
	std::vector<agent> m_agents;
	std::vector<item> m_items;
	int level;
	std::vector<player*>players;
	int m_xsize;
	int m_ysize;
	int m_asize;
	int m_food;
	int m_poison;
protected:

};



#endif 