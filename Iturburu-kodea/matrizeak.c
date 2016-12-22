#include "definitions.h"
#include <GL/glut.h>
#include <stdio.h>

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

GLdouble *multBek(GLdouble *m, GLdouble *v){

    GLdouble *result = (GLdouble*)malloc(sizeof(GLdouble)*4);

    result[0] = m[0]*v[0] + m[4]*v[1] + m[8] *v[2] + m[12]*v[3];
    result[1] = m[1]*v[0] + m[5]*v[1] + m[9] *v[2] + m[13]*v[3];
    result[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
    result[3] = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];

    return (result);
}

GLdouble *translazioa(double x, double y, double z){

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

void print_matrix(GLdouble *matrix){

    for(int i=0; i<16;i=i+4){
        printf("%g\t",(double)matrix[i]);
    }
    printf("\n");
    for(int i=1; i<16;i=i+4){
        printf("%g\t",(double)matrix[i]);
    }
    printf("\n");
    for(int i=2; i<16;i=i+4){
        printf("%g\t",(double)matrix[i]);
    }
    printf("\n");
    for(int i=3; i<16;i=i+4){
        printf("%g\t",(double)matrix[i]);
    }
    printf("\n");
}