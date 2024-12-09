#include <iostream>     // cout
#include <stdlib.h>     // rand
#include <iomanip>      // setw()

using namespace std;

const int COUNT = 100;

int main() {
    int numbers[COUNT];
    int total = 0, valids = 0, highest = 0, i = 0;
    for(i; i < COUNT; i++) {                // Generates all the numbers
        numbers[i] = (rand() % 35);
        cout << numbers[i] << ' ';
    }
    cout << "\n\n";

    for(i = 0; i < COUNT; i++) {
        if(numbers[i] > highest) {          // Highest number thus far
            highest = numbers[i];
            valids++;
            total += highest;
        }
    }
    cout << fixed << setprecision(0) << setw(3)
         << "Total sum:           " << total 
         << "\nnumbers summed up: " << valids << endl; 
}