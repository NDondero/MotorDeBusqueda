#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct
{
    char palabra[20];
    int idDOC;
    int pos; //incrementa palabra por palabra, y no letra por letra
} termino;

void genArrDeUnDoc(char**, int*, char*);
void cargarUnDocEnArchDicc(char*, int, int);
int nuevoIdDoc(void);
int extension(char*, char*);
void genArregloDeTXTs(char*[], int*);
void genArchDicc(void);

#endif // DICCIONARIO_H_INCLUDED
