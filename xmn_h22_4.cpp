#include <iostream>     // cout
#include <cmath>        // sqrt

using namespace std;


int main() {
    int dsum, i, j, sRoot, diff, valids = 0;
    for(i = 1; i <= 1000000; i++) {               // Loops through every number from 1 - 1 million
        dsum = i;                                 // Resets the sum
        for(j = 1; j <= i/2; j++)                 // Loops through all the numbers that can possibly divide n
            if((i % j) == 0)    dsum += j;        // Adds the divisor if it can divide i
        if(dsum > 2 * i) {                        // If Sum of all divisors is twice as large as n
            diff = (dsum - (2*i));                // Finds the difference between the divisor sum and 2n
            sRoot = sqrt(diff);                   // Finds the square root of the difference
            if(sRoot * sRoot == diff) valids++;   // "Counts as valid if you can get back the difference by squaring the root again,
        }                                         // Since integers don't save the float value, squaring it back up again would give a smaller amount"
    }
    cout << "\nTotal amount of valid answers: " << valids << endl;
    return 0;
}