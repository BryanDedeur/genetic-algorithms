#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include <math.h>
#include <iostream>

using namespace std;

class Evaluator {
    public:
        Evaluator();
        ~Evaluator();

        double Evaluate(bool* data, const int& length);

        int GetEncodedBitLength();
        double BinaryToDecimal(bool* binaryData, const int& start, const int& end);

    private:
        int numValues;
        float minValue;
        float maxValue;
        int valueBitLength;
        int totalBitLength;
        int floatingPoint; // location of the decimal
};

#endif /* EVALUATOR_H_ */