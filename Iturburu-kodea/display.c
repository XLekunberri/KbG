#include "definitions.h"
#include <stdio.h>
#include "matrizeak.h"

/** GLOBAL VARIABLES **/

int kamera = KG_KAM_ORTO;

GLdouble *eye = NULL;
GLdouble *center = NULL;
GLdouble *up = NULL;

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _window_height;
extern GLdouble _window_width;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;
extern int argiztatze_sistema;

extern object3d *_first_object;
extern object3d *_selected_object;

extern char* mezua;

extern camera3d* kam_obj;
extern camera3d* kam_ibil;

extern light3d* argia1;
extern light3d* argia2;
extern light3d* argia3;
extern light3d* argia4;
extern light3d* argia5;

extern int gaituta_1;
extern int gaituta_2;
extern int gaituta_3;
extern int gaituta_4;
extern int gaituta_5;

/**
 * @brief Function to draw the axes
 */
void draw_axes() {
	glTranslatef(0.0, 0.0, 0.0);
    glLineWidth(3.0f);
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE,0,0);
    glVertex3d(-1*KG_MAX_DOUBLE,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,KG_MAX_DOUBLE,0);
    glVertex3d(0,-1*KG_MAX_DOUBLE,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,KG_MAX_DOUBLE);
    glVertex3d(0,0,-1*KG_MAX_DOUBLE);
    glEnd();
    glLineWidth(1.0f);
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    GLdouble window = height-24.0;
    _window_ratio = (GLdouble) width / (GLdouble) window;
    _window_height = (GLdouble) height-24;
    _window_width = (GLdouble) width;

}

void draw_grid(){
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(KG_COL_GRID_R, KG_COL_GRID_G, KG_COL_GRID_B);

    int max_value = 1000;
    for(int i=-max_value; i<max_value; i++){
        //Horizontalak
        glBegin(GL_LINES);
        glVertex3f(-max_value, i, 0.0);
        glVertex3f(max_value, i, 0.0);
        glEnd();

        //Bertikalak
        glBegin(GL_LINES);
        glVertex3f(i, -max_value, 0.0);
        glVertex3f(i, max_value, 0.0);
        glEnd();
    }
    glFlush();

}

void kokatuKamera(GLdouble *eye, GLdouble *center, GLdouble *up){
    switch(kamera){
        case KG_KAM_OBJ:

            gluLookAt(eye[0],       eye[1],       eye[2],
                      center[0],    center[1],    center[2],
                      up[0],        up[1],        up[2]);
            break;
        case KG_KAM_IBIL:
            gluLookAt(eye[0],       eye[1],       eye[2],
                      center[0],    center[1],    center[2],
                      up[0],        up[1],        up[2]);
            break;
        default:
            break;
    }
}

