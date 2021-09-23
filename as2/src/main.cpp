
#include <ga.h>

using namespace std;

int main() {

	GA ga = GA();
	if (!ga.Init())
		return 1;

	if (!ga.RunAllSeeds())
		return 1;

	// ga.Init();
	// ga.Run();
    return 0;
}