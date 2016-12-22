#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"
#include "matrizeak.h"

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _window_height;
GLdouble _window_width;
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object = 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/

char* mezua;

camera3d* kam_obj;
camera3d* kam_ibil;

light3d* argia1;
light3d* argia2;
light3d* argia3;
light3d* argia4;
light3d* argia5;

int argiztatze_sistema = KG_AMATATUTA;


/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;
	
    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void kamerakHasieratu(){

    /* Hasierako posizioko matrizea egin */
    GLdouble* lag = translazioa(0,0,22);
    GLdouble* has = mult(identitatea(),lag);

    /* Objektu kamera hasieratu */
    kam_obj = (camera3d*)malloc(sizeof(camera3d));

    kam_obj->eye = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_obj->eye[0]=0; kam_obj->eye[1]=0; kam_obj->eye[2]=0; kam_obj->eye[3]=1;

    kam_obj->center = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_obj->center[0]=0; kam_obj->center[1]=0; kam_obj->center[2]=-5; kam_obj->center[3]=1;

    kam_obj->up = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_obj->up[0]=0; kam_obj->up[1]=1; kam_obj->up[2]=0; kam_obj->up[3]=0;

    kam_obj->pila_z = (pila*)malloc(sizeof(pila));
    kam_obj->pila_z->matrix = has;
    kam_obj->pila_z->next   = NULL;
    kam_obj->pila_y = NULL;

    /* Kamera ibiltaria hasieratu */
    kam_ibil = (camera3d*)malloc(sizeof(camera3d));

    kam_ibil->eye = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_ibil->eye[0]=0; kam_ibil->eye[1]=0; kam_ibil->eye[2]=0; kam_ibil->eye[3]=1;

    kam_ibil->center = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_ibil->center[0]=0; kam_ibil->center[1]=0; kam_ibil->center[2]=-5; kam_ibil->center[3]=1;

    kam_ibil->up = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kam_ibil->up[0]=0; kam_ibil->up[1]=1; kam_ibil->up[2]=0; kam_ibil->up[3]=0;

    kam_ibil->pila_z = (pila*)malloc(sizeof(pila));
    kam_ibil->pila_z->matrix = has;
    kam_ibil->pila_z->next   = NULL;
    kam_ibil->pila_y = NULL;

    kam_ibil->angelua = KG_HAS_ANG;
}

void argiaHasieratu(light3d* argia, float zenb){

    //Hasieran argi guztiak eguzkiak izango dira
    argia->mota = KG_EGUZKI;

    //Eguzkia
    argia->norabide_eguzki = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    argia->norabide_eguzki[0] = 0.0f;
    argia->norabide_eguzki[1] = 1.0f;
    argia->norabide_eguzki[2] = 0.0f;
    argia->norabide_eguzki[3] = 0.0f;

    //Bonbila
    argia->coord_bonbila = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    argia->coord_bonbila[0] = 0.0f;
    argia->coord_bonbila[1] = 4.0f + zenb;
    argia->coord_bonbila[2] = 0.0f;
    argia->coord_bonbila[3] = 1.0f;
    
    //Fokoa
    argia->coord_foko = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    argia->coord_foko[0] = 0.0f;
    argia->coord_foko[1] = 0.0f;
    argia->coord_foko[2] = 4.0f + zenb;
    argia->coord_foko[3] = 1.0f;

    argia->norabide_foko = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    argia->norabide_foko[0] = 0.0f;
    argia->norabide_foko[1] = 0.0f;
    argia->norabide_foko[2] = -4.0f;
    argia->norabide_foko[3] = 0.0f;

    argia->ang_foko = KG_FOKO_ANG_DEFAULT;

    GLdouble* lag = translazioa(0,0,4+(int)zenb);
    GLdouble* has = mult(identitatea(),lag);

    argia->pila_z = (pila*)malloc(sizeof(pila));
    argia->pila_z->matrix = has;
    argia->pila_z->next   = NULL;
    argia->pila_y = NULL;
}

void argiakHasieratu() {
    argia1 = (light3d *) malloc(sizeof(light3d));
    argia2 = (light3d *) malloc(sizeof(light3d));
    argia3 = (light3d *) malloc(sizeof(light3d));
    argia4 = (light3d *) malloc(sizeof(light3d));
    argia5 = (light3d *) malloc(sizeof(light3d));

    argiaHasieratu(argia1, (float) KG_ARGIA_1);
    argiaHasieratu(argia2, (float) KG_ARGIA_2);
    argiaHasieratu(argia3, (float) KG_ARGIA_3);
    argiaHasieratu(argia4, (float) KG_ARGIA_4);
    argiaHasieratu(argia5, (float) KG_ARGIA_5);
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    mezua = (char*)malloc(sizeof(char)*1024);
    mezua[0] = '\0';

    // Garbiago egoteko kanpoan eginda
    kamerakHasieratu();
    argiakHasieratu();

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    glEnable(GL_DEPTH_TEST);



    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);



    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}