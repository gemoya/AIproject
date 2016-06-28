#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
	
#include "nursescheduling.hpp"
#include "helpers.hpp"
#include "assignment.hpp"
using namespace std;



using Matrix = vector < vector<int> >;

int main (int argc, char **argv) {

    clock_t start = clock();
    cout << "Iniciando" << endl;
    int *vars = new int[3];
    int **covertureMatrix;
    int **preferencesMatrix;

    int **preferencesMatrixT;

    // restricciones de enfermeras
    int *consNurseAssigments; // asignaciones min y max
    int *consNurseTurns; // turnos consecutivos min y max


    // restricciones de turnos
    int **consMatrix; // turnos consecutivos iguales min y max, asignaciones por turno min y max


    int a = parserv2(&argv[1], &vars, &covertureMatrix, &preferencesMatrix, &consNurseAssigments, &consNurseTurns, &consMatrix);
    
    traspose(&vars, &preferencesMatrix, &preferencesMatrixT);
    int n,d,s;
    n = (vars)[0];
    d = (vars)[1];
    s = (vars)[2];


    vector < int > covertureVector(d*s);
    matrixToVec(&vars, &covertureMatrix, covertureVector);

    Matrix assignmentM(d*s,vector<int>(n,0));


    vector<vector<vector<int>>> doms(d*s,(vector<vector<int>>(n,(vector<int>(2)))));
    vector<vector<list<int>>> estructura(d*s,(vector<list<int>>(n)));

    for (int i = 0; i<d*s; i++){
        for(int j = 0; j<n; j++){
            for(int k = 0; k<2; k++){
                doms[i][j][k] = k;
            }
        }
    }


    struct s inputs;
    inputs.vars = vars;
    inputs.preferencesMatrixT = preferencesMatrixT;
    inputs.consNurseAssigments = consNurseAssigments;
    inputs.consNurseTurns = consNurseTurns;
    inputs.consMatrix = consMatrix;


    recursiveS(assignmentM, doms,estructura, covertureVector, &inputs,0,0 , d*s, n, start);





    cout << "El tiempo de ejecucion fue: " << (double)(clock() - start)/CLOCKS_PER_SEC << " segundos." << endl;;
    return 0;

}
