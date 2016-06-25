#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int main (int argc, char **argv) {

    int N, S, D;
    string line;
    string partial;

    vector<string> constants;
    vector<string> tokens;

    ifstream inputfile (argv[1]);

    if (inputfile.is_open())
    {

        getline(inputfile,line);

        istringstream iss(line);
        string token;
        while(getline(iss, token, '\t'))
            constants.push_back(token);
            // cout << token << endl;

        N = stoi(constants[0]);
        D = stoi(constants[1]);
        S = stoi(constants[2]);

        cout << "enfermeras: " << N << endl;
        cout << "dias: " << D << endl;
        cout << "turnos por dia: " << S << endl;


        while (getline (inputfile,line))
        {

           // istringstream iss(line);
           // string token;
           // while(getline(iss, token, '\t'))
           //     tokens.push_back(token);
  
        }
        inputfile.close();
    }

    else cout << "No se pudo abrir el archivo" << endl; 

    return 0;
}