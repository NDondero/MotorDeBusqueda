#include "menu.h"

void menu()
{
    char arrTXTs[10][20];
    int validosTXTs = 0;
    nodoA* motor = NULL;

    genArchDicc(arrTXTs, &validosTXTs);
    cargaDatos(&motor);

    hidecursor(0);

    int y,x=14,opcion,salir=0;
///MENU PRINCIPAL
    while(salir!=1)
    {
        y=6;
        opcion=0;
        system("cls");
        while(opcion!=13)
        {
            color(9);
            recuadro(14,1,27,3);
            gotoxy(15,2);
            color(11);
            printf("Shahoo! Search");

            int j = 6;
            while(j<=15)
            {
                color(0);
                recuadro(14,j,27,3);
                j+=3;
            }

            //opciones del menu
            color(7);

            gotoxy(16,7);
            printf("Ver Textos");

            gotoxy(16,10);
            printf("Operaciones de Busqueda");

            gotoxy(16,13);
            printf("Otros");

            gotoxy(16,16);
            printf("Salir");

            //indicador del cursor de seleccion
            color(10);
            recuadro(x,y,27,3);

            //comportamiento de teclas
            opcion=getch();
            switch(opcion)
            {
            case 80://ABAJO
                if(y==15)
                    y=6;
                else
                    y+=3;
                break;
            case 72://ARRIBA
                if(y==6)
                    y=15;
                else
                    y-=3;
                break;
            }
        }
        color(7);
        switch(y)
        {
        case 6:
            system("cls");
            menuVerArchivos(arrTXTs,validosTXTs);
            system("pause");
            break;
        case 9:
            system("cls");
            menuOperacionesDeUsuario(motor,arrTXTs,validosTXTs);
            break;
        case 12:
            system("cls");
            menuOtros(motor);
            break;
        case 15:
            salir=1;
        }
    }
}

void menuVerArchivos(char archivos[][20], int validos)
{
    printf("Seleccione el archivo que desea ver:\n");
    int seleccion,x=0;
    char* texto;
    muestraTXTs(archivos,validos);
    scanf("%i",&seleccion);
    if (seleccion-1<validos && seleccion-1 >=0)
    {
        genArrDeUnDoc(&texto,&x, archivos[seleccion-1]);
        printf("%s\n",texto);
    }else
    {
        printf("Seleccion no valida\n");
    }
}

void menuOperacionesDeUsuario(nodoA* motor, char textos[][20],int validos)
{
    int y,x=14,opcion,salir=0;
    char frase[100];
    int id;
    while(salir!=1)
    {
        y=6;
        opcion=0;
        system("cls");
        while(opcion!=13)
        {
            color(9);
            recuadro(13,1,27,3);
            gotoxy(15,2);
            color(11);
            printf("Operaciones de Busqueda");

            int j = 6;
            while(j<=24)
            {
                color(0);
                recuadro(14,j,40,3);
                j+=3;
            }
            //opciones del menu
            color(7);
            gotoxy(16,7);
            printf("Buscar termino en algun texto");

            gotoxy(16,10);
            printf("Buscar termino en textos selecionados");

            gotoxy(16,13);
            printf("Buscar mas de un termino");

            gotoxy(16,16);
            printf("Buscar una frase completa");

            gotoxy(16,19);
            printf("Buscar el termino de mayor frecuencia");

            gotoxy(16,22);
            printf("Sugerir terminos similares");

            gotoxy(16,25);
            printf("Volver al menu anterior");

            //indicador del cursor de seleccion
            color(10);
            recuadro(x,y,40,3);

            //comportamiento de teclas
            opcion=getch();
            switch(opcion)
            {
            case 80://ABAJO
                if(y==24)
                    y=6;
                else
                    y+=3;
                break;
            case 72://ARRIBA
                if(y==6)
                    y=24;
                else
                    y-=3;
                break;
            }
        }
        color(7);
        switch(y)
        {
        case 6:
            system("cls");
            printf("Buscar termino en algun texto\n");
            printf("Ingrese termino a buscar en documentos\n");
            fflush(stdin);
            gets(frase);
            buscarTerminoEnTodosDocumentos(motor,frase,validos,textos);
            system("pause");
            break;
        case 9:
            system("cls");
            printf("Buscar termino en textos selecionados\n");
            int idDocs[10];
            int cant;
            muestraTXTs(textos,validos);
            printf("Ingrese termino\n");
            fflush(stdin);
            gets(frase);
            preguntarIDs(idDocs,&cant);
            buscarTerminoEnDocumentos(motor,frase,idDocs,cant);
            system("pause");
            break;
        case 12:
            system("cls");
            printf("Buscar mas de un termino\n");
            muestraTXTs(textos,validos);
            printf("Ingrese terminos a buscar\n");
            fflush(stdin);
            gets(frase);
            printf("ingrese id del documento: \n");
            scanf("%i", &id);
            buscarMasDeUnTermino(motor,frase,id);
            system("pause");
            break;
        case 15:
            system("cls");
            printf("Buscar una frase completa\n");
            muestraTXTs(textos,validos);
            printf("Ingrese frase: \n");
            fflush(stdin);
            gets(frase);
            nodoT* resultado= buscarFrase(motor,frase);
            if(resultado)
            {
                printf("La frase se encontro en: \n Documento: %i \n Posicion %i\n\n",resultado->idDOC,resultado->pos);
            }
            else
            {
                printf("No se encontro la frase ingresada\n\n");
            }
            system("pause");
            break;
        case 18:
            system("cls");
            printf("Buscar el termino de mayor frecuencia\n");
            muestraTXTs(textos,validos);
            printf("Seleccione el documento: \n");
            scanf("%i",&id);
            nodoA* frecuente = palabraMayorFrecuenciaDeUnDoc(motor,id);
            if(frecuente)
            {
                int frecuencia = frecuenciaPorDocumento(frecuente->ocurrencias,id);
                if(frecuencia>0)
                {
                    printf("La palabra de mayor frecuencia del documento %i es:\n \"%s\" con %i ocurrecias\n",id,frecuente->palabra,frecuencia);
                }
                else
                {
                    printf("No se encontraron palabras\n");
                }
            }
            system("pause");
            break;
        case 21:
            system("cls");
            printf("Sugerir terminos similares\n");
            printf("Ingrese termino: \n");
            fflush(stdin);
            gets(frase);
            nodoA* sugerencia = sugerirPalabra(motor,frase);
            if (sugerencia && Levenshtein(frase,sugerencia->palabra)<=3)
            {
                if( Levenshtein(frase,sugerencia->palabra)==0)
                {
                    buscarTerminoEnTodosDocumentos(motor,frase,validos,textos);
                }else
                {
                    printf("Quisiste decir \"%s\" en vez de \"%s\"?\n",sugerencia->palabra,frase);
                    buscarTerminoEnTodosDocumentos(motor,sugerencia->palabra,validos,textos);
                }
            }
            else
            {
                printf("No se encontraron palabras similares\n");
            }
            system("pause");
            break;
        case 24:
            salir=1;
        }
    }
}

