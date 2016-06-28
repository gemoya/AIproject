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
        printf("No se encontro el archivo. Saliendo ...\n");
        return -1;
    }

    fscanf(input, "%d\t%d\t%d", &((*vars)[0]),&((*vars)[1]),&((*vars)[2]));
    //cout << vars[0] << vars[1] << vars[2] << endl;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    //cout << n << " " << d << " " << s << endl;

    *covertureMatrix = (int **)malloc(d * sizeof(int*));
    for(i = 0; i < d; i++) (*covertureMatrix)[i] = (int *)malloc(s * sizeof(int));

    // building covertureMatrix from dataset
    for(i = 0; i<d; i++){
        for(j = 0; j<s; j++){
            fscanf(input, "%d\t", &((*covertureMatrix)[i][j]));
        }
        //fscanf(input, "%d\t%d\t%d\t%d", &covertureMatrix[i][0],&covertureMatrix[i][1],&covertureMatrix[i][2], &covertureMatrix[i][3]);
        //cout << (*covertureMatrix)[i][0] << (*covertureMatrix)[i][1] << (*covertureMatrix)[i][2] << (*covertureMatrix)[i][3] << endl;
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
        //    cout << (*preferencesMatrix)[i][j] << " ";
        }
        //cout << endl;
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
    for(i = 0; i < 4; i++) (*consMatrix)[i] = (int *)malloc( s*sizeof(int));


    for(i = 0; i < 4; i++){
        fscanf(input, "%d\t%d\t%d\t%d", &((*consMatrix)[i][0]), &((*consMatrix)[i][1]), &((*consMatrix)[i][2]), &((*consMatrix)[i][3]));
    }

    return 0;
}

void traspose(int **vars, int ***preferencesMatrix, int ***preferencesMatrixT){

    int n, d, s;
    int i, j;

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
    int i;

    n = (*vars)[0];
    d = (*vars)[1];
    s = (*vars)[2];

    for(i = 0; i < (d*s); i++){
            //N = sizeof(m[i][0])/sizeof(int);
            quickSort( (m[i][0]), (m[i][1]), 0, n-1);
    }


}

void matrixToVec(int **vars, int ***covertureMatrix, vector<int> &v){

    int d,s;
    int i,j;
    int element;
    int counter = 0;

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

}



int checkPreferences(vector<vector<int>> &v, int ***preferencesMatrixT){

    int totalPrefs = 0;

    for(unsigned int i= 0; i<v.size(); i++){
        for(unsigned int j = 0; j< v[i].size(); j++){
            totalPrefs+= v[i][j]*((*preferencesMatrixT)[i][j] );
        }
    }

    return totalPrefs;

}

