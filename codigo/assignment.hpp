#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
using namespace std;
using Matrix = vector < vector<int> >;

void undoFilters(vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura);

bool minimalFC(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> &estructura, vector<int> covertureVector, int shift, int nurse);
bool hasone(vector<vector<vector<int>>> &dom, int shift, int nurse);

bool coverture(vector<vector<int>> &v,vector<int> &covertureVector, vector<vector<vector<int>>> &dom, int shift, int nurse);
void recursiveS(vector<vector<int>> &v, vector<vector<vector<int>>> &dom, vector<vector<list<int>>> estructura, vector<int> &covertureVector, int i, int j, int imax, int jmax);

void checkCoverture(vector<vector<int>> &v, vector<int> &covertureVector);


void printDomain(vector<vector<vector<int>>> &d);
void printStruct(vector<vector<list<int>>> &estructura);

#endif