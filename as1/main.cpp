#include <iostream>
using namespace std;

const int MAX_LEN = 100;
const int MAX_ATTEMPTS = 100000;
const int NUM_RUNS = 30;

void init(int sol[], const int size) {
    for(int i = 0; i < size; ++i){
        sol[i] = rand() % 2; // should be random
    }
}

double eval(int *pj);

void modify(int oldSol[], int newSol[], int unsuccessfulAttemps, const int size) {
    float probabilityOfChange = 0.1f * (unsuccessfulAttemps / MAX_LEN);
    for (int i = 0; i < MAX_LEN; ++i) {
        if (rand() % 100 < probabilityOfChange) {
            newSol[i] = 1 - oldSol[i];
        } else {
            newSol[i] = oldSol[i];
        }
    }
}

void clone(int cloneMe[], int intoMe[], const int size) {
    for(int i = 0; i < size; ++i){
        intoMe[i] = cloneMe[i]; // should be random
    }
}

void runHillClimber(float *sumFitness, int *sumAttempts) {
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
        int unsuccessfulAttemps = 0;
        int solution_1[MAX_LEN];
        double fitness_1 = 0;

        float probabilityOfBitChange[MAX_LEN] = {1.0f};
        while(fitness_0 != 100 && attemptCount < MAX_ATTEMPTS) {
            attemptCount++;
            modify(solution_0, solution_1, unsuccessfulAttemps, MAX_LEN);
            fitness_1 = eval(solution_1);
            if (fitness_1 > fitness_0) {
                unsuccessfulAttemps = 0;
                clone(solution_1, solution_0, MAX_LEN);
                fitness_0 = fitness_1;
                //std::cout << "Improvement: " << fitness_0 << " at attempt " << attemptCount << std::endl;
            } else {
                unsuccessfulAttemps++;
            }
        }

        //std::cout << "Final fitness: " << fitness_0 << std::endl;
        *sumFitness += fitness_0;
        *sumAttempts += attemptCount;
}

int main()
{
    float sumFitness = 0;
    int sumAttempts = 0;
    for (int i = 0; i < NUM_RUNS; ++i) {
        runHillClimber(&sumFitness, &sumAttempts);
    }

    cout << "Average fitness over 30 runs: " << sumFitness/NUM_RUNS << endl;
    cout << "Average attempts over 30 runs: " << sumAttempts/NUM_RUNS << endl;

    return 0;
}

