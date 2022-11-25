#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/**
Esta libreria se encarga de leer el directorio en el que se encuentra el proyecto, produce un archivo binario de terminos basado en hasta 10 documentos de texto (.txt) llamado diccionario.bin
es necesario enviar por parametros a la funcion genArchDicc (generar archivo diccionario) una matriz de tipo char y una variable int
que representara las filas que contienen strings con los nombres de los documentos de texto, el orden de estos se correspondera con los idDOCs del 1 al 10
**/

typedef struct
{
    char palabra[20];
    int idDOC;
    int pos; //incrementa palabra por palabra, y no letra por letra
} termino;

void genArrDeUnDoc(char**, int*, char*);
void cargarUnDocEnArchDicc(char*, int, int);
int extension(char*, char*);
void genArregloDeTXTs(char[][20], int*);
void genArchDicc(char[][20], int*);
void mostrarDiccionario(void);
void muestraTXTs(char[][20], int);
void preguntarIDs(int[], int*);

#endif // DICCIONARIO_H_INCLUDED
