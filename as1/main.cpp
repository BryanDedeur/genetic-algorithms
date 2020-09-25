#include <iostream>

using namespace std;

double eval(int *pj);

int main()
{
    int vec[100];

    int i;

    for(i = 0; i < 100; i++){
        vec[i] = 0;
    }
    double fitness;
    fitness = eval(vec);
    cout << "fitness = " << fitness << endl;

}

