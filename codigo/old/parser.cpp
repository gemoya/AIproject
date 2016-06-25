#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


// need a schedule matrix or something
// how to pass undefined variables as references to pointers params of functions?

// defining a nurse
struct nurse {
    
    int id;
    vector<int> preferences;
    vector<string> assigments;
    // more
};

typedef struct nurse Nurse;
Nurse *nurses;
Nurse *heuristicNurses; // maybe not necesary

// change nurses order to improve assigments
void heuristicNurses(Nurse *ns, vector<int> order);

// schedule nurses 
void makeSimpleSchedule();

// schedule nurses with HCs
void makeSchedule();

int main (int argc, char **argv) {

    int n, d, s;
    int i, j, temp;
    FILE *input;

    input = fopen(argv[1], "r");
    if (input  == NULL ){
        printf("File not found\n");
        return -1;
    }

    // getting first values from dataset
    fscanf(input, "%d\t%d\t%d", &n,&d,&s);
    cout << n << d << s << endl;

    nurses = new Nurse[n];

    int **covertureMatrix = (int **)malloc(d * sizeof(int*));
    for(i = 0; i < d; i++) covertureMatrix[i] = (int *)malloc(s * sizeof(int));

    // building covertureMatrix from dataset
    for(i = 0; i<d; i++){
        for(j = 0; j<s; j++){
            fscanf(input, "%d\t", &covertureMatrix[i][j]);
        }
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        cout << covertureMatrix[i][0] << covertureMatrix[i][1] << covertureMatrix[i][2] << covertureMatrix[i][3] << endl;
    }

    // reading preferences matrix from dataset
    for(i = 0; i<n; i++){
        nurses[i].id =i+1;
        for(j = 0; j<(d*s); j++){
            fscanf(input, "%d\t", &temp);
            nurses[i].preferences.push_back(temp);
            cout << nurses[i].preferences[j] << "\t";
        }
        cout << endl;
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        //cout << covertureMatrix[i][0] << covertureMatrix[i][1] << covertureMatrix[i][2] << covertureMatrix[i][3] << endl;
    }


    return 0;
}