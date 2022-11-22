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

/// 1. Buscar todas las apariciones de un término en algún documento (operación or).
int frecuenciaPorDocumento(nodoT* ocurrecias,int id)
{
    int cant=0;
    while(ocurrecias && ocurrecias->idDOC <= id)
    {
        if(ocurrecias->idDOC == id)
        {
            cant++;
        }
        ocurrecias = ocurrecias->sig;
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
        printf("No se encontro la palabra\n");
    }
}
/**Actualmente, la funcion del punto 1 se encarga de comprobar la existencia de una palabra en un documento especifico
e informar cuantas veces aparece en ese documento en particular **/

/// 2. Buscar todas las apariciones de un término en un documento y otros  (operacion and).
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
/**La funcion del punto 2 se encarga de verificar que una palabra este en todos los documentos
que recibe de un arreglo de IDs **/

/// 3. Buscar la aparición de más de un término en el mismo documento.
void separarFrase(char fraseSeparada[][20], char* frase, int* validos)
{
    int i=0;
    int j=0;
    int k=0;
    while(i<=(*validos) && j<10 && k<20) // <=validos porque sino no se lee el ultimo terminador
    {
        if((frase[i]>= 65 && frase[i]<= 90) || (frase[i]>= 97 && frase[i]<= 122))
        {
            fraseSeparada[j][k] = frase[i]; // agrego un caracter
            k++;
        }
        else
        {
            fraseSeparada[j][k] = 0; // agrego un terminador
            k=0;
            j++;
        }
        i++;
    }
    if((j == 10 && i < (*validos)) || (k == 20 && fraseSeparada[j][k-1] != 0))
    {
        j=0;
    }
    *validos = j;
}

void buscarMasDeUnTermino(nodoA* motor, char* palabras, int idDOC, int validos)
{
    char fraseSeparada[10][20];
    separarFrase(fraseSeparada, palabras, &validos);
    for(int i=0;i<validos;i++)
    {
        buscarTerminoEnDocumento(motor,fraseSeparada[i],idDOC);
    }
    if(validos==0)
    {
        printf("no se pudo buscar la frase en el documento\n");
    }
}
/**La funcion del punto 3 se encarga de separar una frase en palabras y repite el la funcion del punto 1
tantas veces como palabras contenga la frase **/

/// 4. Buscar una frase completa (las palabras deben estar contiguas en alguno de los documentos).
int ocurrenciaContigua(nodoT* listaOcurrencias, int pos, int desplazamiento)
{
    while(listaOcurrencias && listaOcurrencias->pos < pos + desplazamiento) // esta ordenada por pos la lista de ocurrencias
    {
        listaOcurrencias = listaOcurrencias->sig;
    }
    if(listaOcurrencias->pos == pos + desplazamiento)
    {
        return 1;
    }
    return 0;
}

int fraseRelativaAOcurrencia(nodoA* motor, char fraseSeparada[][20], int validos, int pos)
{
    int i=1; // 0 es la primer palabra, representada en pos
    nodoA* palabraSiguiente;
    while(i<validos)
    {
        palabraSiguiente = existePalabra(motor, fraseSeparada[i]);
        if(!palabraSiguiente || !ocurrenciaContigua(palabraSiguiente->ocurrencias, pos, i))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int buscarFrase(nodoA* motor, char* frase, int validos, nodoT** ocurrencia)
{
    char fraseSeparada[10][20];
    separarFrase(fraseSeparada, frase, &validos);
    nodoA* primerPalabra = NULL;
    if((validos)>0)
    {
        primerPalabra = existePalabra(motor, fraseSeparada[0]);
    }
    else if(!primerPalabra)
    {
        return -1; // no se pudo separar la frase o la primer palabra no existe
    }
    *ocurrencia = primerPalabra->ocurrencias;
    while(*ocurrencia)
    {
        if(fraseRelativaAOcurrencia(motor, fraseSeparada, validos, (*ocurrencia)->pos))
        {
            return 1; // se encuentra una frase con exito
        }
        *ocurrencia = (*ocurrencia)->sig;
    }
    return 0; // si el control llega aca, es porque la frase contiene una sola palabra y esta en el arbol
    // devolvera la ultima ocurrencia de la palabra
}
/**La funcion del punto 4 se encarga de separar una frase en palabras, devolvera -1 si la frase no se pudo separar
o la primer palabra no existe en ningun documento y no se llegara a modificar el nodoT ocurrencia,
por lo que es conveniente que venga inicializado en NULL. 0 si la frase contenia una sola palabra
y el nodoT ocurrencia contendra la ultima ocurrencia de esa palabra, esto es la ultima posicion encontrada
del documento con mayor ID. 1 si la frase se encuentra de manera contigua en algun documento
y el nodoT ocurrencia contendra la posicion de la primer palabra de la frase en el documento en el que aparece **/
