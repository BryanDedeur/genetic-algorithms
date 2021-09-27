#include "population.h"
#include "ga.h"

Population::Population(GA* ga) {
	m_ga = ga;
	m_totalMembers = 0;
	m_members = nullptr;
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;
	m_best = Individual();
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

bool Population::Init() {
	// reset statistics
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;

	// make sure the individuals exist and are initialized
	m_totalMembers = m_ga->m_popSize;
	m_members = new Individual[m_totalMembers];
	for (int i = 0; i < m_totalMembers; ++i) {
		m_members[i].m_ga = m_ga;
		m_members[i].Init(); 
	}

	return true;
}

void Population::Randomize() {
	ResetStats();
	// evaluate the entire population
	for (int i = 0; i < m_totalMembers; ++i) {
		m_members[i].m_ga = m_ga;
		m_members[i].Randomize();
		m_members[i].Evaluate();

		// gather statistics
		m_sumFitness += m_members[i].m_fitness;
		if(m_minFitness > m_members[i].m_fitness)
	 		m_minFitness = m_members[i].m_fitness;
		if(m_maxFitness < m_members[i].m_fitness)
	 		m_maxFitness = m_members[i].m_fitness;
		if(m_best.m_fitness < m_members[i].m_fitness)
			m_best = m_members[i];
	}
}

void Population::ResetStats() {
	// reset statistics
	m_sumFitness = 0;
	m_minFitness = INFINITY;
	m_maxFitness = -INFINITY;
	m_best.m_fitness = 0;
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

// void Population::IncrementChildrenIndicies(int startIndex) {
// 	m_child1 = startIndex + m_ga->m_popSize;
// 	m_child2 = m_child1 + 1;
// }

void Population::CloneChildrenFromSelected(const Population* childPopulation, const int& child1, const int& child2) {
	for(int i = 0; i < m_ga->m_chromSize; i++) {
		childPopulation->m_members[child1] = m_members[m_selected1];
		childPopulation->m_members[child2] = m_members[m_selected2];
	}
}

void Population::SelectProportional() {
	// select two parents
	for (int j = 0; j < 2; ++j) {
		int i = -1;
		float sum = 0;
		float limit = m_ga->RandFrac() * m_sumFitness;
		do {
			sum += m_members[i].m_fitness;
			i++;
		} while (sum < limit && i < m_ga->m_popSize - 1);
		if (j == 0)
			m_selected1 = i;
		else 
			m_selected2 = i;
	}
}

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

void Population::CrossoverOnePoint(const int& child1, const int& child2) {
	// by this point the children are direct copies of the parents
	if (m_ga->RandFrac() < m_ga->m_px) { 
		// pick a point excluding the first. If we include the first we clone the chrome
		int point = (m_ga->RandFrac() * (m_ga->m_chromSize - 1)) + 1;
		bool temp = 0;
		for(int i = point; i < m_ga->m_chromSize; i++) {
			temp = m_members[child1].m_chromosome[i];
			m_members[child1].m_chromosome[i] = m_members[child2].m_chromosome[i];
			m_members[child2].m_chromosome[i] = temp;
		}
	}
}

void Population::Mutate(const int& child1, const int& child2) {
	for (int j = 0; j < m_ga->m_chromSize; ++j) {
		// mutate child one if chances are right
		if (m_ga->RandFrac() < m_ga->m_pm)
			m_members[child1].m_chromosome[j] = 1 - m_members[child1].m_chromosome[j];
		// mutate child two if chances are right
		if (m_ga->RandFrac() < m_ga->m_pm)
			m_members[child2].m_chromosome[j] = 1 - m_members[child2].m_chromosome[j];
	}
}

void Population::Evaluate(const int& child1, const int& child2) {
	m_members[child1].Evaluate();
	m_members[child2].Evaluate();

	// gather statistics
	m_sumFitness += m_members[child1].m_fitness + m_members[child2].m_fitness;

	// child 1
	if(m_minFitness > m_members[child1].m_fitness)
		m_minFitness = m_members[child1].m_fitness;
	if(m_maxFitness < m_members[child1].m_fitness)
		m_maxFitness = m_members[child1].m_fitness;
	if(m_best.m_fitness < m_members[child1].m_fitness)
		m_best = m_members[child1];
	// child 2
	if(m_minFitness > m_members[child2].m_fitness)
		m_minFitness = m_members[child2].m_fitness;
	if(m_maxFitness < m_members[child2].m_fitness)
		m_maxFitness = m_members[child2].m_fitness;
	if(m_best.m_fitness < m_members[child2].m_fitness)
		m_best = m_members[child2];
}

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

ostream& operator<<(ostream& os, const Population& population) {
    os << "best: " << population.m_maxFitness << " ave: " << population.m_sumFitness / population.m_totalMembers << " worst: " << population.m_minFitness;
    return os;
}