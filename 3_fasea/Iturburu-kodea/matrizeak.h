#ifndef ITURBURU_KODEA_MATRIZEAK_H
#define ITURBURU_KODEA_MATRIZEAK_H

#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLdouble *mult(GLdouble *m1, GLdouble *m2);
GLdouble *multBek(GLdouble *m, GLdouble *v);

GLdouble *translazioa(int x, int y, int z);
GLdouble *biraketa(int x, int y, int z);
GLdouble *eskalaketa(float x, float y, float z);
GLdouble *islapena(int x, int y, int z);
GLdouble *identitatea();

void print_matrix(GLdouble *matrix);
void print_vector(GLdouble *vector);

#endif //ITURBURU_KODEA_MATRIZEAK_H
