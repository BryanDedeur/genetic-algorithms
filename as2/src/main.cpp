#include <iostream>
#include <ga.h>

using namespace std;

int main() {
	GA ga = GA(argc, argv);

	ga.Init();
	ga.Run();
    return 0;
}