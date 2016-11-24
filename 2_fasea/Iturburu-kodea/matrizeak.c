#include "definitions.h"
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

GLdouble *mult(GLdouble *m1, GLdouble *m2) {
    GLdouble *result = malloc(sizeof(GLdouble) * 4 * 4);
    // @formatter:off
    result[0 + 4* 0] = m1[0 + 4* 0] * m2[0 + 4* 0] + m1[0 + 4* 1] * m2[1 + 4* 0] + m1[0 + 4* 2] * m2[2 + 4* 0] + m1[0 + 4* 3] * m2[3 + 4* 0];
    result[1 + 4* 0] = m1[1 + 4* 0] * m2[0 + 4* 0] + m1[1 + 4* 1] * m2[1 + 4* 0] + m1[1 + 4* 2] * m2[2 + 4* 0] + m1[1 + 4* 3] * m2[3 + 4* 0];
    result[2 + 4* 0] = m1[2 + 4* 0] * m2[0 + 4* 0] + m1[2 + 4* 1] * m2[1 + 4* 0] + m1[2 + 4* 2] * m2[2 + 4* 0] + m1[2 + 4* 3] * m2[3 + 4* 0];
    result[3 + 4* 0] = m1[3 + 4* 0] * m2[0 + 4* 0] + m1[3 + 4* 1] * m2[1 + 4* 0] + m1[3 + 4* 2] * m2[2 + 4* 0] + m1[3 + 4* 3] * m2[3 + 4* 0];

    result[0 + 4* 1] = m1[0 + 4* 0] * m2[0 + 4* 1] + m1[0 + 4* 1] * m2[1 + 4* 1] + m1[0 + 4* 2] * m2[2 + 4* 1] + m1[0 + 4* 3] * m2[3 + 4* 1];
    result[1 + 4* 1] = m1[1 + 4* 0] * m2[0 + 4* 1] + m1[1 + 4* 1] * m2[1 + 4* 1] + m1[1 + 4* 2] * m2[2 + 4* 1] + m1[1 + 4* 3] * m2[3 + 4* 1];
    result[2 + 4* 1] = m1[2 + 4* 0] * m2[0 + 4* 1] + m1[2 + 4* 1] * m2[1 + 4* 1] + m1[2 + 4* 2] * m2[2 + 4* 1] + m1[2 + 4* 3] * m2[3 + 4* 1];
    result[3 + 4* 1] = m1[3 + 4* 0] * m2[0 + 4* 1] + m1[3 + 4* 1] * m2[1 + 4* 1] + m1[3 + 4* 2] * m2[2 + 4* 1] + m1[3 + 4* 3] * m2[3 + 4* 1];

    result[0 + 4* 2] = m1[0 + 4* 0] * m2[0 + 4* 2] + m1[0 + 4* 1] * m2[1 + 4* 2] + m1[0 + 4* 2] * m2[2 + 4* 2] + m1[0 + 4* 3] * m2[3 + 4* 2];
    result[1 + 4* 2] = m1[1 + 4* 0] * m2[0 + 4* 2] + m1[1 + 4* 1] * m2[1 + 4* 2] + m1[1 + 4* 2] * m2[2 + 4* 2] + m1[1 + 4* 3] * m2[3 + 4* 2];
    result[2 + 4* 2] = m1[2 + 4* 0] * m2[0 + 4* 2] + m1[2 + 4* 1] * m2[1 + 4* 2] + m1[2 + 4* 2] * m2[2 + 4* 2] + m1[2 + 4* 3] * m2[3 + 4* 2];
    result[3 + 4* 2] = m1[3 + 4* 0] * m2[0 + 4* 2] + m1[3 + 4* 1] * m2[1 + 4* 2] + m1[3 + 4* 2] * m2[2 + 4* 2] + m1[3 + 4* 3] * m2[3 + 4* 2];

    result[0 + 4* 3] = m1[0 + 4* 0] * m2[0 + 4* 3] + m1[0 + 4* 1] * m2[1 + 4* 3] + m1[0 + 4* 2] * m2[2 + 4* 3] + m1[0 + 4* 3] * m2[3 + 4* 3];
    result[1 + 4* 3] = m1[1 + 4* 0] * m2[0 + 4* 3] + m1[1 + 4* 1] * m2[1 + 4* 3] + m1[1 + 4* 2] * m2[2 + 4* 3] + m1[1 + 4* 3] * m2[3 + 4* 3];
    result[2 + 4* 3] = m1[2 + 4* 0] * m2[0 + 4* 3] + m1[2 + 4* 1] * m2[1 + 4* 3] + m1[2 + 4* 2] * m2[2 + 4* 3] + m1[2 + 4* 3] * m2[3 + 4* 3];
    result[3 + 4* 3] = m1[3 + 4* 0] * m2[0 + 4* 3] + m1[3 + 4* 1] * m2[1 + 4* 3] + m1[3 + 4* 2] * m2[2 + 4* 3] + m1[3 + 4* 3] * m2[3 + 4* 3];
    // @formatter:on
    return result;
}

