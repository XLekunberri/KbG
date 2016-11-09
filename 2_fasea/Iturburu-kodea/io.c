#include "definitions.h"
#include "load_obj.h"
#include "matrizeak.h"
#include <malloc.h>
#include <GL/glut.h>
#include <stdio.h>


extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

int err_sist = MODE_GLOBAL; // MODE_GLOBAL
                            // MODE_LOKAL

int aldaketa = -1;	// translazioa = 0
				    // biraketa = 1
                    // tamaina aldatzea = 2


/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){

    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n\n");
	
	printf("ALDAKETA FUNTZIOAK \n");
	printf("<M,m>\t\t Translazioa aktibatu \n");
	printf("<B,b>\t\t Biraketa aktibatu \n");
	printf("<T,t>\t\t Tamaina aldaketa aktibatu \n");
	printf("<G,g>\t\t Aldaketa globalak aktibatu \n");
	printf("<L,l>\t\t Aldaketa lokalak aktibatu \n");
	printf("<O,o>\t\t Translazioa aktibatu \n");
	printf("<GORA>\t\t Mugitu +Y; Txikitu Y; Biratu +X \n");
	printf("<BEHERA>\t Mugitu -Y; Handitu Y; Biratu -X \n");
	printf("<ESKUINA>\t Mugitu +X; Txikitu X; Biratu +Y \n");
	printf("<EZKERRA>\t Mugitu -X; Handitu X; Biratu -Y \n");
	printf("<AVPAG>\t\t Mugitu +Z; Txikitu Z; Biratu +Z \n");
	printf("<REPAG>\t\t Mugitu -Z; Handitu Z; Biratu -Z \n");
	printf("<+>\t\t\t Objektua ardatz guztietan handitu \n");
	printf("<->\t\t\t Objektua ardatz guztietan txikitu \n");
	printf("<CTRL + (Z,z)>\t\t Aldaketak desegin \n");
    printf("\n\n");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;
	
	printf("%d %c\n", key, key);
	
    switch (key) {
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            //Batzuetan, 'F' sakatu beharrean beste konbinazio-tekla bat sakatuz nahi gabe, bufferrean aurretik sartutakoa gordeta geratzen da
            //Honen ondorioz, programak ez du objektuaren helbidea zuzen hartzen.
            //fflush() funtzioa erabiliz STDIN "garbituko" dugu.
            fflush( stdin );
            scanf("%s", fname);
            /*Allocate memory for the structure and read the file*/
            auxiliar_object = (object3d *) malloc(sizeof (object3d));
            read = read_wavefront(fname, auxiliar_object);
            switch (read) {
            /*Errors in the reading*/
            case 1:
                printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
                break;
            case 2:
                printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
                break;
            case 3:
                printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
                break;
            /*Read OK*/
            case 0:
                /*Insert the new object in the list*/
                auxiliar_object->next = _first_object;
                _first_object = auxiliar_object;
                _selected_object = _first_object;
                printf("%s\n",KG_MSSG_FILEREAD);
                break;
            }
            break;

        case 9: /* <TAB> */
            //if hau gehitu dugu, programaren hasieran lista hutsa dagoenez ezin delako objektuen lista zeharkatu
            //Bestela, 'segmentation fault' errorea emango luke
            if (_first_object == 0){
                printf("Ezin da aukeratutako objektua aldatu, oraindik ez delako objekturik kargatu\n");
            }
            else{
                _selected_object = _selected_object->next;
                /*The selection is circular, thus if we move out of the list we go back to the first element*/
                if (_selected_object == 0) _selected_object = _first_object;
            }
            break;

        case 127: /* <SUPR> */
            //if hau gehitu dugu, ez badaudelako objekturik kargatuta eta aukeratutakoa ezabatzen saiatzen bagara, "Segmentation Fault" errorea jaurtitzen du
            //Horretarako, _selected_object (kargatuta dagoen aukeratutako objektua) '0' balioa duenean, errore-mezua pantailaratuko da
            if (_selected_object == 0){
                printf("Ezin da objekturik ezabatu ez dagoelako bat ere ez kargatuta\n");
            }
            else{
                /*Erasing an object depends on whether it is the first one or not*/
                if (_selected_object == _first_object)
                {
                    /*To remove the first object we just set the first as the current's next*/
                    _first_object = _first_object->next;
                    /*Once updated the pointer to the first object it is save to free the memory*/
                    free(_selected_object);
                    /*Finally, set the selected to the new first one*/
                    _selected_object = _first_object;
                } else {
                    /*In this case we need to get the previous element to the one we want to erase*/
                    auxiliar_object = _first_object;
                    while (auxiliar_object->next != _selected_object)
                        auxiliar_object = auxiliar_object->next;
                    /*Now we bypass the element to erase*/
                    auxiliar_object->next = _selected_object->next;
                    /*free the memory*/
                    free(_selected_object);
                    /*and update the selection*/
                    _selected_object = auxiliar_object;
                }
            }
            break;

        case '-':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Increase the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            break;

        case '+':
            //INPLEMENTA EZAZU CTRL + + KONBINAZIOAREN FUNTZIOANLITATEA
            //'Ctrl' + '-' kasuaren ia berdina, bakarrik aldatzen dena da
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Decrease the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            break;

        case '?':
            print_help();
            break;

        case 27: /* <ESC> */
            exit(0);
            break;

        case 'm':
        case 'M':
            if(aldaketa != MODE_TRANS) {
                printf("Translazioa aktibatuta\n");
                aldaketa = MODE_TRANS;
            }
            break;

        case 'b':
        case 'B':
            printf("Biraketa aktibatuta\n");
            aldaketa = MODE_BIRAK;
            break;

        case 't':
        case 'T':
            printf("Tamaina aldatzea aktibatuta\n");
            aldaketa = MODE_ESKAL;
            break;

        case 'g':
        case 'G':
            if(err_sist != MODE_GLOBAL){
                printf("Erreferentzi sistema globala aktibatuta\n");
                err_sist = MODE_GLOBAL;
            }
            break;

        case 'l':
        case 'L':
            if(err_sist != MODE_LOKAL){
                printf("Erreferentzi sistema lokala aktibatuta\n");
                err_sist = MODE_LOKAL;
            }
            break;

        case 'o':
        case 'O':
            break;

        case 'z':
        case 'Z':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){

            }
            break;

        default:
            /*In the default case we just print the code of the key. This is usefull to define new cases*/
            printf("Normala: %d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}


void special_keyboard(int key, int x, int y) {
    GLdouble *mat = NULL;
    glPushMatrix();
    if (aldaketa == -1) {
        printf("Aukeratu transformazio bat\n");
    }
    else{
        switch (key) {
            case GLUT_KEY_UP:
                printf("y+\n");
                switch (aldaketa) {
                    case MODE_TRANS://Trans
                        mat = translazioa(0, 1, 0);
                        break;
                    case MODE_BIRAK://Birak
                        mat = biraketa(0, 1, 0);
                        break;
                    case MODE_ESKAL://Eskal
                        mat = eskalaketa(1, KG_ESKAL_HAND, 1);
                        break;
                }
                break;
            case GLUT_KEY_DOWN:
                printf("y-\n");
                switch (aldaketa) {
                    case MODE_TRANS:
                        mat = translazioa(0, -1, 0);
                        break;
                    case MODE_BIRAK:
                        mat = biraketa(0, -1, 0);
                        break;
                    case MODE_ESKAL:
                        mat = eskalaketa(1, KG_ESKAL_TXIK, 1);
                        break;
                }
                break;

            case GLUT_KEY_RIGHT:
                printf("x+\n");
                switch (aldaketa) {
                    case MODE_TRANS:
                        mat = translazioa(1, 0, 0);
                        break;
                    case MODE_BIRAK:
                        mat = biraketa(1, 0, 0);
                        break;
                    case MODE_ESKAL:
                        mat = eskalaketa(KG_ESKAL_HAND, 1, 1);
                        break;
                }
                break;

            case GLUT_KEY_LEFT:
                printf("x-\n");
                switch (aldaketa) {
                    case MODE_TRANS:
                        mat = translazioa(-1, 0, 0);
                        break;
                    case MODE_BIRAK:
                        mat = biraketa(-1, 0, 0);
                        break;
                    case MODE_ESKAL:
                        mat = eskalaketa(KG_ESKAL_TXIK, 1, 1);
                        break;
                }
                break;

            case GLUT_KEY_PAGE_UP: //av_pag
                printf("z+\n");
                switch (aldaketa) {
                    case MODE_TRANS:
                        mat = translazioa(0, 0, 1);
                        break;
                    case MODE_BIRAK:
                        mat = biraketa(0, 0, 1);
                        break;
                    case MODE_ESKAL:
                        mat = eskalaketa(1, 1, KG_ESKAL_HAND);
                        break;
                }
                break;

            case GLUT_KEY_PAGE_DOWN: //re_pag
                printf("z-\n");
                switch (aldaketa) {
                    case MODE_TRANS:
                        mat = translazioa(0, 0, -1);
                        break;
                    case MODE_BIRAK:
                        mat = biraketa(0, 0, -1);
                        break;
                    case MODE_ESKAL:
                        mat = eskalaketa(1, 1, KG_ESKAL_TXIK);
                        break;
                }
                break;
            default:
                printf("Espeziala: %d %c\n", key, key);
                break;
        }
    }
	if (_selected_object != 0 && mat != NULL) {
        switch(err_sist) {
            case MODE_GLOBAL:
                _selected_object->matrix = mult(mat, _selected_object->matrix);
                break;
            case MODE_LOKAL:
                _selected_object->matrix = mult(_selected_object->matrix, mat);
                break;

        }
	}
	

	glutPostRedisplay();
	glPopMatrix();
}