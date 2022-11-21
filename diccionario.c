#include "diccionario.h"

void genArrDeUnDoc(char** diccionario, int* validos, char* archivo) // recibe un puntero, se convierte en vector, contendra el documento en forma de string
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

void cargarUnDocEnArchDicc(char* diccionario, int validos, int idDOC)
{
    int contadorPos = 1;
    termino aux;
    aux.idDOC = idDOC;
    for(int i=0; i<20; i++) // mal necesario
    {
        aux.palabra[i] = 0;
    }
    int j=0;
    FILE* fp = fopen("diccionario.bin", "ab");
    if(fp)
    {
        for(int i=0; i<validos; i++)
        {
            if((diccionario[i]>= 65 && diccionario[i]<= 90) || (diccionario[i]>= 97 && diccionario[i]<= 122))
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

int extension(char* archivo, char* tipo) // extension("try.txt", ".txt")
{
    char *ext = strrchr(archivo, '.');
    if(ext && strcmpi(ext, tipo) == 0)
    {
        return 1;
    }
    return 0;
}

void genArregloDeTXTs(char mat[][20], int* validos)
{
    DIR* d;
    struct dirent* dir;
    d = opendir(".");
    if(d)
    {
        while((dir = readdir(d))!= NULL && (*validos) < 10)
        {
            if(extension(dir->d_name, ".txt"))
            {

                if(mat[*validos] != NULL)
                {
                    strcpy(mat[*validos], dir->d_name);
                    (*validos)++;
                }
                else
                {
                    dir = NULL;
                    *validos = -1; // error
                }
            }
        }
        closedir(d);
    }
}

void genArchDicc(void)
{
    remove("diccionario.bin");
    char* dicc = NULL;
    int validosDicc = 0;
    char arrTXTs[10][20];
    int validosTXTs = 0;
    genArregloDeTXTs(arrTXTs, &validosTXTs);
    for(int i=0; i<validosTXTs; i++)
    {
        genArrDeUnDoc(&dicc, &validosDicc, arrTXTs[i]);
        cargarUnDocEnArchDicc(dicc, validosDicc, i+1);
        free(dicc);
        dicc = NULL; // este puntero se reutiliza
    }
}

void mostrarDiccionario(void)
{
    FILE* fp = fopen("diccionario.bin", "rb");
    termino aux;

    if(fp)
    {
        while(fread(&aux, sizeof(termino),1,fp))
        {
            printf("%s\n", aux.palabra);
            printf("idDOC: %i\n", aux.idDOC);
            printf("pos: %i\n", aux.pos);
            printf("----------\n");
        }
        fclose(fp);
    }
}
