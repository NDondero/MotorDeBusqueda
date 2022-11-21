#ifndef OPERACIONESDEUSUARIO_H_INCLUDED
#define OPERACIONESDEUSUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motor.h"

int frecuenciaPorDocumento(nodoT*, int);
void buscarTerminoEnDocumento(nodoA*, char*, int);
void buscarTerminoEnDocumentos(nodoA*, char*, int*, int);
void buscarMasDeUnTermino(nodoA*, char*, int, int);
void separarFrase(char*[], char*, int*);
int ocurrenciaContigua(nodoT*, int, int);
int fraseRelativaAOcurrencia(nodoA*, char*[], int, int);
int buscarFrase(nodoA*, char*, int*, nodoT*);

#endif // OPERACIONESDEUSUARIO_H_INCLUDED
