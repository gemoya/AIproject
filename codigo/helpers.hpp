#ifndef HELPERS_H
#define HELPERS_H
using namespace std;

void quickSort(vector<int> &a, vector<int> &b, int first, int last);
int pivot(vector<int> &a, vector<int> &b, int first, int last);
void swap(int& a, int& b);
void swapNoTemp(int& a, int& b);
void print(vector<int> a, const int& N);
 

#endif