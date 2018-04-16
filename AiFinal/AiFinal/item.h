#ifndef ITEM_H
#define ITEM_H
#include "point.h"
class item {
public:
	item();
	item(point pos, bool type);
	item(point);
	point getPos();
	bool getType();
	void draw();
private:
	bool m_type;
	point m_pos;
	
protected:

};



#endif 