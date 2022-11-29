#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "diccionario.h"

/**
Esta libreria se encarga de consumir el archivo diccionario.bin y convertirlo en un arbol binario de busqueda
es necesario invocar la funcion cargaDatos, pasandole un nodoA* inicializado en NULL como parametro
**/

typedef struct nodoT
{
    int idDOC;
    int pos;
    struct nodoT* sig;
} nodoT;

typedef struct nodoA
{
    char palabra[20];
    int frecuencia; ///representa la cantidad de nodos de la lista
    nodoT* ocurrencias; ///ordenada por idDOC, luego por pos
    struct nodoA* der;
    struct nodoA* izq;
    int factorBalance;
} nodoA;

nodoT* crearNodoPalabra(int, int);
nodoA* existePalabra(nodoA*, char*);
void insertarPalabra(nodoT**,int, int);
nodoA* crearNodoMotor (termino);
void insertarNodoYPalabra(nodoA**,termino);
void cargaDatos(nodoA**);
void mostrarTermino (nodoT*);
void mostrarArbol (nodoA*);
int altura(nodoA*);
nodoA* rotarSimpleDer(nodoA*, nodoA*);
nodoA* rotarDobleDerIzq(nodoA*, nodoA*);
nodoA* rotarSimpleIzq(nodoA*, nodoA*);
nodoA* rotarDobleIzqDer(nodoA*, nodoA*);
nodoA* rebalancear(nodoA* motor);

#endif // MOTOR_H_INCLUDED
