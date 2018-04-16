#include "item.h"

item::item(){
	m_type = true;

}

item::item(point pos,bool type){
	m_pos = pos;
	m_type = type;
	//m_type = rand()%2;
}

point item::getPos(){
	return m_pos;
}
bool item::getType()
{
	return m_type;
}
void item::draw() {
	if (!m_type) {
		glColor3f(1.0, 0.5, 0.5);
	}
	else {
		glColor3f(1.0, 1.0, 1.0);
	}
	m_pos.plot();
	glColor3f(1.0, 1.0, 1.0);
}
