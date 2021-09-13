#include <iostream>
using namespace std;

const int MAX_LEN = 100;
const int MAX_ATTEMPTS = 1000;

void init(int sol[], const int size) {
    for(int i = 0; i < size; ++i){
        sol[i] = 0; // should be random
    }
}

double eval(int *pj);

void modify(int oldSol[], int newSol[], const int size) {

}

void clone(int cloneMe[], int intoMe[], const int size) {
    for(int i = 0; i < size; ++i){
        intoMe[i] = cloneMe[i]; // should be random
    }
}

int main()
{
    // Hill climber

    // 1. Initialize
    int solution_0[MAX_LEN];
    init(solution_0, MAX_LEN);

    // 2. Evaluate
    double fitness_0 = eval(solution_0);
    std::cout << "Initial fitness: " << fitness_0 << std::endl;

    // 3. Climb some hills
    int attemptCount = 0;
    int solution_1[MAX_LEN];
    double fitness_1 = 0;
    while(fitness_0 != 100 && attemptCount < MAX_ATTEMPTS) {
        attemptCount++;
        modify(solution_0, solution_1, MAX_LEN);
        fitness_1 = eval(solution_1);
        if (fitness_1 > fitness_0) {
            clone(solution_1, solution_0, MAX_LEN);
            fitness_0 = fitness_1;
            std::cout << "Climb: " << fitness_0 << " at attempt " << attemptCount << std::endl;
        }
    }

    std::cout << "Final fitness: " << fitness_0 << std::endl;

    return 0;
}

