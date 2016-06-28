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

int checkPreferences(vector<vector<int>> &v, int ***preferencesMatrixT);

int checkPenalizations(vector<vector<int>> &v, int ***preferencesMatrixT, int **vars, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix);

int checkObjetive(int totalPrefs, int totalPenalizations);


// parser from file to arrays
int parserv2(char **filename, int **vars, int ***covertureMatrix, int ***preferencesMatrix, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix);



// traspose matrix of preferences
void traspose(int **vars, int ***preferencesMatrix, int ***preferencesMatrixT);

// parse domain problem: nurses and preferences to a matrix of 2*N vector 
void parseDomains(int **vars, int ***preferencesMatrixT,  vector<Matrix> &m);

// apply heuristic sort on matrix of nurses and preferences per turn
void applyHeuristic(int **vars, vector<Matrix> &m);

// transform coverture matrix to a vector of d*s size
void matrixToVec(int **vars, int ***covertureMatrix, vector<int> &v);


void printMatrix(Matrix &m, int rows, int columns);


void _1dTo2d(vector<int> &v, Matrix &m, int rows, int columns);

#endif
