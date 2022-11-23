#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include "diccionario.h"
#include "motor.h"
#include "operacionesDeUsuario.h"

int main()
{
    char arrTXTs[10][20];
    int validosTXTs = 0;
    genArchDicc(arrTXTs, &validosTXTs);
    //mostrarDiccionario();
    nodoA* motor = NULL;
    cargaDatos(&motor);
    //mostrarArbol(motor);

    /*for(int i=0; i<validosTXTs; i++)
    {
        printf("%s\n", arrTXTs[i]);
    }*/

    /*char frase[100];
    printf("frase o termino: ");
    gets(frase);*/

    //int docs[] = {2,3};
    //buscarTerminoEnDocumento(motor, frase, 1);
    //buscarTerminoEnDocumentos(motor, frase, docs, 2);
    //buscarMasDeUnTermino(motor, frase, 1);
    /*nodoT* ocurrencia = NULL;
    if(buscarFrase(motor, frase, &ocurrencia) == 1)
    {
        printf("se encontro en el documento %i en la posicion %i\n", ocurrencia->idDOC,ocurrencia->pos);
    }*/
    /*nodoA* mayorFrecuencia = palabraMayorFrecuencia(motor);
    if(mayorFrecuencia)
    {
        printf("la palabra \"%s\" es la mas frecuente con %i ocurrencias\n", mayorFrecuencia->palabra, mayorFrecuencia->frecuencia);
    }*/
    /*nodoA* sugerencia = sugerirPalabra(motor, frase);
    if(sugerencia && Levenshtein(sugerencia->palabra, frase) <= 3)
    {
        printf("quisiste decir %s en lugar de %s\n", sugerencia->palabra, frase);
    }*/

    return 0;
}
