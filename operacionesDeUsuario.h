#ifndef OPERACIONESDEUSUARIO_H_INCLUDED
#define OPERACIONESDEUSUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motor.h"

/**
Esta libreria se encarga de contener todas las funciones que serian necesarias para que el usuario haga busquedas durante ejecucion
**/

int frecuenciaPorDocumento(nodoT*, int);
void buscarTerminoEnDocumento(nodoA*, char*, int);
void buscarTerminoEnDocumentos(nodoA*, char*, int*, int);
void buscarTerminoEnTodosDocumentos(nodoA*, char*, int, char[][20]);
void separarFrase(char[][20], char*, int*);
void buscarMasDeUnTermino(nodoA*, char*, int);
int ocurrenciaContigua(nodoT*, int, int, int);
int fraseRelativaAOcurrencia(nodoA*, char[][20], int, int, int);
nodoT* buscarFrase(nodoA*, char*);
nodoA* palabraMayorFrecuenciaDeUnDoc(nodoA* motor, int);
int Minimo(int, int);
int Levenshtein(char *,char *);
nodoA* sugerirPalabra(nodoA*, char*);

#endif // OPERACIONESDEUSUARIO_H_INCLUDED
