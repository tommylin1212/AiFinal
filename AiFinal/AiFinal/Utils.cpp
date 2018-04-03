#include "globalgl.h"
#include "Utils.h"
#include <fstream>
#include <ctime>

using namespace std;

void setWorldWin(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewPort(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}