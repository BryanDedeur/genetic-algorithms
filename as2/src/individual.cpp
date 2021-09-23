#include <individual.h>
#include <ga.h>

Individual::Individual(GA* ga) {
	m_ga = ga;
	m_fitness = 0;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

bool Individual::Init(){
	// for(int i = 0; i < chromLength; i++){
	// 	chromosome[i] = Flip(0.5f);
	// }
}

void Individual::Mutate(double pm){
	// for(int i = 0; i < chromLength; i++){
	// 	if(Flip(pm))
	// 		chromosome[i] = 1 - chromosome[i];
	// }
}