int checkPenalizations(vector<vector<int>> &v, int ***preferencesMatrixT, int **vars, int **consNurseAssigments, int **consNurseTurns, int ***consMatrix){
/*
    int *consNurseAssigments; // asignaciones min y max
    int *consNurseTurns; // turnos consecutivos min y max


    // restricciones de turnos
    int **consMatrix; // turnos consecutivos iguales min y max, asignaciones por turno min y max
*/
    int minAssignments = (*consNurseAssigments)[0];
    int maxAssignments = (*consNurseAssigments)[1];

    int minDaily = (*consNurseTurns)[0];
    int maxDaily = (*consNurseTurns)[1];



    int shift0Min = (*consMatrix)[0][2];

    int shift0Max = (*consMatrix)[0][3];

    int shift1Min = (*consMatrix)[1][2];
    int shift1Max = (*consMatrix)[1][3];
 
    int shift2Min = (*consMatrix)[2][2];
    int shift2Max = (*consMatrix)[2][3];
 
    int shift3Min = (*consMatrix)[3][2];
    int shift3Max = (*consMatrix)[3][3];

    


    int shift0MinCons = (*consMatrix)[0][0];
    int shift0MaxCons = (*consMatrix)[0][1];

    int shift1MinCons = (*consMatrix)[1][0];
    int shift1MaxCons = (*consMatrix)[1][1];
 
    int shift2MinCons = (*consMatrix)[2][0];
    int shift2MaxCons = (*consMatrix)[2][1];
 
    int shift3MinCons = (*consMatrix)[3][0];
    int shift3MaxCons = (*consMatrix)[3][1];

    int n,d,s;

    n = (*vars)[0];
    //d = (*vars)[1];
    s = (*vars)[2];



    int totalPenalizations = 0;

    // total de turnos trabajados
    vector<int> totals(n);

    vector<int> dailyAux(n,0);
    // total turnos/dias trabajados consecutivos
    vector<int> dailyCounter(n,0);
    // Cuantas veces se trabajo y cuantas dias consecutitvos se trabajo
    // por cada turno
    for(unsigned int i= 0; i<v.size(); i++){
        // por cada enfermera
        for(unsigned int j = 0; j< v[0].size(); j++){
            // contar asignaciones
            totals[j]+= v[i][j];
            dailyAux[j]+= v[i][j];
            // si se llega al ultimo turno del dia
            if((i%s) == (unsigned)(s-1)){
                // si existe alguna asignacion en el dia
                if(dailyAux[j]>0){
                    // se aumenta el conteo de asignaciones por cada s turnos = dias
                    dailyCounter[j]++;
                    dailyAux[j] = 0;
                }
            } else{
                // comienza nuevo dia y se reinicia
                dailyAux[j] = 0;
            }

        }
    }

    int penalization1 = 0;

    for(unsigned int j = 0; j<v[0].size(); j++){
        if (minAssignments <= totals[j] && maxAssignments>= totals[j]){

        } else {
            penalization1+=3;
        

        }

    }
    int penalization2 = 0;
    for(unsigned int j = 0; j<v[0].size(); j++){
        if (minDaily <= totals[j] && maxDaily>= totals[j]){

        } else {
            penalization1+=3;
        }

    }






    // cuantas veces trabaja consecutiva el turno s
    vector<vector<int>> shiftConsecutive(s,vector<int>(n,0));
    // valor de ese turno en el dia anterior
    vector<vector<int>> shiftTemp(s,vector<int>(n,0));
    // cuantas veces trabaja el turno s
    vector<vector<int>> shiftCounter(s,vector<int>(n,0));


    // por cada turno
    for(unsigned int i = 0; i<v.size(); i++){
        // por cada enfermera
        for(unsigned int j = 0; j< v[i].size(); j++){
           
            // turnos del tipo 0
            if (i%s == 0){


                shiftCounter[0][j]+=v[i][j];

                shiftTemp[0][j]+=v[i][j];
                if(v[i][j] == 1){
                    if (shiftTemp[0][j]== 1){
                        shiftConsecutive[0][j]++;
                    }
                } else {
                    shiftConsecutive[0][j] = 0;
                    shiftTemp[0][j] = 0;
                }

                

            // turnos del tipo 1
            } else if (i%s == 1){
                shiftCounter[1][j]+=v[i][j];
                
                shiftTemp[1][j]+=v[i][j];
                if(v[i][j] == 1){
                    if (shiftTemp[1][j]== 1){
                        shiftConsecutive[1][j]++;
                    }
                } else {
                    shiftConsecutive[1][j] = 0;
                    shiftTemp[1][j] = 0;
                }



            // turnos del tipo 2
            } else if (i%s == 2){
                shiftCounter[2][j]+=v[i][j];

                shiftTemp[2][j]+=v[i][j];
                if(v[i][j] == 1){
                    if (shiftTemp[2][j]== 1){
                        shiftConsecutive[2][j]++;
                    }
                } else {
                    shiftConsecutive[2][j] = 0;
                    shiftTemp[2][j] = 0;
                }



            // turnos del tipo 3
            } else {
                shiftCounter[3][j]+=v[i][j];

                shiftTemp[3][j]+=v[i][j];
                if(v[i][j] == 1){
                    if (shiftTemp[3][j]== 1){
                        shiftConsecutive[3][j]++;
                    }
                } else {
                    shiftConsecutive[3][j] = 0;
                    shiftTemp[3][j] = 0;
                }

            }

        }
    }



    int penalization3=0;
    int penalization4=0;

   // por cada turno
    for(unsigned int i = 0; i<v.size(); i++){
        // por cada enfermera
        for(unsigned int j = 0; j< v[i].size(); j++){
            if (i%s == 0){

                if (shift0Min<=shiftCounter[0][j] && shiftCounter[0][j]<=shift0Max){

                } else {
                    penalization3+=3;

                }

                if (!(shift0MinCons<=shiftConsecutive[0][j] && shiftConsecutive[0][j]<=shift0MaxCons)){
                    penalization4+=3;

                }

            }

            if (i%s == 1){

                if (shift1Min<=shiftCounter[1][j] && shiftCounter[1][j]<=shift1Max){

                } else {
                 
                    penalization3+=3;   
                }

                if (!(shift1MinCons<=shiftConsecutive[1][j] && shiftConsecutive[1][j]<=shift1MaxCons)){
                    penalization4+=3;

                }
            }

            if (i%s == 2){

                if (shift2Min<=shiftCounter[2][j] && shiftCounter[2][j]<=shift2Max){

                } else {

                    penalization3+=3;
                    
                }

                if (!(shift2MinCons<=shiftConsecutive[2][j] && shiftConsecutive[2][j]<=shift2MaxCons)){
                    penalization4+=3;

                }

            }
            if (i%s == 3){

                if (shift3Min<=shiftCounter[3][j] && shiftCounter[3][j]<=shift3Max){

                } else {

                    penalization3+=3;
                    
                }

                if (!(shift3MinCons<=shiftConsecutive[3][j] && shiftConsecutive[3][j]<=shift3MaxCons)){
                    penalization4+=3;

                }

            }



        }
    }

    
    totalPenalizations = penalization1+penalization2+penalization3+penalization4;

    return totalPenalizations;

}

int checkObjetive(int totalPrefs, int totalPenalizations){
    return totalPenalizations+totalPrefs;
}



void printMatrix(Matrix &m, int rows, int columns){

    cout << "Imprimiendo Matriz de asignacion" << endl;
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
        //cout << "j: " << i%columns << " " << "i: " << j << endl;
        //cout << "i: " << i << " " << " i/rows-1:  " << i/(rows-1) << endl;
        m[j][i%columns] = v[i];
    }
}
