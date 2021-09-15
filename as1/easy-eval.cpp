
#include "math.h"
#include "iostream"

long int binToInt(int binary[], int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        if (binary[i] == 1) {
            sum += i / ;
        } 
    }
    return sum;
}

double eval(int sol[]) {
    long int sum = binToInt(sol, 100);
    std::cout << sum << std::endl;
    return 0.0;
}