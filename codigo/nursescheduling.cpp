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

    /*cout << v.size() << endl;


    for(i = 0; i <v.size(); i++){
        cout << v[i] << endl;
    }*/


}


// void recursiveSearch(vector<list<int>> &v, int i, int j, int max, int domainSize){

//     bool constraints = true;
//     if (j< domainSize){
//     cout << "test "<< i << " " << j << endl;

//         if (i < max){

//             for(int k = 0; k< 2; k++){

//                 if (constraints == true){

//                     v[i].push_back(k);

//                     if (j != (domainSize -1)){

//                         recursiveSearch(v,i+1,j,max,domainSize);

//                     } else {
//                     }

//                 }

//             }


//         }

//     } else {
        
//         if (i < max){

//             if (i != (max -1)){
//             recursiveSearch(v,i+1,0,max,domainSize);
//             } else {
//                 cout << "Printing" << endl;
//                 cout << "[" << " ";
//                 for (auto alist: v){
//                     for (auto element: alist){
//                         cout << element << " ";
//                     }
//                 }
                
//                 cout << "]" <<  endl;
//             }
//         }
//     }
// }

// /* TO DO!!!!!!!!!!!!!!!
// // sum of objetive and penalize
// void checkObjetive(){

// }

// // check preferences of a complete assignment
// void checkPreferences(){

// }
// */

// void initializeDomains(vector<list<int>> &d, int vectorSize, int listSize){

//     //for (std::list<int>::const_iterator iterator = intList.begin(), end = intList.end(); iterator != end; ++iterator) {
//     //    std::cout << *iterator;
//     //}


//     for(int i = 0; i<vectorSize; i++){
//         for(int j = 1; j<(listSize+1); j++){
//             d[i].push_back(j);
//         }
//     }

// }

// void saveDomain(vector<vector<vector<vector<int>>>> &t, vector<vector<vector<int>>> &d){

//     t.push_back(d);

// }

// bool checkDomain(vector<vector<vector<int>>> &d, int nurse, int shift){

//     //cout << " Check Domain: " << index << endl;
//     //int i = index%n;
//     //int j = index/n;
//     //cout << i << "," << j << endl;

//     // if domain of the turn is positive
//     //if (d[i][j] == 1){
//     //    return true;
//     //} else {
//     //    return false;
//     //}


//     if (d[nurse][shift][0]){

//         return true;

//     } else {

//         return false;

//     }

// }
// // check if coverture is ready, sum of columns vector of domains
// bool checkCoverture(vector<int> &v, int index){

//     return true;
// }

// // only one turn per day avaible
// // REVISAR NURSE SHIFT YA QUE CAMBIO LA REPRESENTACION!!!
// // d[nurse][shift][0] = > 1
// // d[nurse][shift][1] = > 0
// void mfc(vector<vector<vector<int>>> &d, vector<vector<vector<vector<int>>>> &t,  int nurse, int shift){

//     int count = 3-shift%4; //how many variable to check
//     //cout << "mfc: "<< i << " " << j << " " << count << endl; 
//     // if no more variables to check or is already checked!

//    /* for (int temp = 0; temp<count; temp++){
//         shift++;
//         d[nurse][shift] = 0;

//     }*/

//     /*j = index/n;
//     while(count > 0|| d[i][j+1] == 0){
//         //cout << "while: ";
//         //cout << "i: " << i << "j: " << j << endl;
//         cout << count << " ";
//         j++;
//         d[i][j] = 0;
//         count--;
//     }*/

//    // cout << "termina while con index: " << index << endl;

//     // Last try:
//     // filter only one shift per
//     //


//     for (int temp = 0; temp < count; temp++ ){
//         shift++;
//         d[nurse][shift][0] = 0;
//     }

//     saveDomain(t,d);






// }


// void recursiveSearch(vector<int> &v, vector<vector<int>> &d, Matrix &m, int i, int max){
//     //bool constraints = true;
//     cout << i << endl;
//     if (i < max){
//         for (unsigned int j = 2; j-- > 0; ){

//             bool test = checkDomain(d,i,25);
               
//             if (test){
//             //if (constraints == true){
//                 //cout << "test: " << i << endl;
//                 v[i] = j;
//                 // mfc
//                 //mfc(d, i);


//                 if (i != max -1){
                    
//                     recursiveSearch(v,d,m,i+1,max);
//                 } else {
//                     /*
//                     cout << "vector: [";
//                     for(int k = 0; k<v.size(); k++){
//                        cout <<  v[k] << "," ;
//                     }
//                     cout << "]" << endl;
                    
//                     cout << "entrando a _1dTo2d" << endl;*/
//                     _1dTo2d(v,m,28,25);
//                     cout << "entrando a _printMatrix" << endl;
//                     printMatrix(m,28, 25);
                    
//                 }

