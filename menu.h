#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <locale.h> ///ver
#include "diccionario.h"
#include "motor.h"
#include "operacionesDeUsuario.h"



void menu();
void recuadro(int,int,int,int);
void color(int);
void gotoxy(int,int);
void hidecursor(int);
void muestraTXTs(char[][20], int);
void preguntarIDs(int[], int*);
void menuVerArchivos(char[][20], int);
void menuOperacionesDeUsuario(nodoA*, char[][20],int);
void menuOtros(nodoA*);

#endif // MENU_H_INCLUDED
