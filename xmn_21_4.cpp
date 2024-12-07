#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void sortTwoArrays(int a[], const int b[], const int aLen, const int bLen);


/**
 * Main program
 */
int main() {
    // Set up random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Define the size of the arrays
    const int size1 = 15 + rand() % 6;  // Random size between 15 and 20
    const int size2 = 5 + rand() % 6;   // Random size between 5 and 10

    int array1[size1];
    int array2[size2];

    // Fill array2 with random integers (both positive and negative)
    for (int i = 0; i < size2; i++) {
        array2[i] = (rand() % 21 - 10); // Random number between -10 and 10
    }
    // Fill array1 with random integers and ensure it contains as many zeros as array2's size
    int zerosToAdd = size2; // Number of zeros to add to array1
    for (int i = 0; i < size1; i++) {
        if (zerosToAdd > 0 && rand() % 2 == 0) {
            array1[i] = 0;
            zerosToAdd--;
        } else array1[i] = (rand() % 21 - 10); // Random number between -10 and 10
    }
    for (int i = size1 - zerosToAdd; i < size1; i++) array1[i] = 0; 


    cout << "Array 1: ";
    for (int i = 0; i < size1; i++) cout << array1[i] << ' ';
    cout << "\nArray 2: ";
    for (int i = 0; i < size2; i++) cout << array2[i] << ' ';
    cout << endl;


    sortTwoArrays(array1, array2, size1, size2); 

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
    for(i = 2; i < aLen; i++) {
        value = a[i];
        j = i;
        while (a[j-1] > value) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = value;
    }
    cout << "Sorted array: ";
    for(i = 0; i < aLen; i++) cout << a[i] << ' ';
}
