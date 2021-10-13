#include "evaluator.h"

Evaluator::Evaluator() {
	numValues = 3;
	minValue = -5.12;
	maxValue = 5.12;
	totalBitLength = 100;
	valueBitLength = 0;
	floatingPoint = 0;
}

Evaluator::~Evaluator() {
	
}

int Evaluator::GetEncodedBitLength() {
	// if we hardcode a bit length then just return that.
	if (totalBitLength != 0)
		return totalBitLength;

	// compute bit length based on min max fitness and precision
	float range = maxValue - minValue;
	int significand = floor(range * pow(10, -floatingPoint));
	int exponent = 0;

	int numBits = 0;
	int decValue = 0;
	while (decValue < significand) {
		decValue += pow(2, numBits);
		numBits++;
	}
	valueBitLength = numBits * numValues;
	return numBits;
}

double Evaluator::BinaryToDecimal(bool* binaryData, const int& start, const int& end) {
	double value = 0;
	// get significand value, first bit is least significant
	for (int i = start; i < end; ++i)
		if (binaryData[i] == 1) 
			value += pow(2, i);

	// insert floating point
	value *= pow(10, -floatingPoint);
	return value;
}

double DeJong1(float* x, const int& length) {
	double value = 0;
	for (int i = 0; i < length; ++i)
		value += pow(x[i], 2);
	return value;
}

double DeJong2(float* x, const int& length) {
	return 100 * pow((pow(x[0], 2) - x[1]), 2) + pow((1 - x[0]), 2);;
}

double DeJong3(float* x, const int& length) {
	double value = 0;
	for (int i = 0; i < length; ++i) {
		value += (int)x[i];
	}
	return value;
}

double DeJong4(float* x, const int& length) {
	//double value = 0;
	//for (int i = 0; i < length; ++i) {
	//	value += i * pow(x[i], 4) + gauss(0, 1);
	//}
	return 0;
}

double DeJong5(float* x, const int& length) {
	//double value = 0.002;
	//for (int i = 0; i < length; ++i) {
	//	for (int i = 0; i < 2; ++i) {

	//	}
	//	value += 
	//}
	return 0;
}

double OneSum(bool* binaryData, const int& length) {
	double sum = 0;
	for (int i = 0; i < length; i++)
		sum += (binaryData[i] == 1 ? 1 : 0);
	return sum;
}

double XSquared(bool* binaryData, const int& length) {
	double sum = 0;
	return sum;
}

double Evaluator::Evaluate(bool* binaryData, const int& length) {
	//float* xValues = new float[numValues];
	//for (int i = 0; i < numValues; ++i) {
	//	xValues[i] = BinaryToDecimal(binaryData, i * valueBitLength, (i + 1) * valueBitLength);
	//}

	//double fitness = DeJong1(xValues, numValues);

	//delete[] xValues;

	double fitness = OneSum(binaryData, length);

	return fitness;
}