# MotorDeBusqueda
TPFinal

/// diccionario.h 
Se encarga de leer el directorio en el que se encuentra el proyecto, produce un archivo binario de terminos 
basado en hasta 10 documentos de texto (.txt).

void genArrDeUnDoc(char**, int*, char*); 
Consume un archivo txt y genera un arreglo de caracteres.

void cargarUnDocEnArchDicc(char*, int, int);
Escribe en diccionario.bin cada palabra de cada texto.

int extension(char*, char*);
Devuelve 1 si luego de la ultima ocurrencia de '.' es igual al segundo parametro.

void genArregloDeTXTs(char[][20], int*);
Abre el directorio y genera un arreglo de strings con los archivos de textos encontrados.

void genArchDicc(char[][20], int*);
Elimina el diccionario previo y genera uno actualizado. Persiste un arreglo de strings con los documentos de texto.

void mostrarDiccionario(void);
Muestra el contenido del archivo diccionario.bin

void muestraTXTs(char[][20], int);
Muestra el arreglo de strings de documentos de texto.

void preguntarIDs(int[], int*);
Genera un arreglo de IDs seleccionados por el usuario.

/// motor.h
Esta libreria se encarga de consumir el archivo diccionario.bin y convertirlo en un arbol binario de busqueda.

nodoT* crearNodoPalabra(int, int);
Crea un nodo de tipo termino.

nodoA* existePalabra(nodoA*, char*);
Busca la existencia de una palabra en el arbol. Si la encuentra, retorna el nodo.

void insertarPalabra(nodoT**,int, int);
Inserta un nodoT en una lista de ocurrencias.

nodoA* crearNodoMotor (termino);
Crea un nodo de tipo arbol con la primer ocurrencia de una palabra.

void insertarNodoYPalabra(nodoA**,termino);
Inserta una palabra nueva en el arbol.

void cargaDatos(nodoA**);
Consume diccionario.bin y genera el arbol de busqueda.

void mostrarTermino (nodoT*);
Muestra una lista de ocurrencias.

void mostrarArbol (nodoA*);
Muestra el arbol.

/// operacionesDeUsuario.h

int frecuenciaPorDocumento(nodoT*, int);
Devuelve la cantidad de ocurrencias de un ID.

1. Buscar todas las apariciones de un término en algún documento (operación or).
void buscarTerminoEnTodosDocumentos(nodoA*, char*, int, char[][20]);
Informa la frecuencia de un termino en cada documento que aparece.

2. Buscar todas las apariciones de un término en un documento y otros  (operacion and).
void buscarTerminoEnDocumentos(nodoA*, char*, int*, int);
Informa si el termino esta presente en todos los documentos seleccionados.

void buscarTerminoEnDocumento(nodoA*, char*, int);
Auxiliar de buscarMasDeUnTermino.

void separarFrase(char[][20], char*, int*);
Toma un string y genera un arreglo de strings separados.

3. Buscar la aparición de más de un término en el mismo documento.
void buscarMasDeUnTermino(nodoA*, char*, int);
Informa la frencuencia de todos los terminos ingresados por el usuario en el documento seleccionado o su ausencia.

int ocurrenciaContigua(nodoT*, int, int, int);
Recorre una lista de ocurrencias y devuelve 1 si encuentra una ocurrencia con el ID del segundo parametro y una posicion contigua al tercer parametro. 0 en caso contrario.

int fraseRelativaAOcurrencia(nodoA*, char[][20], int, int, int);
Busca en el arbol la existencia de las palabras de un arreglo de strings y devuelve 0 si no se encuentra una de esas palabras o alguna palabra no tiene una ocurrencia contigua al quinto parametro.
Devuelve 1 si encuentra que la totalidad de la frase es contigua.

4. Buscar una frase completa (las palabras deben estar contiguas en alguno de los documentos).
nodoT* buscarFrase(nodoA*, char*);
Busca una frase (palabras contiguas) en alguno de los documentos. Retorna la ocurrencia de la primer palabra de la frase en caso de encontrarla.

5. Buscar la palabra de más frecuencia que aparece en un doc.
nodoA* palabraMayorFrecuenciaDeUnDoc(nodoA* motor, int);
Recorre el arbol en busca de la palabra con mayor frencuencia de un documento determinado. Retorna el nodo del arbol.

int Minimo(int, int); devuelve el minimo entre dos constantes.
int Levenshtein(char *,char *); devuelve la disntancia de levenshtein entre dos strings.

6. Utilizar la distancia de levenshtein en el ingreso de una palabra
   y sugerir similares a partir de una distancia <= 3.
nodoA* sugerirPalabra(nodoA*, char*);
Devuelve el nodo con la palabra de menor distancia de levenshtein relativa a la palabra ingresada.

/// menu.h

void menu();
Menu Principal.

void menuVerArchivos(char[][20], int);
Menu para ver los archivos de texto del directorio.

void menuOperacionesDeUsuario(nodoA*, char[][20],int);
Menu de operaciones de motor de busqueda.

void menuOtros(nodoA*);
Menu de operaciones extra.

void recuadro(int,int,int,int);
Genera un recuadro en una posicion determinada.

void color(int);
Cambia el color del fondo.

void gotoxy(int,int);
Cambia la posicion del cursor.

void hidecursor(int);
Oculta el cursor.
