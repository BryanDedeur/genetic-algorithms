#include "individual.h"
#include "ga.h"

Individual::Individual() {
	m_ga = nullptr; // this will be manually set
	m_fitness = 0;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

bool Individual::Init() {
	// make sure the ga has been pointed to
	if (m_ga == nullptr) {
		cout << "GA must exist for initializing individuals" << endl;
		return false;
	}

	// create the chromosome and randomly initialize it
	m_chromosome = new bool[m_ga->m_chromSize];
	for(int i = 0; i < m_ga->m_chromSize; ++i) {
		// randomize
		if(m_ga->RandFrac() < 0.5)
			m_chromosome[i] = 1;
		else
			m_chromosome[i] = 0;
			
	}
	return true;
}

double Individual::Evaluate() {
	m_fitness = m_ga->m_evaluator->Evaluate(m_chromosome, m_ga->m_chromSize);
	return m_fitness;
}

bool Individual::BitFlip(int pos, double probability) {
	if (pos < 0 || pos >= m_ga->m_chromSize) {
		cout << "Attempted to bit flip outside the range of the chromosome" << endl;
		return false;
	}

	if (m_ga->RandFrac() < probability)
		m_chromosome[pos] = 1 - m_chromosome[pos];

	return true;
}

// flips any bit in the chromosome with a probability
// void Individual::BitFlip(double probability) {
// 	BitFlip(rand() % m_ga->m_chromSize, probability);
// }


// void Individual::Mutate(double pm){
// 	// for(int i = 0; i < chromLength; i++){
// 	// 	if(Flip(pm))
// 	// 		chromosome[i] = 1 - chromosome[i];
// 	// }
// }