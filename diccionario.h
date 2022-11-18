#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char palabra[20];
    int idDOC;
    int pos; //incrementa palabra por palabra, y no letra por letra
} termino;

typedef struct
{
    char palabra[20];
} parola;

void generarDiccionario(char**, int*, char*);
void cargarArchivoDiccionario(char*, int, int);
int nuevoIdDoc(void);
//parola* separarFraseEnTerminos(char* frase, int* validos);
int Minimo(int, int);
int Levenshtein(char*, char*);

#endif // DICCIONARIO_H_INCLUDED
