#ifndef ITEM_H
#define ITEM_H
#include "point.h"
class item {
public:
	item();
	item(point);
	point getPos();
	void draw();
private:
	bool m_type;
	point m_pos;
	
protected:

};



#endif 