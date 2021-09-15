#include <iostream>
#include <math.h>
using namespace std;

const int MAX_LEN = 100;
const int MAX_ATTEMPTS = 100000;
const int NUM_RUNS = 100;

// Probability that works well for eval.o
// const float BIT_TUNE_VALUE = 0.0001f;
// const float STRING_TUNE_VALUE = 0.0001f;

// Probability that works well for eval1.o
const float BIT_TUNE_VALUE = 0.001f; // lower val = more exploitation
const float STRING_TUNE_VALUE = 0.01f; // higher val = more exploration

void init(int sol[], const int size) {
    for(int i = 0; i < size; ++i){
        sol[i] = rand() % 2; // should be random
        // if (i < 85) {
        //     sol[i] = 1;
        // } else {
        //     sol[i] = 0;
        // }
    }
}

//double eval(int *pj);

float binToVal(int binary[], int size) {
    float sum = 0;
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
    float x = binToVal(sol, 100);
    return clamp(std::ceil(sin(x/6)*x + 15), 0, 100);
}

void modify(int oldSol[], int newSol[], float bitChangeCounter[], int unsuccessfulAttemps, const int size) {
    float probabilityOfRandomChange = STRING_TUNE_VALUE * (unsuccessfulAttemps / MAX_LEN);
    float probabilityOfBitChange = 0;
    for (int i = 0; i < MAX_LEN; ++i) {
        // Determine a probability based on the number of changes. the more changes the less probable it will change
        probabilityOfBitChange = BIT_TUNE_VALUE * (MAX_LEN / bitChangeCounter[i]);
        if (rand() % MAX_LEN < (probabilityOfBitChange + probabilityOfRandomChange)) {
            newSol[i] = 1 - oldSol[i];
        } else {
            newSol[i] = oldSol[i];
        }
    }
}

void clone(int cloneMe[], int intoMe[], float bitChangeCounter[], const int size) {
    for(int i = 0; i < size; ++i) {
        if (cloneMe[i] != intoMe[i])
            bitChangeCounter[i]++;
        intoMe[i] = cloneMe[i]; // should be random
    }
}

float runHillClimber(float *sumFitness, int *sumAttempts) {
            // Hill climber
        srand(time(NULL));

        // 1. Initialize
        int solution_0[MAX_LEN];
        init(solution_0, MAX_LEN);

        // 2. Evaluate
        double fitness_0 = eval(solution_0);
        //std::cout << "Initial fitness: " << fitness_0 << std::endl;

        // 3. Climb some hills
        int attemptCount = 0;
        int unsuccessfulAttempts = 0;
        int solution_1[MAX_LEN] = {1};
        double fitness_1 = 0;

        float bitChangeCounter[MAX_LEN] = {1.0f};
        while(fitness_0 != 100 && attemptCount < MAX_ATTEMPTS) {
            attemptCount++;
            modify(solution_0, solution_1, bitChangeCounter, unsuccessfulAttempts, MAX_LEN);
            fitness_1 = eval(solution_1);
            if (fitness_1 > fitness_0) {
                unsuccessfulAttempts = 0;
                clone(solution_1, solution_0, bitChangeCounter, MAX_LEN);
                fitness_0 = fitness_1;
                //std::cout << "Improvement: " << fitness_0 << " at attempt " << attemptCount << std::endl;
            } else {
                unsuccessfulAttempts++;
            }
        }

        //std::cout << "Final fitness: " << fitness_0 << std::endl;
        *sumFitness += fitness_0;
        *sumAttempts += attemptCount;
        return fitness_0;
}

int main()
{
    float sumFitness = 0;
    int sumAttempts = 0;
    float bestFitness = 0;
    float tempFitness = 0;
    for (int i = 0; i < NUM_RUNS; ++i) {
        tempFitness = runHillClimber(&sumFitness, &sumAttempts);
        if (tempFitness > bestFitness) {
            bestFitness = tempFitness;
        }
    }

    cout << "Best fitness over " << NUM_RUNS << " runs: " << bestFitness << endl;
    cout << "Average fitness over " << NUM_RUNS << " runs: " << sumFitness/NUM_RUNS << endl;
    cout << "Average attempts over " << NUM_RUNS << " runs: " << sumAttempts/NUM_RUNS << endl;

    return 0;
}

