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
void separarFrase(char* fraseSeparada[], char* frase, int* validos) // deberia cambiar a matriz estatica?
{
    int i=0;
    int j=0;
    int k=0;
    while(i<10)
    {
        fraseSeparada[i] = (char*)malloc(sizeof(char)*20); // no olvidar liberar
        i++;
    }
    i=0;
    while(i<(*validos) && j<10 && k<20)
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
    if((j == 10 && i < (*validos)) || (k == 20 && fraseSeparada[j][k-1] != 0)) // caso bizarro?
    {
        i=0;
        while(i<10)
        {
            free(fraseSeparada[i]);
            fraseSeparada[i] = NULL;
        }
        j=0;
    }
    *validos = j;
}

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

int fraseRelativaAOcurrencia(nodoA* motor, char* fraseSeparada[], int validos, int pos)
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

int buscarFrase(nodoA* motor, char* frase, int* validos, nodoT* ocurrencia)
{
    char* fraseSeparada[10];
    separarFrase(fraseSeparada, frase, validos);
    nodoA* primerPalabra = NULL;
    if(fraseSeparada[0] != NULL)
    {
        primerPalabra = existePalabra(motor, fraseSeparada[0]);
    }
    else
    {
        // liberar fraseSeparada
        return -1; // no se pudo separar la frase o la primer palabra no existe
    }
    ocurrencia = primerPalabra->ocurrencias;
    while(ocurrencia)
    {
        if(fraseRelativaAOcurrencia(motor, fraseSeparada, *validos, ocurrencia->pos))
        {
            // liberar fraseSeparada
            return 1; // se encuentra una frase con exito
        }
        ocurrencia = ocurrencia->sig;
    }
    return 0; // si el control llega aca, es porque la frase contiene una sola palabra y esta en el arbol
}