GLdouble *translazioa(int x, int y, int z){

    GLdouble *mat = (GLdouble*)malloc(sizeof(GLdouble) * 4 * 4);

    mat[0] = 1;     mat[4] = 0;     mat[8]  = 0;    mat[12] = x * KG_TRANS_ABIAD;
    mat[1] = 0;     mat[5] = 1;     mat[9]  = 0;    mat[13] = y * KG_TRANS_ABIAD;
    mat[2] = 0;     mat[6] = 0;     mat[10] = 1;    mat[14] = z * KG_TRANS_ABIAD;
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0;    mat[15] = 1;

    return mat;

}

GLdouble *biraketa(int x, int y, int z){

    GLdouble *mat = (GLdouble*)malloc(sizeof(GLdouble) * 4 * 4);
    double c = cos(KG_BIRAK_ANG);
    double s = sin(KG_BIRAK_ANG);

    mat[0] = x * x * (1-c) + c;     mat[4] = x * y * (1-c) - z*s;   mat[8]  = x * z * (1-c) + y*s;  mat[12] = 0;
    mat[1] = x * y * (1-c) + z*s;   mat[5] = y * y * (1-c) + c;     mat[9]  = y * z * (1-c) - x*s;  mat[13] = 0;
    mat[2] = x * z * (1-c) - y*s;   mat[6] = y * z * (1-c) + x*s;   mat[10] = z * z * (1-c) + c;    mat[14] = 0;
    mat[3] = 0;                     mat[7] = 0;                     mat[11] = 0;                    mat[15] = 1;

    return mat;

}

GLdouble *eskalaketa(float x, float y, float z){

    GLdouble *mat = (GLdouble*)malloc(sizeof(GLdouble) * 4 * 4);

    mat[0] = x;     mat[4] = 0;     mat[8]  = 0;      mat[12] = 0;
    mat[1] = 0;     mat[5] = y;     mat[9]  = 0;      mat[13] = 0;
    mat[2] = 0;     mat[6] = 0;     mat[10] = z;      mat[14] = 0;
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0;      mat[15] = 1;

    return mat;
}

GLdouble *islapena(int x, int y, int z){

    GLdouble *mat = (GLdouble*)malloc(sizeof(GLdouble) * 4 * 4);

    mat[0] = x;     mat[4] = 0;     mat[8]  = 0;    mat[12] = 0;
    mat[1] = 0;     mat[5] = y;     mat[9]  = 0;    mat[13] = 0;
    mat[2] = 0;     mat[6] = 0;     mat[10] = z;    mat[14] = 0;
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0;    mat[15] = 1;

    return mat;
}

GLdouble *identitatea(){

    GLdouble *mat = (GLdouble*)malloc(sizeof(GLdouble) * 4 * 4);

    mat[0] = 1;     mat[4] = 0;     mat[8]  = 0;    mat[12] = 0;
    mat[1] = 0;     mat[5] = 1;     mat[9]  = 0;    mat[13] = 0;
    mat[2] = 0;     mat[6] = 0;     mat[10] = 1;    mat[14] = 0;
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0;    mat[15] = 1;

    return mat;
}
