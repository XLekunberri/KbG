#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "definitions.h"
#include "matrizeak.h"

#define MAXLINE 200

/*
 * Auxiliar function to process each line of the file
 */
static int sreadint(char * lerroa, int * zenbakiak) {
    char *s = lerroa;
    int i, zbk, kont = 0;

    while (sscanf(s, " %d%n", &zbk, &i) > 0) {
        s += i;
        zenbakiak[kont++] = zbk;
    }
    return (kont);
}

static int sreadint2(char * lerroa, int * zenbakiak) {
    char *s = lerroa;
    int i, zbk, kont = 0;

    while (sscanf(s, " %d%n", &zbk, &i) > 0) {
        s += i;
	while ((*s != ' ')&&(*s !='\0')) s++;  // jump vector normal information
        zenbakiak[kont++] = zbk;
    }
    printf("%d numbers in the line\n",kont);
    return (kont);
}


void setIzena(char **izena, char *helbidea){
    int end_ind = strlen(helbidea);
    int start_ind = end_ind;

    while( (start_ind != 0) && (helbidea[start_ind]!='/') ){
        start_ind--;
    }
    int luzera = (end_ind-start_ind)+1;

    (*izena)=(char*)malloc(sizeof(char)*luzera);

    if(helbidea[start_ind]=='/'){
        start_ind++;
    }

    sprintf(*izena, helbidea+start_ind);
    /*
    int i = 0, j = start_ind+1;
    while(i<luzera){
        (*izena)[i] = helbidea[j];
        i++;j++;
    }
    */

}

void normalaKalkulatu(face *aurpegia, vertex *erpin_taula){

    // Aurpegiaren 3 erpin hartu
    vertex *erpina1 = &(erpin_taula[aurpegia->vertex_table[0]]);
    vertex *erpina2 = &(erpin_taula[aurpegia->vertex_table[1]]);
    vertex *erpina3 = &(erpin_taula[aurpegia->vertex_table[2]]);

    //Bi bektoreak kalkulatu
    vector3 a, b;

    a.x = erpina1->coord.x - erpina2->coord.x;
    a.y = erpina1->coord.y - erpina2->coord.y;
    a.z = erpina1->coord.z - erpina2->coord.z;

    b.x = erpina1->coord.x - erpina3->coord.x;
    b.y = erpina1->coord.y - erpina3->coord.y;
    b.z = erpina1->coord.z - erpina3->coord.z;

    //Bektoreen biderkadura bektoriala kalkulatu
    vector3 axb;

    axb.x = a.y*b.z - a.z*b.y;
    axb.y = a.z*b.x - a.x*b.z;
    axb.z = a.x*b.y - a.y*b.x;

    //Biderkatura bektoriala normalizatu
    GLdouble norma = sqrt(axb.x*axb.x + axb.y*axb.y + axb.z*axb.z);

    axb.x = axb.x/norma;
    axb.y = axb.y/norma;
    axb.z = axb.z/norma;


    //Bektore normala aurpegiaren erpin guztietan gorde

    for(int i=0; i < aurpegia->num_vertices; i++){
        erpin_taula[i].normal = axb;
    }
}

/**
 * @brief Function to read wavefront files (*.obj)
 * @param file_name Path of the file to be read
 * @param object_ptr Pointer of the object3d type structure where the data will be stored
 * @return Result of the reading: 0=Read ok, 1=File not found, 2=Invalid file, 3=Empty file
 */
