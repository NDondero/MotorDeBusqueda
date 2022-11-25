#include "motor.h"

nodoT* crearNodoPalabra(int idDOC, int pos)
{
    nodoT* nueva = (nodoT*)malloc(sizeof(nodoT));
    nueva->idDOC=idDOC;
    nueva->pos=pos;
    nueva->sig=NULL;
    return nueva;
}

nodoA* existePalabra(nodoA* motor, char* palabra)
{
    if(motor)
    {
        if(strcmpi(motor->palabra,palabra)==0)
        {
            return motor;
        }
        else
        {
            if (strcmpi(motor->palabra,palabra)>0)
            {
                return existePalabra(motor->izq,palabra);
            }
            else
            {
                return existePalabra(motor->der,palabra);
            }

        }
    }
    return NULL;
}

void insertarPalabra(nodoT** listaPalabras,int idDOC, int pos)///¡?
{
    nodoT* nueva = crearNodoPalabra(idDOC, pos);
    nodoT* seg, *ant;
    if(!(*listaPalabras))
    {
        nueva->sig = *listaPalabras;
        *listaPalabras = nueva;
    }
    else
    {
        ant = *listaPalabras;
        seg = (*listaPalabras)->sig;
        while(seg && seg->idDOC <= idDOC && seg->pos < pos)
        {
            ant = seg;
            seg = seg->sig;
        }
        ant->sig = nueva;
        nueva->sig = seg;
    }

    /*if(!(*listaPalabras) || (*listaPalabras)->idDOC>idDOC)
    {
        nodoT* nueva = crearNodoPalabra(idDOC,pos);
        nueva->sig = *listaPalabras;
        *listaPalabras = nueva;
    }
    else
    {
        insertarPalabra(&((*listaPalabras)->sig),idDOC,pos);
    }*/
}

nodoA* crearNodoMotor (termino aux)
{
    nodoA* nuevo = (nodoA*)malloc(sizeof(nodoA));
    strcpy(nuevo->palabra,aux.palabra);
    nuevo->izq=NULL;
    nuevo->der=NULL;
    nodoT* nueva = crearNodoPalabra(aux.idDOC,aux.pos);
    nuevo->ocurrencias = nueva;
    nuevo->frecuencia=1;
    return nuevo;
}

void insertarNodoYPalabra(nodoA** motor,termino aux)
{
    if(!(*motor))
    {
        *motor = crearNodoMotor(aux);
    }
    else if (strcmpi((*motor)->palabra,aux.palabra)>0)
    {
        insertarNodoYPalabra(&((*motor)->izq),aux);
    }
    else
    {
        insertarNodoYPalabra(&((*motor)->der),aux);
    }
}

void cargaDatos(nodoA** motor)
{
    FILE* fp = fopen("diccionario.bin","rb");
    termino aux;
    nodoA* existe;
    if(fp)
    {
        while(fread(&aux,sizeof(termino),1,fp)>0)
        {
            existe = existePalabra((*motor),aux.palabra);
            if(existe)
            {
                insertarPalabra(&(existe->ocurrencias),aux.idDOC,aux.pos);
                (existe->frecuencia)++;
            }
            else
            {
                insertarNodoYPalabra(motor,aux);
            }
        }
        fclose(fp);
    }
}

void mostrarTermino (nodoT* lista)
{
    while(lista)
    {
        printf("idDoc: %i\n",lista->idDOC);
        printf("Posicion: %i\n\n",lista->pos);
        lista = lista->sig;
    }
}

void mostrarArbol (nodoA* motor)
{
    if(motor)
    {
        mostrarArbol(motor->izq);
        printf("Palabra: %s\n",motor->palabra);
        printf("Frecuencia: %i\n\n",motor->frecuencia);
        //mostrarTermino(arbol->ocurrencias);
        mostrarArbol(motor->der);
    }
}

