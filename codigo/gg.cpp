void filterSameDay(vector<vector<int>> &d, int nurse, int shift){

    int remainShifts = 3-shift%4;

    // temp = cuantos dias quedan por fitlrar en cada iteraicon
    // filrra assignaicon y turnos restatnes 
    for (int temp=1; temp< remainShifts+1; temp++){

        d[shift+temp][nurse] = 0;

    }

}

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

int sumNurses(vector<int> row){

    int nursesCount=0;
    for(int value: row){
        if (value != -1){
            nursesCount+=value;
        }
    }
    return nursesCount;
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
                for 
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