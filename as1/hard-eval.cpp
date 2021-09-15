
#include <math.h>
#include <iostream>
using namespace std;

double binToVal(int binary[], int size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        if (binary[i] == 1) {
            sum += 1;
        }
    }
    return sum; //(sum / 4950) * 100;
}

double clamp(double val, double min, double max){
    if (val > max) 
        return max;
    if (val < min)
        return min;
    return val;
}

double eval(int sol[]) {
    double x = binToVal(sol, 100);
    return clamp(std::ceil(sin(x/6)*x + 15), 0, 100);
}