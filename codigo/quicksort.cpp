#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

void quickSort(vector<int> &a, vector<int> &b, int first, int last);
int pivot(vector<int> &a, vector<int> &b, int first, int last);
void swap(int& a, int& b);
void swapNoTemp(int& a, int& b);
void print(vector<int> a, const int& N);
 
using namespace std;
 
int main()
{
    vector<int> test = { 7, -13, 1, 3, 10, 5, 2, 4 };
    vector<int> test2 = {1, 2, 3, 4, 5, 6, 7, 8};
    int N = sizeof(test)/sizeof(int);
    cout << N << endl;
 
    cout << "Size of test array :"  << N << endl;
 
    cout << "Before sorting : " << endl;
    print(test, N);
    cout << "Before sorting : " << endl;
    print(test2, N);
    //quickSort(test, 0, N-1);
    quickSort(test, test2, 0, N-1);


    cout << endl << endl << "After sorting : " << endl;
    print(test, N);
    cout << endl << endl << "After sorting : " << endl;
    print(test2, N);
    return 0;
}
 
/**
 * Quicksort.
 * @param a - The array to be sorted.
 * @param first - The start of the sequence to be sorted.
 * @param last - The end of the sequence to be sorted.
*/
void quickSort( vector<int> &a, vector<int> &b, int first, int last ) 
{
    int pivotElement;
 
    if(first < last)
    {
        pivotElement = pivot(a, b, first, last);
        //quickSort(a, first, pivotElement-1);
        //quickSort(a, pivotElement+1, last);
        quickSort(a, b, first, pivotElement-1);
        quickSort(a, b, pivotElement+1, last);
    }
}
 
/**
 * Find and return the index of pivot element.
 * @param a - The array.
 * @param first - The start of the sequence.
 * @param last - The end of the sequence.
 * @return - the pivot element
*/
int pivot(vector<int> &a, vector<int> &b, int first, int last) 
{
    int  p = first;
    int pivotElement = a[first];
 
    for(int i = first+1 ; i <= last ; i++)
    {
        /* If you want to sort the list in the other order, change "<=" to ">" */
        if(a[i] <= pivotElement)
        {
            p++;
            swap(a[i], a[p]);
            swap(b[i], b[p]);
        }
    }
 
    swap(a[p], a[first]);
    swap(b[p], b[first]);
 
    return p;
}
 
 
/**
 * Swap the parameters.
 * @param a - The first parameter.
 * @param b - The second parameter.
*/
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
 
/**
 * Swap the parameters without a temp variable.
 * Warning! Prone to overflow/underflow.
 * @param a - The first parameter.
 * @param b - The second parameter.
*/
void swapNoTemp(int& a, int& b)
{
    a -= b;
    b += a;// b gets the original value of a
    a = (b - a);// a gets the original value of b
}
 
/**
 * Print an array.
 * @param a - The array.
 * @param N - The size of the array.
*/
void print(vector<int> a, const int& N)
{
    for(int i = 0 ; i < N ; i++){
        cout << "array[" << i << "] = " << a[i] << " ";
    }
    cout << endl;

} 