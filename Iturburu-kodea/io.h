#ifndef IO_H
#define IO_H

void keyboard(unsigned char key, int x, int y);

void special_keyboard(int key, int x, int y);

void aldaketakAplikatu(GLdouble *mat, int key);
void kameraAldatu(GLdouble *mat, int lokala);
void print_help();

void angeluaAldatu(int aldaketa);
int mugituDaiteke(int nora);


#endif // IO_H
