#include <iostream>     // cout
#include <stdlib.h>     // rand
#include "LesData2.h"   // lesint

using namespace std;

void sortTwoArrays(int a[], const int b[], const int aLen, const int bLen);


/**
 * Main program
 */
int main() {
    int length2 = lesInt("Amount of ints in array 2: ", 5, 10);
    int length1 = lesInt("Amount of ints in array 1", length2 + 5, 20);
    int array1[length1];
    int array2[length2] = {0};

    for(int i = 0; i < length1; i++)    array1[i] = -99;                                // Fills array1 with illegal values to be either overwritten by 0 or user-input

    for (int i = 0; i < length2; i++) {                                                 // Randomly places as many 0 as array2 has ints into array1
        int randIndex= rand() % length1;
        array1[randIndex] = 0; 
    }

    for (int i = 0; i < length1; i++) {
        if (array1[i] == -99)    array1[i] = lesInt("New int in array1: ", -20, 20);    // Fills the rest of array1 with integers
    }
    for(int i = 0; i < length2; i++)
        while (array2[i] == 0)   array2[i] = lesInt("New int in array2: ", -20, 20);    // Fills array2 with integers
    
    cout << "Array 1: ";
    for (int i = 0; i < length1; i++) cout << array1[i] << ' ';
    cout << "\nArray 2: ";
    for (int i = 0; i < length2; i++) cout << array2[i] << ' ';
    cout << endl;


    sortTwoArrays(array1, array2, length1, length2);                                    // Sorts and combines array 1 & 2

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
    for(i; i < aLen; i++) {                 // Loops through array1
        if(a[i] == 0) {                     // Found open spot for an array2 int
            a[i] = b[j];                    // places int from array2 into array1
            j++;                            // Goes to the next int in array2
        }
    }
    for(i = 1; i < aLen; i++) {             // Loops from the second to the last int
        value = a[i];
        j = i;
        while (a[j-1] > value && j > 0) {   // As long as the previous is larger
            a[j] = a[j-1];                  // Moves the int down a spot
            j--;                            // Checks the next int
        }
        a[j] = value;                       // Places the int at the correct spot
    }
    cout << "Sorted array: ";
    for(i = 0; i < aLen; i++) cout << a[i] << ' ';
}
