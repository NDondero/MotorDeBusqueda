#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

typedef struct
{
    char palabra[20];
    int idDOC;
    int pos; //incrementa palabra por palabra, y no letra por letra
} termino;

void generarDiccionario(char**, int*, char*);
void cargarArchivoDiccionario(char*, int, int);
int nuevoIdDoc(void);

#endif // DICCIONARIO_H_INCLUDED
