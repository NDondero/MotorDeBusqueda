#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include "diccionario.h"
#include "motor.h"

/// tengo una re idea, cuando hagamos el menu, arranca con dos opciones,
/// el motor con las funciones de usuario y una demo que muestre todo con pausas
/// sin mas interaccion que "presione cualquier tecla para continuar"

int main()
{
    printf("hola mundo!\n");
    return 0;
}

/*parola* separarFraseEnTerminos(char* frase, int* validos)
{
    parola arr[10];
    int i=0;
    int j=0;
    int k=0;
    while(i<(*validos) && j<10)
    {
        if((frase[i]>= 65 && frase[i]<= 90) || (frase[i]>= 97 && frase[i]<= 122))
        {
            arr[j].palabra[k] = frase[i];
            k++;
        }
        else
        {
            arr[j].palabra[k] = 0;
            k=0;
            j++;
        }
        i++;
    }
    *validos = j;

    return arr;
}*/

/*int Minimo(int a, int b)
{
    if(a < b) return a;
    return b;
}

int Levenshtein(char *s1,char *s2)
{
    int t1,t2,i,j,*m,costo,res,ancho;

// Calcula tamanios strings
    t1=strlen(s1);
    t2=strlen(s2);

// Verifica que exista algo que comparar
    if (t1==0) return(t2);
    if (t2==0) return(t1);
    ancho=t1+1;

// Reserva matriz con malloc                     m[i,j] = m[j*ancho+i] !!
    m=(int*)malloc(sizeof(int)*(t1+1)*(t2+1));
    if (m==NULL) return(-1); // ERROR!!

// Rellena primera fila y primera columna
    for (i=0; i<=t1; i++) m[i]=i;
    for (j=0; j<=t2; j++) m[j*ancho]=j;

// Recorremos resto de la matriz llenando pesos
    for (i=1; i<=t1; i++) for (j=1; j<=t2; j++)
        {
            if (s1[i-1]==s2[j-1]) costo=0;
            else costo=1;
            m[j*ancho+i]=Minimo(Minimo(m[j*ancho+i-1]+1,     // Eliminacion
                                       m[(j-1)*ancho+i]+1),              // Insercion
                                m[(j-1)*ancho+i-1]+costo);
        }      // Sustitucion

// Devolvemos esquina final de la matriz
    res=m[t2*ancho+t1];
    free(m);
    return(res);
}*/
