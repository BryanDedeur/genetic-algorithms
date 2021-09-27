#include "individual.h"
#include "ga.h"

Individual::Individual() {
	m_ga = nullptr; // this will be manually set
	m_chromLength = 0;
	m_fitness = 0;
	m_chromosome = nullptr;
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

	// create the chromosome
	m_chromLength = m_ga->m_chromSize;
	m_chromosome = new bool[m_chromLength];

	return true;
}

void Individual::Randomize() {
	// randomize each bit
	for(int i = 0; i < m_chromLength; ++i) {
		if(m_ga->RandFrac() < 0.5)
			m_chromosome[i] = 1;
		else
			m_chromosome[i] = 0;
	}
}

double Individual::Evaluate() {
	m_fitness = m_ga->m_evaluator->Evaluate(m_chromosome, m_chromLength);
	return m_fitness;
}

// bool Individual::BitFlip(int pos, double probability) {
// 	if (pos < 0 || pos >= m_ga->m_chromSize) {
// 		cout << "Attempted to bit flip outside the range of the chromosome" << endl;
// 		return false;
// 	}

// 	if (m_ga->RandFrac() < probability)
// 		m_chromosome[pos] = 1 - m_chromosome[pos];

// 	return true;
// }

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

ostream& operator<<(ostream& os, const Individual& individual) {
	os << "[";
	for (int i = 0; i < individual.m_chromLength; ++i) 
    	os << individual.m_chromosome[i];
	os << "] = " << individual.m_fitness;
    return os;
}

Individual& Individual::operator=(const Individual &rhs) {
	if (this != &rhs) {
		this->m_ga = rhs.m_ga;
		// update the pointer information to match new ga chrom size
		if (this->m_chromLength != rhs.m_chromLength) {
			delete[] this->m_chromosome;
			this->m_chromLength = rhs.m_chromLength;
			if (this->m_chromLength != 0)
				this->m_chromosome = new bool[this->m_chromLength];
		}
		
		this->m_fitness = rhs.m_fitness;
		// clone chromosome
		for(int i = 0; i < this->m_chromLength; ++i) 
			this->m_chromosome[i] = rhs.m_chromosome[i]; 		
    }
    return *this;
}

bool Individual::operator<(const Individual &rhs) {
	bool val = this->m_fitness < rhs.m_fitness;
    return val;
}
