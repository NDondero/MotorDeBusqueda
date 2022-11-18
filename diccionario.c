#include "diccionario.h"

void generarDiccionario(char** diccionario, int* validos, char* archivo) // recibe un puntero, se convierte en vector, contendra el documento en forma de string
{
    FILE* fp = fopen(archivo, "rb");
    long dimArch;
    char aux;
    int i=0;
    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        dimArch = ftell(fp) / sizeof(char);
        fseek(fp, 0, SEEK_SET);
        *diccionario = (char*)malloc(sizeof(char)*dimArch);
        while(fread(&aux, sizeof(char), 1, fp))
        {
            (*diccionario)[i] = aux;
            i++;
        }
        *validos = i;
        fclose(fp);
    }
}

void cargarArchivoDiccionario(char* diccionario, int validos, int idDOC)
{
    int contadorPos = 0;
    termino aux;
    aux.idDOC = idDOC;
    aux.palabra[0] = 0;
    int j=0;
    FILE* fp = fopen("diccionario.bin", "wb");
    if(fp)
    {
        for(int i=0; i<validos; i++)
        {
            if((diccionario[i]>= 65 && diccionario[i]< 91) || (diccionario[i]>= 97 && diccionario[i]< 123))
            {
                aux.palabra[j] = diccionario[i];
                j++;
            }
            else if(aux.palabra[0] != 0)
            {
                j=0;
                aux.pos = contadorPos;
                fwrite(&aux, sizeof(termino),1,fp);
                for(int k=0; k<20; k++)
                {
                    aux.palabra[k] = 0;
                }
                contadorPos++;
            }
        }
        fclose(fp);
    }
}

int nuevoIdDoc(void)
{
    FILE* fp = fopen("diccionario.bin", "rb");
    termino aux;
    if(fp)
    {
        fseek(fp, -sizeof(termino), SEEK_END); // overflow?
        fread(&aux, sizeof(termino),1,fp);
        fclose(fp);
        return aux.idDOC+1;
    }
    return 1;
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

int Minimo(int a, int b)
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
}
