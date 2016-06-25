#ifndef NURSESCHEDULING_H
#define NURSESCHEDULING_H
using namespace std;
using Matrix = vector < vector<int> >;



struct nurse {
    int id;
    vector<int> preferences;
    vector<string> nurseAssigments;
    // more
    int *counter = new int[3]; //index 0 to 1s, 1 to 2s, 2 to 3s
};


struct nursePerTurn {

	int id;
	int pref;

};

struct filter {

     //   int vector < list<int>> filter1;
     //   int vector < list<int>> filter2;
     //   int vector < list<int>> filter3;
     //   int vector < list<int>> filter4;
};

struct constraints {

        
    int total = 0;
	int consecutiveShifts = 0;

    int *consecutiveSameShift = new int[4];
    int *assigmentsPerShift = new int[4];

    int pay = 0 ;

};




// parser from file to arrays
int parserv2(char **filename, int **vars, int ***covertureMatrix, int ***preferencesMatrix, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix);

// parser form arrays to other variables
int parserToVars(int **vars,  int ***preferencesMatrix, nurse **nurses);

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









// bool checkDomain(vector<vector<int>> &d, int index, int n);

// bool checkCoverture(vector<int> &v, int index);


// void saveDomain(vector<vector<vector<vector<int>>>> &t, vector<vector<vector<int>>> &d);

// // only one turn per day avaible
// void mfc(vector<vector<vector<int>>> &d, vector<vector<vector<vector<int>>>> &t,  int nurse, int shift);

// // recursive deph search on a linear vector
// void recursiveSearch(vector<int> &v, vector<vector<int>> &d, Matrix &m, int i, int max);

// void recursiveSearch2(vector<vector<int>> &v, vector<vector<vector<int>>> &d, vector<vector<vector<vector<int>>>> &t,  int i, int j, int imax, int jmax);

//void recursiveSearch3(vector<vector<int>> &v, vector<vector<int>> &d, int i, int j, int imax, int jmax);

// function to print matrix for a given matrix and number of rows and columns
//


void filterSameDay(vector<vector<int>> &d, int nurse, int shift);

bool checkOut(vector<int> coverture, vector<vector<int>> domainTime, vector<list<int>> v, int actual);



int sumNurses(vector<int> row);

void recursiveSearch3(vector<list<int>> &v, vector<vector<vector<int>>> &d, vector<int> &coverture, int i, int imax);

void recursiveSearch4(vector<list<int>> &v, vector<vector<vector<int>>> &d, vector<int> &coverture, int i, int imax);
void printMatrix(Matrix &m, int rows, int columns);
// parse 1D vector a 2D vector Matrix, for a given vector, number
// of rows and columns. for a index in vector this are index/(rows -1) for matrix rows
// and index%columns the column index 
void _1dTo2d(vector<int> &v, Matrix &m, int rows, int columns);

#endif
