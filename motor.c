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
    nuevo->factorBalance = 0;
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
    if(*motor)
    {
        (*motor)->factorBalance = altura((*motor)->der) - altura((*motor)->izq);
        if((*motor)->factorBalance < -1 || (*motor)->factorBalance > 1)
        {
            *motor = rebalancear(*motor);
        }
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
        printf("idDoc: %i ",lista->idDOC);
        printf("Posicion: %i\n",lista->pos);
        lista = lista->sig;
    }
}

void mostrarArbol (nodoA* motor)
{
    if(motor)
    {
        mostrarArbol(motor->izq);
        printf("Palabra: %s\n",motor->palabra);
        printf("Frecuencia: %i\n",motor->frecuencia);
        mostrarTermino(motor->ocurrencias);
        printf("\n");
        mostrarArbol(motor->der);
    }
}

int altura(nodoA* motor)
{
    int altIzq, altDer;
    if(motor)
    {
        altIzq = 1 + altura(motor->izq);
        altDer = 1 + altura(motor->der);
        if(altIzq > altDer)
        {
            return altIzq;
        }
        return altDer;
    }
    return 0;
}

nodoA* rotarSimpleDer(nodoA* X, nodoA* Z) // X == raiz a rotar | Z == hijo a derecha pesado a derecha
{
    X->der = Z->izq; // puede ser NULL o un subarbol
    Z->izq = X; // rotacion de padre por hijo
    X->factorBalance = altura(X->der) - altura(X->izq);
    Z->factorBalance = altura(Z->der) - altura(Z->izq);
    return Z; // la nueva raiz del subarbol
}

nodoA* rotarDobleDerIzq(nodoA* X, nodoA* Z) // X == raiz a rotar | Z == hijo a derecha pesado a izquierda
{
    nodoA* Y = Z->izq; // contiene una llave entre X y Z
    Z->izq = Y->der; // en insercion siempre va a ser NULL // Y->der puede ser un desenlace o rotacion de llaves mayores a la futura raiz
    Y->der = Z; // 1era rotacion
    X->der = Y->izq; // en insercion siempre va a ser NULL // Y->izq puede ser desenlance o rotacion de llaves
    Y->izq = X; // 2da rotacion
    X->factorBalance = altura(X->der) - altura(X->izq);
    Z->factorBalance = altura(Z->der) - altura(Z->izq);
    Y->factorBalance = altura(Y->der) - altura(Y->izq);
    return Y; // devuelve la nueva raiz
}

nodoA* rotarSimpleIzq(nodoA* Z, nodoA* X) // Z == raiz a rotar | X == hijo a izquierda pesado a izquierda
{
    Z->izq = X->der;
    X->der = Z;
    Z->factorBalance = altura(Z->der) - altura(Z->izq);
    X->factorBalance = altura(X->der) - altura(X->izq);
    return X;
}

nodoA* rotarDobleIzqDer(nodoA* Z, nodoA* X) // Z == raiz a rotar | X == hijo a izquierda pesado a derecha
{
    nodoA* Y = X->der;
    X->der = Y->izq;
    Y->izq = X;
    Z->izq = Y->der;
    Y->der = Z;
    X->factorBalance = altura(X->der) - altura(X->izq);
    Z->factorBalance = altura(Z->der) - altura(Z->izq);
    Y->factorBalance = altura(Y->der) - altura(Y->izq);
    return Y;
}

nodoA* rebalancear(nodoA* motor)
{
    if(motor->factorBalance > 1)
    {
        if(motor->der->factorBalance >= 0)
        {
            return rotarSimpleDer(motor, motor->der);
        }
        return rotarDobleDerIzq(motor, motor->der);
    }
    else
    {
        if(motor->izq->factorBalance <= 0)
        {
            return rotarSimpleIzq(motor, motor->izq);
        }
        return rotarDobleIzqDer(motor, motor->izq);
    }
}
