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

    srand(static_cast<unsigned int>(time(0)));                          // Set up random number generator

    const int SIZE1 = 15 + rand() % 6;                                  // Random size between 15 and 20
    const int SIZE2 = 5 + rand() % 6;                                   // Random size between 5 and 10

    int array1[SIZE1];
    int array2[SIZE2];

    for (int i = 0; i < SIZE2; i++) array2[i] = (rand() % 21 - 10);     // Fill array2 with integers between -10 and 10

    int zerosToAdd = SIZE2;                                             // Number of zeros to add to array1
    for (int i = 0; i < SIZE1; i++) {
        if (zerosToAdd > 0 && rand() % 2 == 0) {                        // Either add a 0 to array1
            array1[i] = 0;
            zerosToAdd--;
        } else array1[i] = (rand() % 21 - 10);                          // Or add random number between -10 and 10
    }
    for (int i = SIZE1 - zerosToAdd; i < SIZE1; i++) array1[i] = 0;     // Fills the end of array1 with 0 if needed


    cout << "Array 1: ";
    for (int i = 0; i < SIZE1; i++) cout << array1[i] << ' ';
    cout << "\nArray 2: ";
    for (int i = 0; i < SIZE2; i++) cout << array2[i] << ' ';
    cout << endl;


    sortTwoArrays(array1, array2, SIZE1, SIZE2);                        // Combines and sorts array1 and 2 into the former array

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