//             } else {
//                 cout << "pegado" << endl;
//                 /*// assign 0 and pass to next
//                 // added
//                 v[i] = 0;
//                 if (i != max -1){
//                     recursiveSearch(v,d,m,i+1,max);
//                 } else {
//                     //cout << "vector: [";
//                     //for(int k = 0; k<v.size(); k++){
//                     //    cout <<  v[k] << "," ;
//                     //}
//                     //cout << "]" << endl;
//                     vector<vector<int>> dv(25,vector<int>(7*4,1));
//                     d = dv;
//                     _1dTo2d(v,m,7*4,25);
//                     printMatrix(m,7*4, 25);
//                 }*/
//             }
//         }
//     }
// }


void checkout(){

}




void recursiveSearch2(vector<vector<int>> &v, vector<vector<vector<int>>> &d, vector<vector<vector<vector<int>>>> &t,  int i, int j, int imax, int jmax){

    if (i< imax){

        if (j < jmax){
    
            for (unsigned int k = 2; k-- > 0; ){
    
                if(true){

                        
                    // si el 1 esta disponible en el dominio
                    v[i][j] = k;
                    // falta si no esta disponible el 1

                    //mfc(d,t,j,i);

                    if (j!= jmax -1){
                        
                        recursiveSearch2(v,d,t,i,j+1,imax,jmax);

                    } else {

                        if (i != imax -1){
                            recursiveSearch2(v,d,t,i+1,j-(jmax-1),imax,jmax);
                        } else {



                            printMatrix(v,28,25);

                            /*cout << "Matrix" << endl;
                            for (int row = 0; row < 28; row++){
                                for (int col = 0; col < 25; col++){

                                    cout << v[row][col] << " ";
                                }
                            }
                            cout << endl;*/

                        }



                    }
    
                // restaurar 
    
                } else {
    
                }
            }
        }  
    } }

// void joinDomains(vector<list<int>> &v, list<int> filtered){

// }



//filro para que enfermeras trabajan una vez al dia, es decir
// si trabaja el turno de mañana entonces si cambian a 0
void filterSameDay(vector<vector<int>> &d, int nurse, int shift){

    int remainShifts = 3-shift%4;

    // temp = cuantos dias quedan por fitlrar en cada iteraicon
    // filrra assignaicon y turnos restatnes 
    for (int temp=1; temp< remainShifts+1; temp++){

        d[shift+temp][nurse] = 0;

    }

}


//Chequeo de cobertura, si la suma de las enfermeras disponibles para algun turno no se cumple, entonces
// retorna false, utilizando SumNurses para sumar y ver disponibles
bool checkOut(vector<int> coverture, vector<vector<int>> domainTime, vector<list<int>> v, int actual){



    for (int i = 0; i<coverture.size(); i++){

        int size= sumNurses(domainTime[i]);
        cout << "Covertura: " << coverture[i] << " Size: " << size << " v: " << v[i].size() << endl;
        // las que quedan del dominio, la que quiero asignar + las asginadas 
        //int sum = size+v[i].size();
        int sum = size;
        //if (actual == i) sum++;

        if ( coverture[i]<=sum){
        } else {
            return false;
        }
    }
    return true;
}

// SUma de enfermeras disponibles en la matriz,
// es decir las la suma de los 1s en las filas de D*sxN
int sumNurses(vector<int> row){

    int nursesCount=0;
    for(int value: row){
        if (value != -1){
            nursesCount+=value;
        }
    }
    return nursesCount;
}


