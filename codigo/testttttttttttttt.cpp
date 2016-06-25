#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "nursescheduling.hpp"
#include "helpers.hpp"

using namespace std;
using Matrix = vector < vector<int> >;


int parserv2(char **filename, int **vars, int ***covertureMatrix, int ***preferencesMatrix, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix){


    int n, d, s;
    int i, j, temp;

    int false1, false2;


    FILE *input;

    input = fopen(*filename, "r");
    if (input  == NULL ){
        printf("File not found\n");
        return -1;
    }

    fscanf(input, "%d\t%d\t%d", &((*vars)[0]),&((*vars)[1]),&((*vars)[2]));
    //cout << vars[0] << vars[1] << vars[2] << endl;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    cout << n << " " << d << " " << s << endl;

    *covertureMatrix = (int **)malloc(d * sizeof(int*));
    for(i = 0; i < d; i++) (*covertureMatrix)[i] = (int *)malloc(s * sizeof(int));

    // building covertureMatrix from dataset
    for(i = 0; i<d; i++){
        for(j = 0; j<s; j++){
            fscanf(input, "%d\t", &((*covertureMatrix)[i][j]));
        }
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        cout << (*covertureMatrix)[i][0] << (*covertureMatrix)[i][1] << (*covertureMatrix)[i][2] << (*covertureMatrix)[i][3] << endl;
    }


    *preferencesMatrix = (int **)malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) (*preferencesMatrix)[i] = (int *)malloc((d*s) * sizeof(int));


    // reading preferences matrix from dataset
    for(i = 0; i<n; i++){
        for(j = 0; j<(d*s); j++){
            fscanf(input, "%d\t", &temp);
            //nurses[i].preferences.push_back(temp);
            //cout << nurses[i].preferences[j] << "\t";
            (*preferencesMatrix)[i][j] = temp;
            cout << (*preferencesMatrix)[i][j] << " ";
        }
        cout << endl;
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        //cout << covertureMatrix[i][0] << covertureMatrix[i][1] << covertureMatrix[i][2] << covertureMatrix[i][3] << endl;
    }

    // repeated data
    fscanf(input, "%d\t%d", &false1, &false2);

    *consNurseAssigments = new int[2];
    fscanf(input, "%d\t%d", &((*consNurseAssigments)[0]), &((*consNurseAssigments)[1]));


    *consNurseTurns = new int[2];
    fscanf(input, "%d\t%d", &((*consNurseTurns)[0]), &((*consNurseTurns)[1]));

    *consMatrix =  (int **)malloc(4 * sizeof(int*));
    for(i = 0; i < 3; i++) (*consMatrix)[i] = (int *)malloc( s*sizeof(int));


    for(i = 0; i < 3; i++){
        fscanf(input, "%d\t%d\t%d\t%d", &((*consMatrix)[i][0]), &((*consMatrix)[i][1]), &((*consMatrix)[i][2]), &((*consMatrix)[i][3]));
    }



    return 0;
}


int parserToVars(int **vars, int ***preferencesMatrix, nurse **nurses){

    int n, d, s;
    int i, j;
    int temp;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    *nurses = new nurse[n];
    for(i = 0; i<n; i++){
        (*nurses)[i].id = i+1;
        for(j = 0; j<(d*s); j++){
            temp = (*preferencesMatrix)[i][j];
            (*nurses)[i].preferences.push_back(temp);
        }
    }

    return 0;
}

int heuristics(int **vars, nurse **nurses, int **sortedIds, int ***heuristicMatrix){

    int n, d, s;
    int i, j;
    int temp;



    n = (*vars)[0]; d = (*vars)[1]; s = (*vars)[2];

    *heuristicMatrix = (int **)malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) (*heuristicMatrix)[i] = (int *)malloc((3 * sizeof(int)));

    for(i = 0; i<n; i++){
        for(j = 0; j<(d*s); j++){
            if ((*nurses)[i].preferences[j] == 1){
                (*nurses)[i].counter[0]++;

            } else if ((*nurses)[i].preferences[j] == 2){
                (*nurses)[i].counter[1]++;

            } else if ((*nurses)[i].preferences[j] == 3){
                (*nurses)[i].counter[2]++;
            }
        }
        cout << "Nurse id: " << (*nurses)[i].id  << " 1s:" << (*nurses)[i].counter[0] << " 2s:" << (*nurses)[i].counter[1] << " 3s:" << (*nurses)[i].counter[2] << endl;

    }


    for(i = 0; i<n; i++){
        for(j = 0; j<(3); j++){
            (*heuristicMatrix)[i][j] = (*nurses)[i].counter[j];
        }
    }




    return 0;

}


