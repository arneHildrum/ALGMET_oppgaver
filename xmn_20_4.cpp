#include <iostream>
#include "LesData2.h"
using namespace std;

int removeDuplicates(int a[], const int n);


/**
 * Main program
 */
int main() {
    int amount = lesInt("How many numbers do you want in the array: ", 0, 100);
    int array[amount];
    for(int i = 0; i < amount; i++) array[i] = lesInt("Write the numbers in ascending order: ", 1, 100);
    for(int i = 0; i < amount; i++)
        cout << array[i] << ' ';
    cout << "\n\n";
    
    int unique = removeDuplicates(array, amount);
    cout << unique << " unique number(s) found. \n"
                   << "New array: \n";
    for(int i = 0; i < unique; i++)
        cout << array[i] << ' ';

    return 0;
}


/**
 * @brief Removes duplicate values from a sorted array, fills the tail with zeros, and returns the number of duplicates.
 * 
 * @param a The array to process, containing positive integers sorted in ascending order.
 * @param n The number of elements in the array.
 * @return The number of duplicate elements found in the array.
 */
int removeDuplicates(int a[], const int n) {
    if (n < 2)  return 0;                                             // Too few elements for duplicates to exist
    
    int numLeft = n, duplicates = 0, k, j;   
    
    for(int i = 0; i < numLeft; i++) {                                // Iterate through all elements that could still be unique
        j = 0;                                                        // Resets the counter for duplicates
        while(a[i + j + 1] == a[i]) j++;                              // Find all duplicates of the current value
        numLeft   -= j;                                               // Reduce the count of potentially unique elements
        duplicates  += j;                                             // Increase the total count of duplicates
        
        for(int k = 1; k < n - j; k++)     a[i + k] = a[i + j + k];  // Overwrite duplicates with the next values in the array
        for(k = numLeft; a[k] != 0; k++) a[k] = 0;                   // Fill the trailing part of the array with zeros
    }
    return  n - duplicates;                                          // Return the total number of unique numbers
}