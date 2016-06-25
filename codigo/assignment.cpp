#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "nursescheduling.hpp"
#include "helpers.hpp"
#include "assignment.hpp"


using namespace std;
using Matrix = vector < vector<int> >;

/*
Ejemplo dom
[
[[1,0],[1,0],[1,0]],
[[1,0],[1,0],[1,0]],
[[1,0],[1,0],[1,0]],
[[1,0],[1,0],[1,0]]
]


*/

// v, matriz de D*SxN de asignaciones i: shifts, j: nurses
// dom dominios
// estructura similar a dominios pero su ultimo nivel es una lista dado que comienza vacio
// i, referencia de iterar avanzar recursivamente sobre filas
// j, referencia de iterar/ avanzar recursivamente sobre columnas
// cuando se encuentra la ultima columna de la fila actual, entonces se llama a la recursion en la fila siguiente en su primera columna


//no terminado
void undoFilters(vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, int shift, int nurse){


}


bool minimalFC(vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, vector<int> covertureVector, int shift, int nurse){

	int remainShifts = 3-shift%4;
	int value;

	// crear un dominio temporal para filtrar
	vector<vector<vector<int>>> test = dom;
    // temp = cuantos dias quedan por fitlrar en cada iteraicon
    // filrra assignaicon y turnos restatnes 
    for (int temp=1; temp< remainShifts+1; temp++){

        value = test[shift+temp][nurse].back();
        estructura[shift+temp][nurse].push_back(value);
        test[shift+temp][nurse].pop_back();

    }
    //suggested 

    // si se cumple la covertura entonces el dominio se cambia
    // de lo contrario no, ya que no se debe asignar aun supuestamente
    if (coverture(covertureVector, dom)){
    	dom = test;
    	return true;
    } else {
    	return false;
    }

}

// dudas si lo
bool coverture(vector<int> &covertureVector, vector<vector<vector<int>>> &dom){

		// counter == enfermeras disponibles para assignar

		int counter=0;
		for(unsigned int i = 0; i<covertureVector.size(); i++){
			for(auto n: dom[i]){
				for(auto element: n){
					//cout << "elemen: " << element << endl;
					counter+= element;
				}

			
			}
			cout << "COunter: " << counter << " " << " covertura: " << covertureVector[i] << " del turno " << i << endl; 
			if (covertureVector[i]<=counter){
				return true;
			}
			counter = 0;


		}
		return false;

}


void recursiveS(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> estructura, vector<int> &covertureVector, int i, int j, int imax, int jmax){

	// value to assign

	int k;
    if (i< imax){
        if (j < jmax){
            //for (unsigned int k = 2; k-- > 0; ){
        	// dom[i][j] = = [0,1]
        	vector<int> actualDom = dom[i][j];
            for (auto domij: actualDom){
            	cout << "i: " << i << "j: " << j <<endl;
            	cout << "En el primer for, domij= " << domij << endl;

            	// primero es 1, luego es 0
            	k = 1- domij;
                // por mientras
            	// si se cumple covertura (coverture == true), se sigue, delo contrario se debe acabar la recursion actual
            	// quizas covertura debe ir antes del for..
                //if(coverture(covertureVector, dom)){

                //v[i][j] = k;
                //dom[i][j].pop_back();
                // si el valor es 1, entonces se debe hacer MFC para filtrar dom y pasar a estuctura
                if (true) {
                	cout << "k : " << k << endl;
                	if (minimalFC(dom, estructura, covertureVector, i, j) && k ){

                		cout << "se aplico MFC" << endl;
                		v[i][j] = k;

                		if (j!= jmax -1){
                		    recursiveS(v,dom,estructura,covertureVector,i,j+1,imax,jmax);
                		} else {
                		    if (i != imax -1){
                		        recursiveS(v,dom,estructura,covertureVector,i+1,j-(jmax-1),imax,jmax);
                		    } else {
                		    	// se ha llegado al final de la matriz
                		    	cout << "imprimir la matriz" << endl; 
                		        printMatrix(v,4,5);
                		        cout << "imprimir dominios" << endl;
                		        /*cout << "Matrix" << endl;
                		        for (int row = 0; row < 28; row++){
                		            for (int col = 0; col < 25; col++){
                		                cout << v[row][col] << " ";
                		            }
                		        }
                		        cout << endl;*/
                		    }
                		}

                	}
                } else {
                	cout << " terminaod el for para i: " << i << " y j: " << j << endl;
                	cout << "asignacion actual" << endl; 
                	printMatrix(v,4,5);
                }
                // sin else, se continua normal 
                // if (j!= jmax -1){
                //     recursiveS(v,dom,estructura,covertureVector,i,j+1,imax,jmax);
                // } else {
                //     if (i != imax -1){
                //         recursiveS(v,dom,estructura,covertureVector,i+1,j-(jmax-1),imax,jmax);
                //     } else {
                //     	// se ha llegado al final de la matriz
                //     	cout << "imprimir la matriz" << endl; 
                //         printMatrix(v,4,5);
                //         cout << "imprimir dominios" << endl;
                //         /*cout << "Matrix" << endl;
                //         for (int row = 0; row < 28; row++){
                //             for (int col = 0; col < 25; col++){
                //                 cout << v[row][col] << " ";
                //             }
                //         }
                //         cout << endl;*/
                //     }
                // }
                // restaurar 
                //} else {
 				//   
                //}
            }
        }  
    } 
}