void traspose(int **vars, int ***preferencesMatrix, int ***preferencesMatrixT){

    int n, d, s;
    int i, j;
    int temp;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];


    *preferencesMatrixT = (int **)malloc((d*s) * sizeof(int*));
    for(i = 0; i < (d*s); i++) (*preferencesMatrixT)[i] = (int *)malloc((n) * sizeof(int));

    for(i = 0; i < n; i++){
        for(j=0; j<(d*s); j++){
            (*preferencesMatrixT)[j][i] = (*preferencesMatrix)[i][j];
        }
    }


}


void parseDomains(int **vars, int ***preferencesMatrixT,  vector<Matrix> &m){

    int n,d,s;
    int i,j;
    int temp;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    for(i = 0; i < (d*s); i++){
        for(j = 0; j < n; j++){
            m[i][0][j] = (*preferencesMatrixT)[i][j];
            m[i][1][j] = j+1;

        }
    }

}

void applyHeuristic(int **vars, vector<Matrix> &m){

    int n,d,s;
    int i,j;
    int N;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    for(i = 0; i < (d*s); i++){
            //N = sizeof(m[i][0])/sizeof(int);
            quickSort( (m[i][0]), (m[i][1]), 0, n-1);
    }


}

void matrixToVec(int **vars, int ***covertureMatrix, vector<int> &v){

    int n,d,s;
    int i,j;
    int element;
    int counter = 0;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    for(i = 0; i < d; i++){
        for(j = 0; j<(s); j++){
            element = (*covertureMatrix)[i][j];
            v[counter] = element;
            //cout << v.back() << endl;
            counter++;
        }
    }

    cout << v.size() << endl;


    for(i = 0; i <v.size(); i++){
        cout << v[i] << endl;
    }


}




bool searchDayCons(int i, int id, vector< list<int> > &assignmentVector){

    int shift = (i)%4;
    //int day = (i)/4;
    bool var1,var2,var3;
    int s1,s2,s3;

    if (shift == 0) return false;
    
    else if (shift == 1){
        s1 = (i) - 1;
        s2 = (i) + 1;
        s3 = (i) + 2;

        return (((assignmentVector[s1].end()) != find(assignmentVector[s1].begin(), assignmentVector[s1].end(), (id)+1 )) || ((assignmentVector[s2].end()) != find(assignmentVector[s2].begin(), assignmentVector[s2].end(), (id)+1 )) || ((assignmentVector[s3].end()) != find(assignmentVector[s3].begin(), assignmentVector[s3].end(), (id)+1 ))  );


    } else if (shift == 2){
        s1 = (i) - 2;
        s2 = (i) - 1;
        s3 = (i) + 1;

        return (((assignmentVector[s1].end()) != find(assignmentVector[s1].begin(), assignmentVector[s1].end(), (id)+1 )) || ((assignmentVector[s2].end()) != find(assignmentVector[s2].begin(), assignmentVector[s2].end(), (id)+1 )) || ((assignmentVector[s3].end()) != find(assignmentVector[s3].begin(), assignmentVector[s3].end(), (id)+1 ))  );
    } else {
        s1 = (i) - 2;
        s2 = (i) - 2;
        s3 = (i) - 1;

        return (((assignmentVector[s1].end()) != find(assignmentVector[s1].begin(), assignmentVector[s1].end(), (id)+1 )) || ((assignmentVector[s2].end()) != find(assignmentVector[s2].begin(), assignmentVector[s2].end(), (id)+1 )) || ((assignmentVector[s3].end()) != find(assignmentVector[s3].begin(), assignmentVector[s3].end(), (id)+1 ))  );
    
    }
    
}

