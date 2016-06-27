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
void undoFilters(vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura){

	for(unsigned int i = 0; i<dom.size(); i++){
		for(unsigned int j = 0; j<dom[i].size(); j++){
			for(unsigned int k = 0; k<estructura[i][j].size(); k++){
				dom[i][j].push_back(estructura[i][j].back());
				estructura[i][j].pop_back();
			}
		}
	}


}


bool minimalFC(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, vector<int> covertureVector, int shift, int nurse){

	//int remainShifts = 1-shift%2;
	int remainShifts = 3-shift%4;
	int value;

	// crear un dominio temporal para filtrar
	vector<vector<vector<int>>> test = dom;
	cout << "se crea dominio temporal" << endl;
    // temp = cuantos dias quedan por fitlrar en cada iteraicon
    // filrra assignaicon y turnos restatnes 
    for (int temp=1; temp< remainShifts+1; temp++){
    	cout  << "filtrando el turno" << temp+shift << endl; 
        value = (test[shift+temp][nurse]).back();
        cout << "sacando: " << value << "del dominio de la enfermera " << nurse << "para el turno " << shift+temp << endl;
        estructura[shift+temp][nurse].push_back(value);
        test[shift+temp][nurse].pop_back();
        cout << test[shift+temp][nurse].back() << endl;

    }

    //suggested 

    // si se cumple la covertura entonces el dominio se cambia
    // de lo contrario no, ya que no se debe asignar aun supuestamente
    if (coverture(v,covertureVector, test,shift,nurse)){
    	dom = test;
    	return true;
    } else {
    	return false;
    }

}

bool hasone(vector<vector<vector<int>>> &dom, int shift, int nurse){

	int count = 0;
	for (auto k: dom[shift][nurse]){
		count+=k;
	}
	if (count == 1){
		return true;
	} else {
		return false;
	}
}

// dudas si lo

// separar asignados en otro lado y que covertura sume desde poscion actual
// asta el final de la fila + los asignados
// retorna true si se cumple la cobertura en el turno actual y en los siguientes
bool coverture(vector<vector<int>> &v, vector<int> &covertureVector, vector<vector<vector<int>>> &dom, int shift, int nurse){

	// counter == enfermeras disponibles para assignar

	bool temp;

	int thisshift=0;
	int counter = 0;

	//los ya asignados tambien debe ser sumados ya que aportan a la cobertura
	for (int j = 0; j<nurse; j++){
		thisshift+=v[shift][j];
	}


	// misma fila de la matriz de asignacion caso especial en el que se cuenta desde el punto actual hasta el final de la fila
	for(unsigned int j = nurse; j<dom[shift].size(); j++){
		for(auto element: dom[shift][j]){
			counter+= element;
		}
	}

	cout << "Cobertura del turno actual: " << " Asignados: " << thisshift << " Contador del dominio: " << counter << " " << " covertura: " << covertureVector[shift] << " del turno " << shift << endl;


	if (covertureVector[shift]<=counter+thisshift){
		cout << "Se cumple la cobertura del turno actual: " << shift << endl;
		temp = true;
		counter=0;

		// chequear covertura en el resto de los turnos
		for(unsigned int i = (shift+1); i<covertureVector.size(); i++){
			for(unsigned j = 0; j < dom[i].size(); j++){
			//for(auto n: dom[i]){
				for(auto element: dom[i][j]){
					//cout << "elemen: " << element << endl;
					counter+= element;
				}
			}
			cout << "Contador del dominio: " << counter << " " << " covertura: " << covertureVector[i] << " del turno " << i << endl; 
			if (covertureVector[i]<=counter){
				cout << "Se cumple covertura para el turno: " << i << endl;
			} else {
				cout << "No se cumple cobertura para el turno: " << i << endl;
				return false;
			}
			counter = 0;
		}
	} else {
		return false;
	}

	// si se cumplen los casos entonces temp se queda como true
	cout << "Cobertura retornando TRUE" << endl;
	return temp;

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
                // si el valor es 1, entonces se debe hacer MFC para filtrar dom y pasar a estructura

            	vector<vector<list<int>>> estructuraRecursion(4,(vector<list<int>>(5)));
            	estructuraRecursion = estructura;




                if (true) {
                	cout << "k : " << k << endl;
                	if (hasone(dom,i,j) && k && minimalFC(v,dom, estructuraRecursion, covertureVector, i, j)){

                		cout << "se aplico MFC" << endl;
                		v[i][j] = k;
                		cout << "imprimir la matriz" << endl; 
                		printMatrix(v,28,25);

                		printDomain(dom);
                		printStruct(estructuraRecursion);







                		if (j!= jmax -1){
                			cout << "entrando a recursion con i; " << i << " j: " << j+1 << endl;
                		    recursiveS(v,dom,estructuraRecursion,covertureVector,i,j+1,imax,jmax);
                		} else {
                		    if (i != imax -1){
                		    	cout << "entrando a recursion con i; " << i+1 << " j: " << j-jmax+1 << endl;
                		        recursiveS(v,dom,estructuraRecursion,covertureVector,i+1,j-(jmax-1),imax,jmax);
                		    } else {
                		    	// se ha llegado al final de la matriz
                		    	cout << "imprimir la matriz" << endl; 
                		        printMatrix(v,28,25);
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

                	} else {
                		cout << "terminado el for para i: " << i << " y j: " << j << endl;
                		cout << "asignacion actual" << endl;      		

                		//undoFilters(dom,estructura);
                		v[i][j] = 0;
                		printMatrix(v,28,25);
                		if (j!= jmax -1){
                			cout << "entrando a recursion con i; " << i << " j: " << j+1 << endl;
                		    recursiveS(v,dom,estructuraRecursion,covertureVector,i,j+1,imax,jmax);
                		} else {
                		    if (i != imax -1){
                		    	cout << "entrando a recursion con i; " << i+1 << " j: " << j-jmax+1 << endl;
                		        recursiveS(v,dom,estructuraRecursion,covertureVector,i+1,j-(jmax-1),imax,jmax);
                		    } else {


                		    	v[i][j] = 0;
                		    	undoFilters(dom,estructura);

                		    	// se ha llegado al final de la matriz
                		    	cout << "imprimir la matriz" << endl; 
                		        printMatrix(v,28,25);
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


void printDomain(vector<vector<vector<int>>> &d){

	cout << "Imprimiendo dominio" << endl;
	for(unsigned int i = 0; i<d.size() ; i++){
		for(unsigned int j =0; j<d[i].size(); j++){
			cout << "[ ";
			for(auto element: d[i][j]){
				cout << element << " ";
			}
			cout << " ], ";
		}
		cout << endl;
	}
}

void printStruct(vector<vector<list<int>>> &estructura){

	cout << "Imprimiendo estructura/ complemento del dominio filtrado" << endl;
	for(unsigned int i = 0; i<estructura.size() ; i++){
		for(unsigned int j =0; j<estructura[i].size(); j++){
			cout << "[ ";
			for(auto element: estructura[i][j]){
				cout << element << " ";
			}
			cout << " ], ";
		}
		cout << endl;
	}
}