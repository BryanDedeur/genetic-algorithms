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
	delete[] m_members;
	m_ga = nullptr;
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

void Population::CloneChildrenFromSelected(const Population* childPopulation, const int& child1, const int& child2) {
	for(int i = 0; i < m_ga->m_chromSize; i++) {
		childPopulation->m_members[child1] = m_members[m_selected1];
		childPopulation->m_members[child2] = m_members[m_selected2];
	}
}

void Population::SelectProportional() {
	for (int j = 0; j < 2; ++j) {
		int i = -1;
		float sum = 0;
		float limit = m_ga->RandFrac() * m_sumFitness;
		do {
			i++;
			sum += m_members[i].m_fitness;
		} while (sum < limit && i < m_ga->m_popSize - 1);
		if (j == 0)
			m_selected1 = i;
		else 
			m_selected2 = i;
	}
}

void Population::CrossoverOnePoint(const int& child1, const int& child2) {
	// by this point the children are direct copies of the parents
	if (m_ga->RandFrac() < m_ga->m_px) { 
		// pick a point greater than or equal to low and strictly less than high
		int point = m_ga->IntInRange(0, m_ga->m_chromSize);
		//cout << "Crossover point: " << point << endl;
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

ostream& operator<<(ostream& os, const Population& population) {
    os << "best: " << population.m_maxFitness << " ave: " << population.m_sumFitness / population.m_totalMembers << " worst: " << population.m_minFitness;
	//for (int i = 0; i < population.m_totalMembers; ++i) {
	//	os << i << population.m_members[i] << endl;
	//}
    return os;
}