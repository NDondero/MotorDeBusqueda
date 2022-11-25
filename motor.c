#include "motor.h"

nodoT* crearNodoPalabra(int idDOC, int pos)
{
    nodoT* nueva = (nodoT*)malloc(sizeof(nodoT));
    nueva->idDOC=idDOC;
    nueva->pos=pos;
    nueva->sig=NULL;
    return nueva;
}

nodoA* existePalabra(nodoA* arbol, char* palabra)
{
    if(arbol)
    {
        if(strcmpi(arbol->palabra,palabra)==0)
        {
            return arbol;
        }
        else
        {
            if (strcmpi(arbol->palabra,palabra)>0)
            {
                return existePalabra(arbol->izq,palabra);
            }
            else
            {
                return existePalabra(arbol->der,palabra);
            }

        }
    }
    return NULL;
}

void insertarPalabra(nodoT** listaPalabras,int idDOC, int pos)
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

void insertarNodoYPalabra(nodoA** arbol,termino aux)
{
    if(!(*arbol))
    {
        *arbol = crearNodoMotor(aux);
    }
    else if (strcmpi((*arbol)->palabra,aux.palabra)>0)
    {
        insertarNodoYPalabra(&((*arbol)->izq),aux);
    }
    else
    {
        insertarNodoYPalabra(&((*arbol)->der),aux);
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

void mostrarArbol (nodoA* arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izq);
        printf("Palabra: %s\n",arbol->palabra);
        printf("Frecuencia: %i\n\n",arbol->frecuencia);
        //mostrarTermino(arbol->ocurrencias);
        mostrarArbol(arbol->der);
    }
}

nodoA* buscarPalabra(nodoA* arbol, char* palabra)
{
    if(arbol)
    {
        if(strcmpi(arbol->palabra,palabra)==0)
        {
            return arbol;
//            char aux[2];
//            itoa(arbol->frecuencia,aux,10);
//            //strcat()
//           MessageBox(NULL, arbol->palabra, "", MB_OK);
//           MessageBox(NULL, aux, "", MB_OK);
//           //MessageBoxA()
        }
        else
        {
            if (strcmpi(arbol->palabra,palabra)>0)
            {
                return buscarPalabra(arbol->izq,palabra);
            }
            else
            {
               return buscarPalabra(arbol->der,palabra);
            }

        }
    }
    return NULL;
}
