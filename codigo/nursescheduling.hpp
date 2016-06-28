#ifndef NURSESCHEDULING_H
#define NURSESCHEDULING_H
using namespace std;
using Matrix = vector < vector<int> >;

struct s
{
    int *vars;
    int **preferencesMatrixT;
    int *consNurseAssigments;
    int *consNurseTurns;
    int **consMatrix;
    
};

//funcion que calcula las preferencias
//recibe la matriz de asignacion como v, y la matriz de preferencias como preferencesMatrixT
// retorna el valor de las preferencias totales 
int checkPreferences(vector<vector<int>> &v, int ***preferencesMatrixT);

//funcion que calcula las  penalizaciones
//recibe la matriz de asignacion como v, y la matriz de preferencias como preferencesMatrixT
// recibe los valores minimos y maximos de las restricciones duras.
// retorna el valor de las penalizaciones totales totales 
int checkPenalizations(vector<vector<int>> &v, int ***preferencesMatrixT, int **vars, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix);

//calcula el objetivo
int checkObjetive(int totalPrefs, int totalPenalizations);


// parser de archivo de entrada a variables
// recibe el archivo, matriz de covertura, de preferencias y variables asociadas a las restricciones
int parserv2(char **filename, int **vars, int ***covertureMatrix, int ***preferencesMatrix, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix);



//funcion auxiliar que traspone una matriz
void traspose(int **vars, int ***preferencesMatrix, int ***preferencesMatrixT);

//funcion auxiliar para parsear dominios, sirve para debug
void parseDomains(int **vars, int ***preferencesMatrixT,  vector<Matrix> &m);

/// funcion auxiliar para aplicar heuristicas, no en uso actualmente
void applyHeuristic(int **vars, vector<Matrix> &m);

// tfuncion auxiliar que transforma matrices en vectores
void matrixToVec(int **vars, int ***covertureMatrix, vector<int> &v);

//funcion auxiliar que imprime una matriz
void printMatrix(Matrix &m, int rows, int columns);
//funcion auxiliar que recibe un vector y entrega una trasnformacion de sus coordenads en 2d

void _1dTo2d(vector<int> &v, Matrix &m, int rows, int columns);

#endif
