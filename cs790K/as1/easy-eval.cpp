
#include <iostream>
using namespace std;

double binToVal(int binary[], int size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 4 == 0) {
            if (1 - binary[i] == 1) {
                sum += 1;
            }
        } else if (i % 2 == 0) {
            if (binary[i] == 1) {
                sum += 1;
            }
        } else {
            if (binary[i] == 1) {
                sum += 1;
            }
        }
    }
    return sum;
}

double eval(int sol[]) {
    double x = binToVal(sol, 100);
    return x;
}