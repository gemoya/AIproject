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

// parser form arrays to other variables
//int parserToVars(int **vars,  int ***preferencesMatrix, nurse **nurses);

//int heuristics(int **vars, nurse **nurses, int **sortedIds, int ***heuristicMatrix);

// traspose matrix of preferences
void traspose(int **vars, int ***preferencesMatrix, int ***preferencesMatrixT);

// parse domain problem: nurses and preferences to a matrix of 2*N vector 
void parseDomains(int **vars, int ***preferencesMatrixT,  vector<Matrix> &m);

// apply heuristic sort on matrix of nurses and preferences per turn
void applyHeuristic(int **vars, vector<Matrix> &m);

// transform coverture matrix to a vector of d*s size
void matrixToVec(int **vars, int ***covertureMatrix, vector<int> &v);
// search in day assigments to satisfy rule 1 assign per day
//bool searchDayCons(int i, int id, vector< list<int> > &assignmentVector);

//bool searchGBJ(int i, int id, vector< list<int> > &assignmentVector);

//void assign(int **vars, vector<Matrix> &assigmentMatrix, vector<Matrix> &m, vector< int > &v, vector< list < list<int> > > &domains);
//void assign(int **vars, Matrix &assigmentMatrix, Matrix &assigmentPrefsMatrix, vector<Matrix> &m, vector<int> &covertureVector, filter **filters, vector<list<int>> &movements, constraint **cons, int *broken);
//void assign(int **vars, vector<list<int>> &assignmentVector ,Matrix &assignmentMatrix, Matrix &assignmentPrefsMatrix, vector<Matrix> &m, vector<int> &covertureVector, filter **filters, vector<list<int>> &movements, constraints **cons, int *broken );


void printMatrix(Matrix &m, int rows, int columns);
// parse 1D vector a 2D vector Matrix, for a given vector, number
// of rows and columns. for a index in vector this are index/(rows -1) for matrix rows
// and index%columns the column index 
void _1dTo2d(vector<int> &v, Matrix &m, int rows, int columns);

#endif
