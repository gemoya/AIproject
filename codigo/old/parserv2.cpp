#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int parserv2(char *filename, int **vars, int ***covertureMatrix, int ***preferencesMatrix){


    int n, d, s;
    int i, j temp;

    FILE *input;

    input = fopen(filename, "r");
    if (input  == NULL ){
        printf("File not found\n");
        return -1;
    }

    fscanf(input, "%d\t%d\t%d", &vars[0],&vars[1],&vars[2]);
    cout << vars[0] << vars[1] << vars[2] << endl;

    n = vars[0];
    d = vars[1];
    s = vars[2];


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


    int **preferencesMatrix = (int **)malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) preferencesMatrix[i] = (int *)malloc((d*s) * sizeof(int));


    // reading preferences matrix from dataset
    for(i = 0; i<n; i++){
        for(j = 0; j<(d*s); j++){
            fscanf(input, "%d\t", &temp);
            //nurses[i].preferences.push_back(temp);
            
            cout << nurses[i].preferences[j] << "\t";
        }
        cout << endl;
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        //cout << covertureMatrix[i][0] << covertureMatrix[i][1] << covertureMatrix[i][2] << covertureMatrix[i][3] << endl;
    }


    return 0;

}


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