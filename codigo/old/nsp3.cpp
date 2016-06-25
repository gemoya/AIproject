#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int main (int argc, char **argv) {

    int N, S, D;
  	int temp;
    vector<int> nds;

    ifstream inputfile;
    inputfile.open(argv[1]);
    string line;

    getline(inputfile, line);
  	istringstream buffer(line);  

    buffer >> N >> D >> S;
    cout << N << D << S << endl;


	while (getline(inputfile, line)){

		if (!(line=="")){

    		istringstream ss(line);

    		for(int i = 0; i<S; i++){
    			ss >> temp;
    			cout << temp << endl;
    		}
    	}
	}
    return 0;
}