int read_wavefront(char * file_name, object3d * object_ptr) {
    vertex *vertex_table;
    face *face_table;
    GLdouble *normal = (GLdouble*)malloc(sizeof(GLdouble)*3);
    int num_vertices = -1, num_faces = -1, count_vertices = 0, count_faces = 0;
    FILE *obj_file;
    char line[MAXLINE], line_1[MAXLINE], aux[45];
    int k;
    int i, j;
    int values[MAXLINE];


    /*
     * The function reads twice the file. In the first read the number of
     * vertices and faces is obtained. Then, memory is allocated for each
     * of them and in the second read the actual information is read and
     * loaded. Finally, the object structure is created
     */
    if ((obj_file = fopen(file_name, "r")) == NULL) return (1);
    while (fscanf(obj_file, "\n%[^\n]", line) > 0) {
        i = 0;
        while (line[i] == ' ') i++;
        if ((line[0] == '#') && ((int) strlen(line) > 5)) {
            i += 2;
            j = 0;
            while (line[i] != ' ') line_1[j++] = line[i++];
            i++;
            line_1[j] = '\0';
            j = 0;
            while ((line[i] != ' ') && (line[i] != '\0'))
                aux[j++] = line[i++];
            aux[j] = 0;
            if (strcmp(aux, "vertices") == 0) {
                num_vertices = atoi(line_1);
            }
            if (strncmp(aux, "elements", 7) == 0) {
                num_faces = atoi(line_1);
            }
        } else {
            if (strlen(line) > 6) {
                if (line[i] == 'f' && line[i + 1] == ' ')
                    count_faces++;
                else if (line[i] == 'v' && line[i + 1] == ' ')
                    count_vertices++;
            }
        }
    }
    fclose(obj_file);
    printf("1 pasada: num vert = %d (%d), num faces = %d(%d) \n",num_vertices,count_vertices,num_faces,count_faces);
    if ((num_vertices != -1 && num_vertices != count_vertices) || (num_faces != -1 && num_faces != count_faces)) {
        printf("WARNING: full file format: (%s)\n", file_name);
        //return (2);
    }
    if (num_vertices == 0 || count_vertices == 0) {
        printf("No vertex found: (%s)\n", file_name);
        return (3);
    }
    if (num_faces == 0 || count_faces == 0) {
        printf("No faces found: (%s)\n", file_name);
        return (3);
    }

    num_vertices = count_vertices;
    num_faces = count_faces;

    vertex_table = (vertex *) malloc(num_vertices * sizeof (vertex));
    face_table = (face *) malloc(num_faces * sizeof (face));

    obj_file = fopen(file_name, "r");
    k = 0;
    j = 0;

    for (i = 0; i < num_vertices; i++)
        vertex_table[i].num_faces = 0;

    while (fscanf(obj_file, "\n%[^\n]", line) > 0) {
        switch (line[0]) {
            case 'v':
            if (line[1] == ' ')  // vn not interested
		{
                sscanf(line + 2, "%lf%lf%lf", &(vertex_table[k].coord.x),
                        &(vertex_table[k].coord.y), &(vertex_table[k].coord.z));
                k++;
		}
               break;

            case 'f':
	    if (line[1] == ' ') // fn not interested
                {
                for (i = 2; i <= (int) strlen(line); i++)
                    line_1[i - 2] = line[i];
		line_1[i-2] = '\0';
                face_table[j].num_vertices = sreadint2(line_1, values);
                //printf("f %d vertices\n",face_table[j].num_vertices);
                face_table[j].vertex_table = (int *) malloc(face_table[j].num_vertices * sizeof (int));
                for (i = 0; i < face_table[j].num_vertices; i++) {
                    face_table[j].vertex_table[i] = values[i] - 1;
                    //printf(" %d ",values[i] - 1);
                    vertex_table[face_table[j].vertex_table[i]].num_faces++;
                    }
                //printf("\n");
                j++;
                }
              break;
        }
    }

    fclose(obj_file);


    for(int i = 0; i<num_faces; i++){
        normalaKalkulatu(face_table[i], vertex_table);
    }

    printf("2 pasada\n");

    /*
     * Information read is introduced in the structure */
    object_ptr->vertex_table = vertex_table;
    object_ptr->face_table = face_table;
    object_ptr->num_vertices = num_vertices;
    object_ptr->num_faces = num_faces;


    /*
     * The maximum and minimum coordinates are obtained **/
    object_ptr->max.x = object_ptr->vertex_table[0].coord.x;
    object_ptr->max.y = object_ptr->vertex_table[0].coord.y;
    object_ptr->max.z = object_ptr->vertex_table[0].coord.z;
    object_ptr->min.x = object_ptr->vertex_table[0].coord.x;
    object_ptr->min.y = object_ptr->vertex_table[0].coord.y;
    object_ptr->min.z = object_ptr->vertex_table[0].coord.z;

    for (i = 1; i < object_ptr->num_vertices; i++)
    {
        if (object_ptr->vertex_table[i].coord.x < object_ptr->min.x)
            object_ptr->min.x = object_ptr->vertex_table[i].coord.x;

        if (object_ptr->vertex_table[i].coord.y < object_ptr->min.y)
            object_ptr->min.y = object_ptr->vertex_table[i].coord.y;

        if (object_ptr->vertex_table[i].coord.z < object_ptr->min.z)
            object_ptr->min.z = object_ptr->vertex_table[i].coord.z;

        if (object_ptr->vertex_table[i].coord.x > object_ptr->max.x)
            object_ptr->max.x = object_ptr->vertex_table[i].coord.x;

        if (object_ptr->vertex_table[i].coord.y > object_ptr->max.y)
            object_ptr->max.y = object_ptr->vertex_table[i].coord.y;

        if (object_ptr->vertex_table[i].coord.z > object_ptr->max.z)
            object_ptr->max.z = object_ptr->vertex_table[i].coord.z;

    }

    //Hasieratu

    setIzena(&(object_ptr->izena), file_name);


    object_ptr->pila_z = (pila*)malloc(sizeof(pila));
    object_ptr->pila_z->matrix = identitatea();
    object_ptr->pila_z->next   = NULL;
    object_ptr->pila_y = NULL;
    return (0);
}

