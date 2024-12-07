#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ARRAY1LENGTH = 15;
const int ARRAY2LENGTH = 6;

void sortTwoArrays(int a[], const int b[], const int aLen, const int bLen);


/**
 * Main program
 */
int main() {
    int array1[ARRAY1LENGTH] = {3, 0, 7, -7, 6, 0, 4, 0, -6, 0, 0, -12, 35, 9, 0};
    int array2[ARRAY2LENGTH] = {17, -3, 4, 66, 8, -9};


    cout << "Array 1: ";
    for (int i = 0; i < ARRAY1LENGTH; i++) cout << array1[i] << ' ';
    cout << "\nArray 2: ";
    for (int i = 0; i < ARRAY2LENGTH; i++) cout << array2[i] << ' ';
    cout << endl;


    sortTwoArrays(array1, array2, ARRAY1LENGTH, ARRAY2LENGTH); 

    return 0;
}


/**
 * @brief Sort two unsorted arrays by combining them and sorting them numerically. 
 * @param a first and biggest array, that b gets combined into.
 * @param b second array, that gets combined into a.
 * @param aLen the amount of ints in array a, aka the length of array a
 * @param bLen the amount of ints in array b, aka the length of array b
 */
void sortTwoArrays(int a[], const int b[], const int aLen, const int bLen) {
    int i = 0;  int j = 0;  int value = 0;
    for(i; i < aLen; i++) {
        if(a[i] == 0) {
            a[i] = b[j];
            j++;
        }
    }
    for(i = 1; i < aLen; i++) {
        value = a[i];
        j = i;
        while (a[j-1] > value && j > 0) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = value;
    }
    cout << "Sorted array: ";
    for(i = 0; i < aLen; i++) cout << a[i] << ' ';
}
