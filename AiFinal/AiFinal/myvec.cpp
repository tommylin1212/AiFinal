#include "myvec.h"

using namespace std;

myvec::myvec() {
	m_length = -1;
}
myvec::myvec(GLdouble x, GLdouble y) {
	m_x = x;
	m_y = y;
	m_length = sqrt((x*x) + (y*y));
}
GLdouble myvec::dprod(myvec other) {
	return (m_x*other.m_x) + (m_y*other.m_y);
}
myvec myvec::sprod(GLdouble s) {
	return myvec(m_x*s, m_y*s);
}
myvec myvec::add(myvec a) {
	return myvec(m_x + a.m_x, m_y + a.m_y);
}
myvec myvec::sub(myvec a) {
	return myvec(m_x - a.m_x, m_y - a.m_y);
}
myvec myvec::perp() {
	return myvec(-1 * m_y, m_x);
}
myvec myvec::norm() {
	return myvec(m_x, m_y).sprod(1 / m_length);
}