bool searchGBJ(int i, int id, vector< list<int> > &assignmentVector){

    return ((assignmentVector[i].end()) != find(assignmentVector[i].begin(), assignmentVector[i].end(), id+1));
}

//void mfc(int **vars, vector<Matrix> &assigmentMatrix, vector<Matrix> &m,  vector<int> &v, vector<list<int>> &assigmentVector, vector<list<list<int>>> &domains){
//}

//void assign(int **vars, vector<Matrix> &assigmentMatrix, vector<Matrix> &m,  vector< int > &v, vector < list < int > > &assigmentVector,vector< list < list<int> > > &domains){

// vars = variables, assigmentMatrix= matriz de asignacion, m = dominios + preferencias, covertureVector = matriz de covertura como vector lineal, filters = filtros para restricciones, movements = movimientos que se realizan

void assign(int **vars, vector<list<int>> &assignmentVector ,Matrix &assignmentMatrix, Matrix &assignmentPrefsMatrix, vector<Matrix> &m, vector<int> &covertureVector, filter **filters, vector<list<int>> &movements, constraints **cons, int *broken ){

    int n,d,s;
    int i,j;
    // v vector de covertura
    int requirement;
    int bt = 0;

    int rowCounter;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];
    /*
    vector<int> linear(d*s*n);
    for(i = 0; i < d*s; i++){
        for (j = 0; i < n; ++i)
        {
            
        }
    }*/

    /*for(i = 0; i < (d*s); i++){
        rowCounter = 0;
        requirement = covertureVector[i];
        if ((requirement == 0) && ((i%s) != 3)){
            continue;
        }
            for(j = 0; j < n; j++){
                //cout << "test 2" << endl;
                bool lala = searchDayCons(i, j, assignmentVector);
                //cout << lala << endl;
                //if (rowCounter == requirement) {
                //    continue;
                } if (searchDayCons(i, m[i][1][j]-1, assignmentVector)){
                  //  continue;
                //} //else if ((requirement == 1) && (searchGBJ(i,j, assignmentVector))){
                 else {
                    // cout << "else" << endl;
                    assignmentMatrix[i][ m[i][1][j]-1] = 1;
                    assignmentPrefsMatrix[i][j] = m[i][0][j];
                    assignmentVector[i].push_back(m[i][1][j]);
                    rowCounter++;
                    //print
                }
            }
       // }*
    }*/




}

void recursiveSearch(vector<int> &v, Matrix &m, int i, int max){
    bool constraints = true;
    if (i < max){
        for (int j = 0; j < 2; j++){
            if (constraints == true){
                v[i] = j;
                if (i != max -1){
                    recursiveSearch(v,m,i+1,max);
                } else {
                    cout << "vector: [";
                    for(int k = 0; k<v.size(); k++){
                        cout <<  v[k] << "," ;
                    }
                    cout << "]" << endl;

                    _1dTo2d(v,m,2,2);
                    printMatrix(m,2, 2);

                }

            }

        }
    }

}


void printMatrix(Matrix &m, int rows, int columns){


    cout << "Printing Matrix" << endl;
    for (int i = 0; i<rows; i++){
        for(int j = 0; j< columns; j++){
            cout << m[i][j] << " ";

        }
        cout << endl;
    }
    cout << endl;

}

void _1dTo2d(vector<int> &v, Matrix &m, int rows, int columns){

    int j = 0;
    for (int i = 0; i<(rows*columns); i++){

        if((i != 0) && ((i%columns) == 0) ){
            j++;

        }

        //cout << "i: " << i << " " << " i/rows-1:  " << i/(rows-1) << endl;
        m[j][i%columns] = v[i];

    }

}

/*
void penalize(int *objetive, int *constraint){
    
    if ((*constraint) == 1){
        (*objetive)++;
    } else if ((*constraint) == 2){
        (*objetive)++++;
    } else if ((*constraint) == 3){
    
    } else if ((*constraint) == 4){
    
    } else if ((*constraint) == 5){
    
    } else if ((*constraint) == 6){
    
    }
}
*/
Status API Training Shop Blog About
