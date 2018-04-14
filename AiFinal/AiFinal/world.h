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
private:
	std::vector<agent> m_agents;
	std::vector<item> m_items;
protected:

};



#endif 