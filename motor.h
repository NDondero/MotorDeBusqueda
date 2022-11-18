#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "diccionario.h"

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
} nodoA;

nodoT* crearNodoPalabra(int, int);
nodoA* existePalabra(nodoA*, char*);
void insertarPalabra(nodoT**,int, int);
nodoA* crearNodoMotor (termino);
void insertarNodoYPalabra(nodoA**,termino);
void cargaDatos(nodoA**);
void mostrarTermino (nodoT*);
void mostrarArbol (nodoA*);
nodoA* buscarPalabra(nodoA*, char*);

#endif // MOTOR_H_INCLUDED
