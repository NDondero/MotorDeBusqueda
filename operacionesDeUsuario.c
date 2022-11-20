#include "operacionesDeUsuario.h"

/**OPERACIONES DEL USUARIO

1. Buscar todas las apariciones de un término en algún documento (operación or).
2. Buscar todas las apariciones de un término en un documento y otros  (operacion and).
3. Buscar la aparición de más de un término en el mismo documento.
4. Buscar una frase completa (las palabras deben estar contiguas en alguno de los documentos).
5. Buscar la palabra de más frecuencia que aparece en un doc.
6. Utilizar la distancia de levenshtein en el ingreso de una palabra
   y sugerir similares a partir de una distancia <= 3.
**/

/// 1.
int frecuenciaPorDocumento(nodoT* ocurrecias,int id)
{
    int cant=0;
    while (ocurrecias && ocurrecias->idDOC<= id)
    {
        if(ocurrecias->idDOC==id)
        {
            cant++;
        }
        ocurrecias= ocurrecias->sig;
    }
    return cant;
}

void buscarTerminoEnDocumento(nodoA* motor, char* palabra, int id)
{
    nodoA* nodoPalabra = buscarPalabra(motor,palabra);
    if(nodoPalabra)
    {
        int cant = frecuenciaPorDocumento(nodoPalabra->ocurrencias,id);
        printf("La palabra: %s, esta en el documento: %i %i veces\n",palabra,id,cant);
    }else
    {
        printf("No se encontro la palabra");
    }
}

/// 2.
void buscarTerminoEnDocumentos(nodoA* motor,char* palabra, int* idDocs, int validos)
{
    nodoA* nodoPalabra = buscarPalabra(motor,palabra);
    int i=0,flag=1;
    while (i<validos && flag==1 )
    {
        int frecuencias = frecuenciaPorDocumento(nodoPalabra->ocurrencias,idDocs[i]);
        if(frecuencias ==0)
        {
            flag=0;
        }
        i++;
    }
    if(flag==1)
    {
        printf("Se encontro la palabra: %s, en los documentos seleccionados\n",palabra);
    }else
    {
        printf("No se encontro la palabra en todos o alguno de los documentos\n");
    }
}

/// 3.
void buscarMasDeUnTermino(nodoA* motor, char* palabras, int idDOC, int validos)
{
    for(int i=0;i<validos;i++)
    {
        buscarTerminoEnDocumento(motor,&palabras[i],idDOC);
    }
}

/// 4.
void buscarFrase(nodoA* motor, char* frase, int validos)
{
  /*while(frase)
  {
      nodoA
      while(ocurrencia)
      {
          palabra en id -> posi
      }
  }*/
}
