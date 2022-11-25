#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "operacionesDeUsuario.h"



void menu();
void recuadro(int,int,int,int);
void color(int);
void gotoxy(int,int);
void hidecursor(int);
void menuVerArchivos(char[][20], int);
void menuOperacionesDeUsuario(nodoA*, char[][20],int);
void menuOtros(nodoA*);

#endif // MENU_H_INCLUDED
