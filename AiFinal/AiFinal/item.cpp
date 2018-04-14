#include "item.h"

item::item(){
	m_type = true;

}

item::item(point pos){
	m_pos = pos;
	m_type = true;
}

point item::getPos(){
	return m_pos;
}
void item::draw() {
	m_pos.plot();
}
