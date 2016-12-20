#include "definitions.h"
#include <stdio.h>
#include "matrizeak.h"

/** GLOBAL VARIABLES **/

int kamera = KG_KAM_ORTO;

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

/**
 * @brief Function to draw the axes
 */
void draw_axes() {
	glTranslatef(0.0, 0.0, 0.0);
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
    printf("eye\n");
    print_vector(eye);
    printf("center\n");
    print_vector(center);
    printf("up\n");
    print_vector(up);
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

/**
 * @brief Callback display function
 */
void display(void) {
    glViewport(0, 24, (GLsizei) _window_width, (GLsizei) _window_height);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */
    GLdouble *eye = NULL;
    GLdouble *center = NULL;
    GLdouble *up = NULL;

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

            printf("eye:\n");
            print_vector(eye);
            printf("center:\n");
            print_vector(center);
            printf("up:\n");
            print_vector(up);
            //sprintf(mezua, "center: %f %f %f\tup: %f %f %f", center[0], center[1],center[2], up[0], up[1], up[2]);

            //kokatuKamera(eye, center, up);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(KG_KAM_FOV,_window_ratio,KG_KAM_N,KG_KAM_F);
            break;
        default:
            break;
    }

    GLfloat  horia  [4] = {0.0, 1.0, 1.0,  1.0};
    GLfloat  grisa  [4] = {0.2, 0.2, 0.2,  1.0};
    GLfloat  txuria  [4] = {1.0, 1.0, 1.0,  1.0};
    glLightfv (GL_LIGHT0 , GL_AMBIENT , grisa );
    glLightfv (GL_LIGHT0 , GL_DIFFUSE , horia );
    glLightfv (GL_LIGHT0 , GL_SPECULAR , txuria );

    glLightfv (GL_LIGHT1 , GL_AMBIENT , grisa );
    glLightfv (GL_LIGHT1 , GL_DIFFUSE , horia );
    glLightfv (GL_LIGHT1 , GL_SPECULAR , txuria );

    glLightfv (GL_LIGHT2 , GL_AMBIENT , grisa );
    glLightfv (GL_LIGHT2 , GL_DIFFUSE , horia );
    glLightfv (GL_LIGHT2 , GL_SPECULAR , txuria );

    glLightfv (GL_LIGHT3 , GL_AMBIENT , grisa );
    glLightfv (GL_LIGHT3 , GL_DIFFUSE , horia );
    glLightfv (GL_LIGHT3 , GL_SPECULAR , txuria );

    glLightfv (GL_LIGHT4 , GL_AMBIENT , grisa );
    glLightfv (GL_LIGHT4 , GL_DIFFUSE , horia );
    glLightfv (GL_LIGHT4 , GL_SPECULAR , txuria );

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
    }
    glDisable(GL_DEPTH_TEST);
    draw_grid();
    draw_axes();
    glEnable(GL_DEPTH_TEST);
    if(argiztatze_sistema == KG_PIZTUTA){
        glEnable(GL_LIGHTING);
    }

	glPopMatrix();


    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
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
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);

                glNormal3d(aux_obj->vertex_table[v_index].normala.x,
                           aux_obj->vertex_table[v_index].normala.y,
                           aux_obj->vertex_table[v_index].normala.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }

    /*



    /*Make the viewport*/
    if(argiztatze_sistema == KG_PIZTUTA){
        glDisable(GL_LIGHTING);
    }

    glLoadIdentity();
    glViewport(0,0, (GLsizei) _window_width, 24);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
    }

    /*Do the actual drawing*/
    glFlush();
}

