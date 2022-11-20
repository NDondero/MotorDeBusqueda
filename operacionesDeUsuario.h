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
void buscarFrase(nodoA*, char*, int);

#endif // OPERACIONESDEUSUARIO_H_INCLUDED
