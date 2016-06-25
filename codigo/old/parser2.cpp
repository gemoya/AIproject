#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct problemData {
    int n;
    int d;
    int s;
    int **matrix;
    
};

struct nurse {
    int id;
    vector<int> preferences;
    vector<string> assigments;
    // more
};

typedef struct nurse Nurse;
Nurse *nurses;
Nurse *heuristicNurses; // maybe not necesary



void fileParser(char *inputFile, Nurse **ns, struct problemData *data){

    int n, d, s;
    int i, j, temp;
    FILE *input;

    input = fopen(inputFile, "r");
    if (input  == NULL ){
        printf("File not found\n");
    }

    fscanf(input, "%d\t%d\t%d", &(n),&(d),&(s));
    data->n = n;
    data->d = d;
    data->s = s;
    cout << data->n << data->d << data->s << endl;


    int **covertureMatrix = (int **)malloc(d * sizeof(int*));
    for(i = 0; i < d; i++) covertureMatrix[i] = (int *)malloc(s * sizeof(int));

    for(i = 0; i<d; i++){
        for(j = 0; j<s; j++){
            fscanf(input, "%d\t", &covertureMatrix[i][j]);
        }
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        cout << covertureMatrix[i][0] << covertureMatrix[i][1] << covertureMatrix[i][2] << covertureMatrix[i][3] << endl;
    }

    data->matrix = covertureMatrix;
    *ns = (Nurse *)malloc(n * sizeof(Nurse));
    for(i = 0; i<n; i++){
        for(j = 0; j<(d*s); j++){
            fscanf(input, "%d\t", &temp);
            cout << "gg" << endl;
            ns[i]->preferences.push_back(temp);
            cout << ns[i]->preferences[j] << "\t";
        }
        cout << endl;

    }
}

void applyHeuristic(Nurse *nurses, struct problemData *data);

int main (int argc, char **argv) {

    struct problemData data;

    fileParser(argv[1], &nurses, &data);

    return 0;
}