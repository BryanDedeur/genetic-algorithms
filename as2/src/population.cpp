#include "population.h"
#include "ga.h"

Population::Population(GA* ga) {
	m_ga = ga;
	m_numMembers = m_ga->m_popSize * 2;
	m_numAncestors = m_ga->m_popSize;
	m_members = new Individual[m_numMembers];
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;
	m_aveFitness = 0;
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

bool Population::Init() {
	// reset statistics
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;
	m_aveFitness = 0;

	// evaluate the entire population
	for (int i = 0; i < m_numAncestors; ++i) {
		m_members[i].m_ga = m_ga;
		m_members[i].Init();
		m_members[i].Evaluate();

		// gather statistics
		m_sumFitness += m_members[i].m_fitness;
		if(m_minFitness > m_members[i].m_fitness)
	 		m_minFitness = m_members[i].m_fitness;
		if(m_maxFitness < m_members[i].m_fitness)
	 		m_maxFitness = m_members[i].m_fitness;
	}

	return true;
}

bool Population::Evaluate() {
	// reset statistics
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;
	m_aveFitness = 0;

	// evaluate the parents, children are already evaluated
	for (int i = 0; i < m_numAncestors; ++i) {
		m_members[i].Evaluate();

		// gather statistics
		m_sumFitness += m_members[i].m_fitness;
		if(m_minFitness > m_members[i].m_fitness)
	 		m_minFitness = m_members[i].m_fitness;
		if(m_maxFitness < m_members[i].m_fitness)
	 		m_maxFitness = m_members[i].m_fitness;
	}
	return true;
}

// void Population::Report(unsigned long int gen){
// 	// char printbuf[1024];
// 	// sprintf(printbuf, "%4i \t %f \t %f \t %f\n ", (int)gen, min, avg, max);
// 	// WriteBufToFile(std::string(printbuf), options.outfile);
// 	// std::cout << printbuf;
// }

// void Population::Generation(Population *child){
// 	// int pi1, pi2, ci1, ci2;
// 	// Individual *p1, *p2, *c1, *c2;
// 	// for(int i = 0; i < options.popSize; i += 2){
// 	// 	pi1 = ProportionalSelector();
// 	// 	pi2 = ProportionalSelector();

// 	// 	ci1 = i;
// 	// 	ci2 = i + 1;

// 	// 	p1 = members[pi1]; p2 = members[pi2];
// 	// 	c1 = child->members[ci1]; c2 = child->members[ci2];

// 	// 	XoverAndMutate(p1, p2, c1, c2);
// 	// }
// }



// int Population::ProportionalSelector(){
// 	int i = -1;
// 	// float sum = 0;
// 	// float limit = RandomFraction() * sumFitness;
// 	// do {
// 	// 	i = i + 1;
// 	// 	sum += members[i]->fitness;
// 	// } while (sum < limit && i < options.popSize-1 );

// 	return i;
// }

// void Population::XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2){

// 	// for(int i = 0; i < options.chromLength; i++){ //First copy
// 	// 	c1->chromosome[i] = p1->chromosome[i];
// 	// 	c2->chromosome[i] = p2->chromosome[i];
// 	// }
// 	// if(Flip(options.px)){ // if prob, then cross/exchange bits
// 	// 	OnePoint(p1, p2, c1, c2);
// 	// }

// 	// c1->Mutate(options.pm);
// 	// c2->Mutate(options.pm);
// }

// void Population::OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
// 	// int t1 = IntInRange(0, options.chromLength);
// 	// for(int i = t1; i < options.chromLength; i++){
// 	// 	c1->chromosome[i] = p2->chromosome[i];
// 	// 	c2->chromosome[i] = p1->chromosome[i];
// 	// }
// }

// void Population::TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
// 	// int t1 = IntInRange(0, options.chromLength);
// 	// int t2 = IntInRange(0, options.chromLength);
// 	// int xp1 = std::min(t1, t2);
// 	// int xp2 = std::max(t1, t2);
// 	// for(int i = xp1; i < xp2; i++){
// 	// 	c1->chromosome[i] = p2->chromosome[i];
// 	// 	c2->chromosome[i] = p1->chromosome[i];
// 	// }
// }