void pantailaratu(char* string){
    char *c;
    glColor3f(KG_COL_TEXT_R,KG_COL_TEXT_G,KG_COL_TEXT_B);
    glRasterPos2f(KG_POS_TEXT_X, KG_POS_TEXT_Y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

}

void argiaPantailaratu(light3d *argia, GLenum GL_LIGHTi) {
    glLoadIdentity();
    //TODO
    if(kamera != KG_KAM_ORTO) {
        kokatuKamera(eye, center, up);
    }
    glMultMatrixd(argia->pila_z->matrix);

    switch (argia->mota){
        case KG_EGUZKI:
            glLightfv(GL_LIGHTi, GL_POSITION, argia->norabide_eguzki);
            glLightf(GL_LIGHTi, GL_SPOT_CUTOFF, 180.0);
            break;
        case KG_BONBILA:
            glLightfv(GL_LIGHTi, GL_POSITION, argia->coord_bonbila);
            glLightf(GL_LIGHTi, GL_SPOT_CUTOFF, 180.0);
            break;
        case KG_FOKO:
            glLightfv(GL_LIGHTi, GL_POSITION, argia->coord_foko);
            glLightfv(GL_LIGHTi, GL_SPOT_DIRECTION, argia->norabide_foko);
            glLightf(GL_LIGHTi, GL_SPOT_CUTOFF, argia->ang_foko);
            glLightf(GL_LIGHTi, GL_SPOT_EXPONENT, 1.0);
            break;
        default:
            break;
    }
}

void argiakPantailaratu(){
    //GLfloat  horia  [4] = {0.5, 0.5, 0.5,  1.0};
    //GLfloat  grisa  [4] = {0.2, 0.2, 0.2,  1.0};
    GLfloat  txuria  [4] = {1.0, 1.0, 1.0,  1.0};

    glLightfv (GL_LIGHT0 , GL_AMBIENT , txuria );
    glLightfv (GL_LIGHT0 , GL_DIFFUSE , txuria );
    glLightfv (GL_LIGHT0 , GL_SPECULAR , txuria );

    glLightf (GL_LIGHT0 , GL_CONSTANT_ATTENUATION , 0.1);
    glLightf (GL_LIGHT0 , GL_LINEAR_ATTENUATION , 0.0);
    glLightf (GL_LIGHT0 , GL_QUADRATIC_ATTENUATION , 0.1);

    glLightfv (GL_LIGHT1 , GL_AMBIENT , txuria );
    glLightfv (GL_LIGHT1 , GL_DIFFUSE , txuria );
    glLightfv (GL_LIGHT1 , GL_SPECULAR , txuria );

    glLightf (GL_LIGHT1 , GL_CONSTANT_ATTENUATION , 0.1);
    glLightf (GL_LIGHT1 , GL_LINEAR_ATTENUATION , 0.0);
    glLightf (GL_LIGHT1 , GL_QUADRATIC_ATTENUATION , 0.1);

    glLightfv (GL_LIGHT2 , GL_AMBIENT , txuria );
    glLightfv (GL_LIGHT2 , GL_DIFFUSE , txuria );
    glLightfv (GL_LIGHT2 , GL_SPECULAR , txuria );

    glLightf (GL_LIGHT2 , GL_CONSTANT_ATTENUATION , 0.1);
    glLightf (GL_LIGHT2 , GL_LINEAR_ATTENUATION , 0.0);
    glLightf (GL_LIGHT2 , GL_QUADRATIC_ATTENUATION , 0.1);

    glLightfv (GL_LIGHT3 , GL_AMBIENT , txuria );
    glLightfv (GL_LIGHT3 , GL_DIFFUSE , txuria );
    glLightfv (GL_LIGHT3 , GL_SPECULAR , txuria );

    glLightf (GL_LIGHT3 , GL_CONSTANT_ATTENUATION , 0.1);
    glLightf (GL_LIGHT3 , GL_LINEAR_ATTENUATION , 0.0);
    glLightf (GL_LIGHT3 , GL_QUADRATIC_ATTENUATION , 0.1);

    glLightfv (GL_LIGHT4 , GL_AMBIENT , txuria );
    glLightfv (GL_LIGHT4 , GL_DIFFUSE , txuria );
    glLightfv (GL_LIGHT4 , GL_SPECULAR , txuria );

    glLightf (GL_LIGHT4 , GL_CONSTANT_ATTENUATION , 0.1);
    glLightf (GL_LIGHT4 , GL_LINEAR_ATTENUATION , 0.0);
    glLightf (GL_LIGHT4 , GL_QUADRATIC_ATTENUATION , 0.1);


    if(gaituta_1 == KG_GAITUTA){
        argiaPantailaratu(argia1, GL_LIGHT0);
        glEnable(GL_LIGHT0);
    }
    else{
        glDisable(GL_LIGHT0);
    }
    if(gaituta_2 == KG_GAITUTA){
        argiaPantailaratu(argia2, GL_LIGHT1);
        glEnable(GL_LIGHT1);
    }
    else{
        glDisable(GL_LIGHT1);
    }
    if(gaituta_3 == KG_GAITUTA){
        argiaPantailaratu(argia3, GL_LIGHT2);
        glEnable(GL_LIGHT2);
    }
    else{
        glDisable(GL_LIGHT2);
    }
    if(gaituta_4 == KG_GAITUTA){
        argiaPantailaratu(argia4, GL_LIGHT3);
        glEnable(GL_LIGHT3);
    }
    else{
        glDisable(GL_LIGHT3);
    }
    if(gaituta_5 == KG_GAITUTA){
        argiaPantailaratu(argia5, GL_LIGHT4);
        glEnable(GL_LIGHT4);
    }
    else{
        glDisable(GL_LIGHT4);
    }
}

/**
 * @brief Callback display function
 */
void display(void) {
    glViewport(0, 24, (GLsizei) _window_width, (GLsizei) _window_height);
    if(argiztatze_sistema == KG_AMATATUTA) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */

    switch(kamera){
        case KG_KAM_ORTO:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
                /* New width */
                GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
                /* Midpoint in the X axis */
                GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
                /*Definition of the projection*/
                glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
            } else {/* In the opposite situation we extend the Y axis */
                /* New height */
                GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
                /* Midpoint in the Y axis */
                GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
                /*Definition of the projection*/
                glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
            }
            break;

        case KG_KAM_OBJ:

            eye = multBek(kam_obj->pila_z->matrix, kam_obj->eye);
            center = multBek(kam_obj->pila_z->matrix, kam_obj->center);
            up = multBek(kam_obj->pila_z->matrix, kam_obj->up);

            //kokatuKamera(eye, center, up);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(KG_KAM_FOV,_window_ratio,KG_KAM_N,KG_KAM_F);
            break;

        case KG_KAM_IBIL:

            eye = multBek(kam_ibil->pila_z->matrix, kam_ibil->eye);
            center = multBek(kam_ibil->pila_z->matrix, kam_ibil->center);
            up = multBek(kam_ibil->pila_z->matrix, kam_ibil->up);

            //kokatuKamera(eye, center, up);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(KG_KAM_FOV,_window_ratio,KG_KAM_N,KG_KAM_F);
            break;
        default:
            break;
    }

    /* Now we start drawing the object */
	glPushMatrix();
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    if(kamera != KG_KAM_ORTO) {
        kokatuKamera(eye, center, up);
    }

    /*First, we draw the grid and then the axes*/
    if(argiztatze_sistema == KG_PIZTUTA){
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
    }
    glDisable(GL_DEPTH_TEST);
    draw_grid();
    draw_axes();
    glEnable(GL_DEPTH_TEST);
    if(argiztatze_sistema == KG_PIZTUTA){
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
    }

	glPopMatrix();

    argiakPantailaratu();



    /*Now each of the objects in the list*/
    if(argiztatze_sistema == KG_PIZTUTA){
        glDisable(GL_COLOR_MATERIAL);
    }
    GLfloat ambient_selected [4] = {0.0215, 0.1745,	0.0215, 1.0};
    GLfloat diffuse_selected [4] = {0.07568, 0.61424, 0.07568, 1.0};
    GLfloat specular_selected [4] = {0.633,	0.727811, 0.633, 1.0};
    GLfloat shininess_selected = 0.8;

    GLfloat ambient_nonselected [4] = {0.25, 0.20725, 0.20725, 1.0};
    GLfloat diffuse_nonselected [4] = {1, 0.829, 0.829, 1.0};
    GLfloat specular_nonselected [4] = {0.296648, 0.296648, 0.296648, 1.0};
    GLfloat shininess_nonselected = 0.088;
    while (aux_obj != 0) {


        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            if(argiztatze_sistema == KG_PIZTUTA) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_selected);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_selected);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_selected);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_selected);
            }
            else {
                glColor3f(KG_COL_SELECTED_R, KG_COL_SELECTED_G, KG_COL_SELECTED_B);
            }
        }
        else{
            if(argiztatze_sistema == KG_PIZTUTA) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_nonselected);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_nonselected);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_nonselected);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_nonselected);
            }
            else {
                glColor3f(KG_COL_NONSELECTED_R, KG_COL_NONSELECTED_G, KG_COL_NONSELECTED_B);
            }
        }

        /* Draw the object; fFFor each face create a new polygon with the corresponding vertices */
        glLoadIdentity();
        if(kamera != KG_KAM_ORTO) {
            kokatuKamera(eye, center, up);
        }

        glMultMatrixd(aux_obj->pila_z->matrix);
        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {

                v_index = aux_obj->face_table[f].vertex_table[v];

                glNormal3d(aux_obj->vertex_table[v_index].normala->x,
                           aux_obj->vertex_table[v_index].normala->y,
                           aux_obj->vertex_table[v_index].normala->z);

                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);



            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }

    if(argiztatze_sistema == KG_PIZTUTA){
        glEnable(GL_COLOR_MATERIAL);
    }


    /*Make the viewport*/
    if(argiztatze_sistema == KG_PIZTUTA){
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
    }

    glLoadIdentity();
    glViewport(0,0, (GLsizei) _window_width, 24);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(argiztatze_sistema == KG_AMATATUTA) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glColor3d(1,1,1);
    glBegin(GL_QUADS);
    glVertex2d(-1,-1);
    glVertex2d( 1,-1);
    glVertex2d( 1, 1);
    glVertex2d(-1, 1);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    /*Print at the viewport*/
    pantailaratu(mezua);
    mezua[0] = '\0';
    glEnable(GL_DEPTH_TEST);

    if(argiztatze_sistema == KG_PIZTUTA){
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
    }

    /*Do the actual drawing*/
    glFlush();
}


