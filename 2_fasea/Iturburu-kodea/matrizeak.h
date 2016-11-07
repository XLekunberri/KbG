#ifndef ITURBURU_KODEA_MATRIZEAK_H
#define ITURBURU_KODEA_MATRIZEAK_H

#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLdouble *mult(GLdouble *m1, GLdouble *m2);
GLdouble *translazioa(int x, int y, int z);
GLdouble *biraketa(int x, int y, int z);
GLdouble *eskalaketa(int x, int y, int z);

#endif //ITURBURU_KODEA_MATRIZEAK_H
