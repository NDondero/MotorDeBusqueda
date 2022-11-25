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
#define col 20


void menu();
void recuadro(int,int,int,int);
void color(int);
void gotoxy(int,int);
void hidecursor(int);
void menuOperacionesDeUsuario();

#endif // MENU_H_INCLUDED
