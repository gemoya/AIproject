#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;





int main (int argc, char **argv) {

    int n, d s;

    int *vars = new int[3];
    int **covertureMatrix;
    int **preferencesMatrix;

    paserv2(&argv[1], &vars, &covertureMatrix, &preferencesMatrix);



    return 0;
}