#ifndef OPERACIONESDEUSUARIO_H_INCLUDED
#define OPERACIONESDEUSUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motor.h"

int frecuenciaPorDocumento(nodoT*, int);
void buscarTerminoEnDocumento(nodoA*, char*, int);
void buscarTerminoEnDocumentos(nodoA*, char*, int*, int);
void separarFrase(char[][20], char*, int*);
void buscarMasDeUnTermino(nodoA*, char*, int);
int ocurrenciaContigua(nodoT*, int, int, int);
int fraseRelativaAOcurrencia(nodoA*, char[][20], int, int, int);
int buscarFrase(nodoA*, char*, nodoT**);
nodoA* palabraMayorFrecuencia(nodoA* motor);
int Minimo(int, int);
int Levenshtein(char *,char *);
nodoA* sugerirPalabra(nodoA*, char*);

#endif // OPERACIONESDEUSUARIO_H_INCLUDED
