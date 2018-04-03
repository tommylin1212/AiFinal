#ifndef HELP_H
#define HELP_H
#include "Utils.h"
#include "globalgl.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

void myResize(GLint, GLint);
void timer(int value);
void myInit(int, int);

void myMouseFun(int button, int state, int x, int y);

void myMouseMotionFun(int x, int y);
void myDisplay();

void myKeyFun(unsigned char key, int x, int y);

#endif