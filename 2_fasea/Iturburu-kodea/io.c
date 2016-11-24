#include "definitions.h"
#include "load_obj.h"
#include "matrizeak.h"
#include "display.h"
#include <malloc.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

extern char* mezua;

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

int err_sist = MODE_GLOBAL;

int aldaketa = MODE_DEFAULT;


/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){

    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("<I,i>\t\t Objektuaren informazioa pantailaratu\n");
    printf("<Q,q>)\t\t Defektuz dagoen objektua kargau\n\n");
	
	printf("ALDAKETA FUNTZIOAK \n");
	printf("<M,m>\t\t Translazioa aktibatu \n");
	printf("<B,b>\t\t Biraketa aktibatu \n");
	printf("<T,t>\t\t Tamaina aldaketa aktibatu \n");
    printf("<R,r>\t\t Islapena aktibatu \n");
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
            sprintf(mezua, "Objektua kargatuta");
            break;
        case 'q':
        case 'Q':
            fname = QUICK_LOAD;
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
            sprintf(mezua, "al.obj kargatuta");
            break;

        case 9: /* <TAB> */
            //if hau gehitu dugu, programaren hasieran lista hutsa dagoenez ezin delako objektuen lista zeharkatu
            //Bestela, 'segmentation fault' errorea emango luke
            if (_first_object != 0){
                _selected_object = _selected_object->next;
                /*The selection is circular, thus if we move out of the list we go back to the first element*/
                if (_selected_object == 0){
                    _selected_object = _first_object;
                }
                sprintf(mezua, "%s objektua aukeratuta", _selected_object->izena);
            }
            else{
                sprintf(mezua, "Ezin da aukeratutako objektua aldatu, oraindik ez delako objekturik kargatu");
            }
            break;

        case 127: /* <SUPR> */
            //if hau gehitu dugu, ez badaudelako objekturik kargatuta eta aukeratutakoa ezabatzen saiatzen bagara, "Segmentation Fault" errorea jaurtitzen du
            //Horretarako, _selected_object (kargatuta dagoen aukeratutako objektua) '0' balioa duenean, errore-mezua pantailaratuko da
            if (_selected_object != 0){
                /*Erasing an object depends on whether it is the first one or not*/
                if (_selected_object == _first_object)
                {
                    sprintf(mezua, "%s objektua ezabatuta", _first_object->izena);
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
                    sprintf(mezua, "%s objektua ezabatuta", _selected_object->izena);
                    /*free the memory*/
                    free(_selected_object);
                    /*and update the selection*/
                    _selected_object = auxiliar_object;
                }
            }
            else{
                sprintf(mezua, "Ez dago objekturik kargatuta");
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
            sprintf(mezua, "Laguntza terminalean pantailaratu da");
            print_help();
            break;

        case 'i':
        case 'I':
            if (_selected_object != 0) {

                sprintf(mezua, "%s objektuak %d erpin eta %d aurpegi ditu",
                        _selected_object->izena, _selected_object->num_vertices, _selected_object->num_faces);
            }
            else{
                sprintf(mezua, "Ez dago objekturik kargatuta");
            }
            break;

        case 27: /* <ESC> */
            exit(0);
            break;

        case 'm':
        case 'M':
            if(aldaketa != MODE_TRANS){
                sprintf(mezua, "Translazioa aktibatuta");
                aldaketa = MODE_TRANS;
            }
            break;

        case 'b':
        case 'B':
            if(aldaketa != MODE_BIRAK){
                sprintf(mezua, "Biraketa aktibatuta");
                aldaketa = MODE_BIRAK;
            }
            break;

        case 't':
        case 'T':
            if(aldaketa != MODE_ESKAL){
                sprintf(mezua, "Eskalaketa aktibatuta");
                aldaketa = MODE_ESKAL;
            }
            break;

        case 'r':
        case 'R':
            if(aldaketa != MODE_ISLAP){
                sprintf(mezua, "Islapena aktibatuta");
                aldaketa = MODE_ISLAP;
            }
            break;

        case 'g':
        case 'G':
            if(err_sist != MODE_GLOBAL){
                sprintf(mezua, "Erreferentzi-sistema globala aktibatuta");
                err_sist = MODE_GLOBAL;
            }
            break;

        case 'l':
        case 'L':
            if(err_sist != MODE_LOKAL){
                sprintf(mezua, "Erreferentzi sistema lokala aktibatuta");
                err_sist = MODE_LOKAL;
            }
            break;

        case 'o':
        case 'O':;
            break;


        case 25: /* <CTRL + y/Y> */
            //Nahiz eta 'if (glutGetModifiers() == GLUT_ACTIVE_CTRL)' baldintza ez egon,
            //'CTRL + y/Y' kasua hartzen du, konbinazio horren emaitza karaktere berezi bat delako
            if(_selected_object != 0){
                if (_selected_object->pila_y != NULL) {
                    //Aldaketa pila_y-tik pila_z-ra mugitu
                    pila *add_elem = _selected_object->pila_y;
                    _selected_object->pila_y = add_elem->next;
                    add_elem->next = _selected_object->pila_z;
                    _selected_object->pila_z = add_elem;
                } else {
                    sprintf(mezua, "Ez dago aldaketarik berregiteko");
                }
            }
            else{
                sprintf(mezua, "Ez dago objekturik kargatuta");
            }
            break;

        case 26: /* <CTRL + z/Z> */
            //Nahiz eta 'if (glutGetModifiers() == GLUT_ACTIVE_CTRL)' baldintza ez egon,
            //'CTRL + z/Z' kasua hartzen du, konbinazio horren emaitza karaktere berezi bat delako
            if( _selected_object != 0 ) {
                if (_selected_object->pila_z->next != NULL) { //Hasierako matrizean (unitarioan) ez bagaude
                    //Aldaketa pila_z-tik pila_y-ra mugitu
                    pila *del_elem = _selected_object->pila_z;
                    _selected_object->pila_z = del_elem->next;
                    del_elem->next = _selected_object->pila_y;
                    _selected_object->pila_y = del_elem;
                } else {
                    sprintf(mezua, "Ez dago aldaketarik desegiteko");
                }
            }
            else{
                sprintf(mezua, "Ez dago objekturik kargatuta");
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

    switch (key) {
        case GLUT_KEY_UP:
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(0, 1, 0);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(1, 0, 0);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(1, KG_ESKAL_HAND, 1);
                    break;
                case MODE_ISLAP:
                    mat = islapena(1, -1, 1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;
            }
            break;
        case GLUT_KEY_DOWN:
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(0, -1, 0);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(-1, 0, 0);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(1, KG_ESKAL_TXIK, 1);
                    break;
                case MODE_ISLAP:
                    mat = islapena(1, -1, 1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;

            }
            break;

        case GLUT_KEY_RIGHT:
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(1, 0, 0);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(0, 1, 0);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(KG_ESKAL_HAND, 1, 1);
                    break;
                case MODE_ISLAP:
                    mat = islapena(-1, 1, 1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;
            }
            break;

        case GLUT_KEY_LEFT:
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(-1, 0, 0);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(0, -1, 0);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(KG_ESKAL_TXIK, 1, 1);
                    break;
                case MODE_ISLAP:
                    mat = islapena(-1, 1, 1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;
            }
            break;

        case GLUT_KEY_PAGE_UP: //av_pag
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(0, 0, 1);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(0, 0, 1);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(1, 1, KG_ESKAL_TXIK);
                    break;
                case MODE_ISLAP:
                    mat = islapena(1, 1, -1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;
            }
            break;

        case GLUT_KEY_PAGE_DOWN: //re_pag
            switch (aldaketa) {
                case MODE_TRANS:
                    mat = translazioa(0, 0, -1);
                    break;
                case MODE_BIRAK:
                    mat = biraketa(0, 0, -1);
                    break;
                case MODE_ESKAL:
                    mat = eskalaketa(1, 1, KG_ESKAL_HAND);
                    break;
                case MODE_ISLAP:
                    mat = islapena(1, 1, -1);
                    break;
                case MODE_DEFAULT:
                    sprintf(mezua, "Ez dago aldaketarik aukeratuta, aukeratu bat");
                    break;
            }
            break;

        default:
            printf("Espeziala: %d %c\n", key, key);
            break;
    }
	if (_selected_object != 0){
            if(mat != NULL){
                switch (err_sist) {
                    case MODE_GLOBAL:
                        mat = mult(mat, _selected_object->pila_z->matrix);
                        break;
                    case MODE_LOKAL:
                        mat = mult(_selected_object->pila_z->matrix, mat);
                        break;
                }

                //Aldaketa berria gehitu pila_z pilari
                pila *new_elem = (pila *) malloc(sizeof(pila));
                new_elem->matrix = mat;
                new_elem->next = _selected_object->pila_z;
                _selected_object->pila_z = new_elem;

                //Aldaketabat egin dugunez, pila_y pila hustu
                _selected_object->pila_y = NULL;
            }
	}
    else if (key != GLUT_CTRL){
        sprintf(mezua, "Ez dago objekturik transformazioa aplikatzeko");
    }

    glutPostRedisplay();
	glPopMatrix();
}

