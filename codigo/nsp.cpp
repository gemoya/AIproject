#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
	
#include "nursescheduling.hpp"
#include "helpers.hpp"
#include "assignment.hpp"
using namespace std;

// defining a nurse
/*struct nurse {
    int id;
    vector<int> preferences;
    vector<string> assigments;
    // more
};
*/
//typedef struct nurse Nurse;
//Nurse *nurses;
//Nurse *heuristicNurses; // maybe not necesary

using Matrix = vector < vector<int> >;


int main (int argc, char **argv) {


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

    int *sortedIds;
    int **heuristicMatrix;
	    
    nurse *nurses;

    //int a = parserv2(&argv[1], &vars, &covertureMatrix, &preferencesMatrix);
    int a = parserv2(&argv[1], &vars, &covertureMatrix, &preferencesMatrix, &consNurseAssigments, &consNurseTurns, &consMatrix);
    
    traspose(&vars, &preferencesMatrix, &preferencesMatrixT);

    

    int n,d,s;
    n = (vars)[0];
    d = (vars)[1];
    s = (vars)[2];

    int i,j;


    //int c = heuristics(&vars, &nurses, &sortedIds, &heuristicMatrix);

    // a matrix of vectors with 2d vectors of nurses and it preferences
    vector<Matrix> m(d*s, vector<vector<int>>(2, vector<int>(n)));

    parseDomains( &vars, &preferencesMatrixT, m);

    

    // a copy  matrix of previous matrix to be sorted
    vector<Matrix> m2(d*s, vector<vector<int>>(2, vector<int>(n)));
    m2 = m;

    applyHeuristic(&vars, m2); // sorting matrix

    // matrix coverture to vector
    vector < int > covertureVector(d*s);
    cout << covertureVector.size() << endl;
    matrixToVec(&vars, &covertureMatrix, covertureVector);

    // matrix of assigments
    // 1 si enfermera se asigna al turno, 0 en caso contrario
    Matrix assignmentMatrix(d*s, vector<int>(n) );
    // vector of assignments, listas enfermeras asignadas por cada turno en orden
    vector< list<int> > assignmentVector(d*s);

    // matrix of assigned preferences
    Matrix assignmentPrefsMatrix(d*s, vector<int>(n) );


    //domainVector[i][j][0] => 1
    //domainVector[i][j][1] => 0 
    vector<vector<vector<int>>> domainsVector(n,vector<vector<int>>(d*s,vector<int>(2,1)));
    vector<list<int>> preferencesVector(d*s);


    //vector<int> testo(n*d*s,0);
    Matrix testo2(d*s,vector<int>(n,0));
    //printMatrix(testo2, 2,4);
    //recursiveSearch(testo,domainsVector,testo2,0,n*d*s);

    vector<vector<int>> testos(2,vector<int>(2));
    // little test
    //recursiveSearch2(testos,domainsVector,0,0,2,2);
    //recursiveSearch2(testo2,domainsVector,timeDomains,0,0,d*s,n);



    vector<list<int>> testo3(d*s);
    vector< vector< vector<int> > > domainsVec(1,(vector<vector<int>>(d*s,vector<int>(n,1))));


    //initializeDomains(d,d*s,n)

    //recursiveSearch4(testo3, domainsVec, covertureVector, 0, d*s);

    vector<vector<vector<int>>> doms(d*s,(vector<vector<int>>(n,(vector<int>(2)))));
    vector<vector<list<int>>> estructura(d*s,(vector<list<int>>(n)));

    for (int i = 0; i<d*s; i++){
        for(int j = 0; j<n; j++){
            for(int k = 0; k<2; k++){
                doms[i][j][k] = k;
            }
        }
    }


    Matrix juguete1(4,vector<int>(5));
    vector<vector<vector<int>>> juguete2(4,(vector<vector<int>>(5,(vector<int>(2)))));
    vector<vector<list<int>>> juguete3(4,(vector<list<int>>(5)));

    vector<int> juguete4 = {1,4,1,2};


    for (int i = 0; i<4; i++){
        for(int j = 0; j<5; j++){
            for(int k = 0; k<2; k++){
                juguete2[i][j][k] = k;
            }
        }
    }

    recursiveS(testo2, doms,estructura, covertureVector, 0,0 , d*s, n);
    //recursiveS(juguete1,juguete2,juguete3,juguete4, 0,0,4,5);





    return 0;

}
