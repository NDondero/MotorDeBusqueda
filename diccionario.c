#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    FILE* fp = fopen("diccionario.bin", "wb"); // esto eventualmente va a cambiar de modo, creo que ab sirve para crear y agregar, pero no recuerdo
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
                for(int l=0; l<20; l++)
                {
                    aux.palabra[l] = 0;
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
        fseek(fp, sizeof(termino)*-1, SEEK_END);
        fread(&aux, sizeof(termino),1,fp);
        fclose(fp);
        return aux.idDOC+1;
    }
    return 1;
}
