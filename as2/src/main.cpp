
#include "evaluator.h"
#include "ga.h"

using namespace std;

int main() {

	Evaluator* eval = new Evaluator();

	GA ga = GA(eval);
	if (!ga.Init())
		return 1;

	if (!ga.RunAllSeeds())
		return 1;

	// ga.Init();
	// ga.Run();
    return 0;
}