void menuOtros(nodoA* motor)
{
    int y,x=14,opcion,salir=0;

    while(salir!=1)
    {
        y=6;
        opcion=0;
        system("cls");
        while(opcion!=13)
        {
            color(9);
            recuadro(14,1,27,3);
            gotoxy(15,2);
            color(11);
            printf("Funciones Adicionales");

            int j = 6;
            while(j<=12)
            {
                color(0);
                recuadro(14,j,27,3);
                j+=3;
            }

            //opciones del menu
            color(7);

            gotoxy(16,7);
            printf("Mostrar arbol de datos");

            gotoxy(16,10);
            printf("Mostrar diccionario");

            gotoxy(16,13);
            printf("Volver al menu anterior");


            //indicador del cursor de seleccion
            color(10);
            recuadro(x,y,27,3);

            //comportamiento de teclas
            opcion=getch();
            switch(opcion)
            {
            case 80://ABAJO
                if(y==12)
                    y=6;
                else
                    y+=3;
                break;
            case 72://ARRIBA
                if(y==6)
                    y=12;
                else
                    y-=3;
                break;
            }
        }
        color(7);
        switch(y)
        {
        case 6:
            system("cls");
            mostrarArbol(motor);
            system("pause");
            break;
        case 9:
            system("cls");
            mostrarDiccionario();
            system("pause");
            break;
        case 12:
            salir=1;
        }
    }
}

void color(int x)                                                               /// Cambia la combinacion de color de fondo y frente
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void gotoxy(int X,int Y)                                                        /// Cambia las coordenadas del cursor
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=X;
    dwPos.Y=Y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void hidecursor(int ver)                                                        /// funcion para mostrar o esconder el cursor
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = ver;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void recuadro(int x,int y,int ancho,int alto)
{
    int i=0;
    ancho-=2;
    alto-=2;
    gotoxy(x,y);
    printf("%c",218);
    x+=1;
    for(i=0; i<ancho; i++)
    {
        gotoxy(x,y);
        printf("%c",196);
        x++;
    }
    gotoxy(x,y);
    printf("%c",191);
    x-=ancho+1;
    y++;
    for(i=0; i<alto; i++)
    {
        gotoxy(x,y);
        printf("%c",179);
        gotoxy(x+ancho+1,y);
        printf("%c",179);
        y++;
    }
    gotoxy(x,y);
    printf("%c",192);
    x+=1;
    for(i=0; i<ancho; i++)
    {
        gotoxy(x,y);
        printf("%c",196);
        x++;
    }
    gotoxy(x,y);
    printf("%c",217);
}
