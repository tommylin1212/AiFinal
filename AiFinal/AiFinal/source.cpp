#include "globalgl.h"
#include "Utils.h"
#include "point.h"
#include "ngon.h"
#include "help.h"
#include <iostream>
#include "myvec.h"
#include <string>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int width = 1280;
int height = 960;
using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Not Ants");
	glutKeyboardFunc(myKeyFun);
	glutDisplayFunc(myDisplay);
	myInit(width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is
	glViewport(0, 0, width, height);
	glutMainLoop();
	return 0;
}     // go into a perpetual loop
