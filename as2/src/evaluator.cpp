#include "evaluator.h"

Evaluator::Evaluator() {

}

Evaluator::~Evaluator() {
	
}

double Evaluator::Evaluate(bool* binaryData, int length) {
	// decode

	// calculate fitness
	double sum = 0;
	for(int i = 0; i < length; i++){
		sum += (binaryData[i] == 1 ? 1: 0);
	}
	return sum;
}