void recursiveSearch4(vector<list<int>> &v, vector<vector<vector<int>>> &d, vector<int> &coverture, int i, int imax){

    vector<vector<int>> domainTime = d.back();
    if (i < imax){
        int flag = 1;

        // recorriendo el dominio de enfermeras para el turno i
        for(int j = 0; j<domainTime[i].size(); j++){
    
            // si la enfermera esta disponible

            for (unsigned int k = 2; k-- > 0; ){

                bool finder = (((v[i].end()) == find(v[i].begin(), v[i].end(), j+1 )));
                if (domainTime[i][j] && finder && k){
                    cout << "Entrando al if con turno: " << i << "y enfermera: " << j+1 << endl;
                    // filtro
                    filterSameDay(domainTime,j,i);
                    //check out, recibe el turno, dia, y el tamaño del vector de asignacion para el turno i
                    if (checkOut(coverture, domainTime, v, i)) {
                        // agregar a los dominios en el tiempo el dominio filtrado en este tiempo
                        d.push_back(domainTime);
                        // asignar enfermera 
                        v[i].push_back(j+1);
                        cout<< "cobertura satisfecha" << endl;
                        cout << "imprimriendo asignacion :"<< endl;
                        for (auto val: v){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }
                        cout << endl;
                        cout << "imprimriendo filtro :"<< endl;
                        for (auto val: domainTime){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }
                        cout << endl;
                    } else {
                        cout << "covertura no satisfecha" << endl;
                        cout << "imprimriendo asignacion :"<< endl;
                        for (auto val: v){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }
                        cout << endl;
                        cout << "imprimriendo filtro :"<< endl;
                        for (auto val: domainTime){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }
                        cout << endl;
                        flag =1;
                        // vector<vector<int>> domainTemp = d.back();
                         d.pop_back();
                        // domainTemp[i][j]=0;
                        // d.push_back(domainTemp);
                        if (v[i].size() == 0){
                            cout << "ME DEVOLVI DE TURNO" << endl;
                            v[i-1].pop_back();
                            recursiveSearch4(v,d,coverture,i-1,imax);
                        } else{
                            cout << "ME DEVOLVI DE ASIGNACION" << endl;
                            v[i].pop_back();
                            recursiveSearch4(v,d,coverture,i,imax);
                        }
                    }
                } else {


                    if(checkOut(coverture, domainTime, v, i)){

                        domainTime[i][j] = 0;
                        d.push_back(domainTime);

                        recursiveSearch4(v,d,coverture,i+1,imax);



                    } else { 

                        cout << "covertura no satisfecha" << endl;
                        cout << "imprimriendo asignacion :"<< endl;
                        for (auto val: v){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }
                        cout << endl;
                        cout << "imprimriendo filtro :"<< endl;
                        for (auto val: domainTime){
                            cout << "<";
                            for (auto l: val){
                                cout << l << " ";
                            }
                            cout << ">"<< endl;
                        }


                    }


                } 

            } 

        } 
        if (flag == 1) recursiveSearch4(v,d,coverture,i+1,imax);
    }
}









// 
void recursiveSearch3(vector<list<int>> &v, vector<vector<vector<int>>> &d, vector<int> &coverture, int i, int imax){

    vector<vector<int>> domainTime = d.back();
    if (i < imax){
        int flag = 1;

        // recorriendo el dominio de enfermeras para el turno i
        for(int j = 0; j<domainTime[i].size(); j++){
    
            // si la enfermera esta disponible
            if (domainTime[i][j] == 1){

            }

            bool finder = (((v[i].end()) == find(v[i].begin(), v[i].end(), j+1 )));
            if (domainTime[i][j] && finder){
                cout << "Entrando al if con turno: " << i << "y enfermera: " << j+1 << endl;
    
                // filtro
                filterSameDay(domainTime,j,i);

                //check out, recibe el turno, dia, y el tamaño del vector de asignacion para el turno i
                if (checkOut(coverture, domainTime, v, i)) {



                    // agregar a los dominios en el tiempo el dominio filtrado en este tiempo
                    d.push_back(domainTime);
                    // asignar enfermera 
                    v[i].push_back(j+1);
                    cout<< "cobertura satisfecha" << endl;

                    cout << "imprimriendo asignacion :"<< endl;
                    for (auto val: v){
                        cout << "<";
                        for (auto l: val){
                            cout << l << " ";
                        }

                        cout << ">"<< endl;

                    }

                    cout << endl;


                    cout << "imprimriendo filtro :"<< endl;
                    for (auto val: domainTime){
                        cout << "<";
                        for (auto l: val){
                            cout << l << " ";
                        }

                        cout << ">"<< endl;

                    }

                    cout << endl;


                } else {

                    cout << "covertura no satisfecha" << endl;

                    cout << "imprimriendo asignacion :"<< endl;
                    for (auto val: v){
                        cout << "<";
                        for (auto l: val){
                            cout << l << " ";
                        }

                        cout << ">"<< endl;

                    }

                    cout << endl;


                    cout << "imprimriendo filtro :"<< endl;
                    for (auto val: domainTime){
                        cout << "<";
                        for (auto l: val){
                            cout << l << " ";
                        }

                        cout << ">"<< endl;

                    }

                    cout << endl;

                    flag =1;


                    // vector<vector<int>> domainTemp = d.back();
                     d.pop_back();
                    // domainTemp[i][j]=0;
                    // d.push_back(domainTemp);


                    if (v[i].size() == 0){
                        cout << "ME DEVOLVI DE TURNO" << endl;
                        v[i-1].pop_back();
                        recursiveSearch3(v,d,coverture,i-1,imax);
                    } else{

                        cout << "ME DEVOLVI DE ASIGNACION" << endl;
                        v[i].pop_back();
                        recursiveSearch3(v,d,coverture,i,imax);

                    }



                }
            }

        } 

        if (flag == 1) recursiveSearch3(v,d,coverture,i+1,imax);

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
        //cout << "j: " << i%columns << " " << "i: " << j << endl;
        //cout << "i: " << i << " " << " i/rows-1:  " << i/(rows-1) << endl;
        m[j][i%columns] = v[i];
    }
}
