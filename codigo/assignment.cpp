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

bool checkCoverture(vector<vector<int>> &v, vector<int> &covertureVector){

	bool check = true;
	int counter= 0;
	for(unsigned int i = 0; i<v.size(); i++){
		//cout << i << " ";
		for(unsigned int j = 0; j< v[0].size(); j++){
			counter+=v[i][j];
		}

		//cout << "Comprobacion final " << "turno: " << i << "Cobertura: " << covertureVector[i] << "Asignados: " << counter << endl;

		if (counter < covertureVector[i]){
			return false;
		}
		counter = 0;
	}

	if (check){
		return true;
		//cout << "SE CUMPLE COBERTURA" << endl;

	} else {
		return false;
	}

}



bool minimalFC(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, vector<int> covertureVector, int shift, int nurse){

	//int remainShifts = 1-shift%2;
	int remainShifts = 3-shift%4;
	int value;

	// crear un dominio temporal para filtrar
	vector<vector<vector<int>>> test = dom;
	//cout << "se crea dominio temporal" << endl;
    // temp = cuantos dias quedan por fitlrar en cada iteraicon
    // filrra assignaicon y turnos restatnes 
    for (int temp=1; temp< remainShifts+1; temp++){
    	//cout  << "filtrando el turno" << temp+shift << endl; 
        value = (test[shift+temp][nurse]).back();
        //cout << "sacando: " << value << "del dominio de la enfermera " << nurse << "para el turno " << shift+temp << endl;
        estructura[shift+temp][nurse].push_back(value);
        test[shift+temp][nurse].pop_back();
        
        //cout << test[shift+temp][nurse].back() << endl;

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

	int remainShifts = 3-shift%4;
	int remainCoverture = 0;

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

	//cout << "Cobertura del turno actual: " << " Asignados: " << thisshift << " Contador del dominio: " << counter << " " << " covertura: " << covertureVector[shift] << " del turno " << shift << endl;

	if (covertureVector[shift]<=counter+thisshift){
		//cout << "Se cumple la cobertura del turno actual: " << shift << endl;
		temp = true;
		
		//counter=0;



		// chequear covertura de los turnos del dia
		for(int i = (shift+1); i<shift+remainShifts+1; i++){

			remainCoverture+=covertureVector[i];
		}

		//cout << "Cobertura acumulada: " << remainCoverture << " " << "disponibles: " << counter << endl;

		if (remainCoverture<counter){
			//cout << "Cobertura retornando TRUE" << endl;
			return temp;

		} else {
			return false;
		}
	} else {
		return false;
	}


 	//cout << "Cobertura retornando TRUE" << endl;
	//return temp;
}


			


void recursiveS(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> estructura, vector<int> &covertureVector, s *inputs, int i, int j, int imax, int jmax, clock_t start){

	
	int k;
    if (i< imax){
        if (j < jmax){

        	vector<int> actualDom = dom[i][j];
            for (auto domij: actualDom){
  
        
            	k = 1- domij;
             
            	vector<vector<list<int>>> estructuraRecursion(4,(vector<list<int>>(5)));
            	estructuraRecursion = estructura;


            	//solo por orden
                if (true) {
             
                	if (hasone(dom,i,j) && k && minimalFC(v,dom, estructuraRecursion, covertureVector, i, j)){

                		v[i][j] = k;
          
                		if (j!= jmax -1){
                			
                		    recursiveS(v,dom,estructuraRecursion,covertureVector, &(*inputs), i,j+1,imax,jmax, start);
                		} else {
                		    if (i != imax -1){
                		        recursiveS(v,dom,estructuraRecursion,covertureVector,&(*inputs), i+1,j-(jmax-1),imax,jmax, start);
                		    } else {
                		    	// se ha llegado al final de la matriz



                		        if (checkCoverture(v,covertureVector)){
                		        	int n = (*inputs).vars[0];
                		        	int d = (*inputs).vars[1];
                		        	int s = (*inputs).vars[2];

                		        	int preferences = checkPreferences(v, &((*inputs).preferencesMatrixT));
                					cout << "Mejor solucion tempral, imprimiendo matriz de asignacion" << endl;
                		        	printMatrix(v,d*s,n);
                		        	cout << "Total Preferencias: " << preferences << endl;
                		        	int penalize = checkPenalizations(v, &((*inputs).preferencesMatrixT), &((*inputs).vars), &((*inputs).consNurseAssigments), &((*inputs).consNurseTurns), &((*inputs).consMatrix));
              						cout << "Total Penalizaciones: " << penalize << endl;
              						cout << "Calidad: " << checkObjetive(preferences, penalize) << " ";
              						cout << "En un tiempo de: " << (double)(clock() - start)/CLOCKS_PER_SEC << " segundos." << endl;


                		        }


                		    }
                		}

                	} else {
                		
                		v[i][j] = 0;
             
                		if (j!= jmax -1){
                		    recursiveS(v,dom,estructuraRecursion,covertureVector,&(*inputs),i,j+1,imax,jmax, start);
                		} else {
                		    if (i != imax -1){
                		        recursiveS(v,dom,estructuraRecursion,covertureVector,&(*inputs), i+1,j-(jmax-1),imax,jmax, start);
                		    } else {


                		    	v[i][j] = 0;
                		    	undoFilters(dom,estructura);

                		        if (checkCoverture(v,covertureVector)){
                		        	int n = (*inputs).vars[0];
                		        	int d = (*inputs).vars[1];
                		        	int s = (*inputs).vars[2];

                		        	int preferences = checkPreferences(v, &((*inputs).preferencesMatrixT));
                					cout << "Mejor solucion tempral, imprimiendo matriz de asignacion" << endl;
                		        	printMatrix(v,d*s,n);
                		        	cout << "Total Preferencias: " << preferences << endl;
                		        	int penalize = checkPenalizations(v, &((*inputs).preferencesMatrixT), &((*inputs).vars), &((*inputs).consNurseAssigments), &((*inputs).consNurseTurns), &((*inputs).consMatrix));
              						cout << "Total Penalizaciones: " << penalize << endl;
              						cout << "Calidad: " << checkObjetive(preferences, penalize) << " ";
              						cout << "En un tiempo de: " << (double)(clock() - start)/CLOCKS_PER_SEC << " segundos." << endl;


              					}
                			}		
                		}
                	} 
            	}
        	}  
    	} 
	}
}


void printDomain(vector<vector<vector<int>>> &d){

	//cout << "Imprimiendo dominio" << endl;
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

	//cout << "Imprimiendo estructura/ complemento del dominio filtrado" << endl;
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