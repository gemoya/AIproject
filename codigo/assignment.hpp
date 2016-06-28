#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
using namespace std;
using Matrix = vector < vector<int> >;

//funcion que deshace los filtros uniendo la estructura con los dominios, 
// recibe como parametros el vector tridimensional de dominios y el vector 2d con listas estructura
void undoFilters(vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura);
//Funcion que aplica MFC, recibe la matriz de asignacion como v, el triple vector de dominios, la estructura de filtros, las coberturas como un vector de coberturas, el turno y enfermera
// actual
// Filtra los turnos sgtes al de los parametros y lo hace solo si se esta asegurada la cobertura para los turnos restantes en el dia
bool minimalFC(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, vector<int> covertureVector, int shift, int nurse);

// funcion que verifica que existan unos en los dominios , recibe los dominios, una enfermera y el turno
// retorna true si lo encuentra, false en caso contrario
bool hasone(vector<vector<vector<int>>> &dom, int shift, int nurse);

// funcion que verifica que se pueda cumplir la cobertura recibe la matriz de asignacion como v, la cobertura como un vector covertureVector,
// los dominios, un turno y enfermera actual que utiliza como margen para comenzar a chequear
// retorna true si se cumple, false en caso contrario,
// sirve para construir solucion
bool coverture(vector<vector<int>> &v,vector<int> &covertureVector, vector<vector<vector<int>>> &dom, int shift, int nurse);
// busqueda en profundidad recursiva, recibe la matriz de asignacion, el triple vector de dominios, la estructura 
// para los elemenos filtrados, el vector de cobertura, una sruct de tipo s, que sirve como auxiliar para almacenar variables que seran
// pasadas a los chequeos de preferencias y penalizaciones, tambien recibe un indice i,j de fila columna para iniciar la busqueda, y un imax y jmax como limites
// de esta en la matriz.
// esta funcion imprime las asignaicones encontradas y llama a minimalFC, coverture, checkCoverture
// es la funcion mas relevante.
void recursiveS(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> estructura, vector<int> &covertureVector, s *input, int i, int j, int imax, int jmax, clock_t start);

// chequeo de cobertura de soluciones completas, recibe la matriz de asignacion como v, y las coberturas como un vector.
// sirve para evaluar los procesos en que la recursion comienza ir "hacia atras"
// retorna true si se cumple la cobertura
// false en caso contrairo
bool checkCoverture(vector<vector<int>> &v, vector<int> &covertureVector);

// funcion auxiliar que imprime dominios
void printDomain(vector<vector<vector<int>>> &d);
// funcion auxiliar que imprime la estructura
void printStruct(vector<vector<list<int>>> &estructura);

#endif