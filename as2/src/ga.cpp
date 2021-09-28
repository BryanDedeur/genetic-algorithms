#include "ga.h"

GA::GA(Evaluator* eval) {
	m_settingsFile = "";
	m_resultsFile = "";
	m_parents = nullptr;
	m_children = nullptr;
	m_evaluator = eval;
	m_chromSize = 0;
	m_popSize = 0;
	m_numGens = 0;
	m_px = 0;
	m_pm = 0;
	m_currentSeed = 0;
	m_seedCounter = 0;
	m_seeds = nullptr;
	m_numSeeds = 0;
	m_runTime = 0;
	m_aveTimePerSeed = 0;
	m_bestIndividual = Individual();
	m_worstIndividual = Individual();
	m_avefitnessPerSeed = 0;
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}

bool GA::Init(const unsigned int chromSize, const unsigned int popSize, const unsigned int numGens, const float probX, const float probM, int* seeds, const unsigned int numSeeds) {
	m_chromSize = chromSize;
	if (popSize % 2 != 0) {
		cout << "Population size must be even" << endl;
		return false;
	}
	m_popSize = popSize;
	m_numGens = numGens;
	if (probX < 1 / RAND_FRAC_PREC || probM < 1 / RAND_FRAC_PREC) {
		cout << "Increase random fraction precision" << endl;
		return false;
	}
	m_px = probX;
	m_pm = probM;
	m_numSeeds = numSeeds;
	m_seeds = new int[numSeeds];
	m_seeds = seeds;

	m_parents = new Population(this);
	if (!m_parents->Init())
		return false;

	m_children = new Population(this);
	if (!m_children->Init())
		return false;

	if (m_evaluator == nullptr) {
		cout << "No evaluator passed to the GA" << endl;
		return false;
	}
	
	cout << "GA initialized:";
	cout << " px(" << m_px << ") ";
	cout << " pm(" << m_pm << ") ";
	cout << " chrom len(" << m_chromSize << ") ";
	cout << " pop size(" << m_popSize << ") ";
	cout << " gens(" << m_numGens << ") ";
	cout << " seeds(" << m_numSeeds << ")" << endl;

	return true;
}

bool GA::Init(const string settingsFile) {
	return true;
}

bool GA::Init() {
	// inject some default settings
	int numSeeds = 30;
	int* seeds = new int[numSeeds];
	for (int i = 0; i < numSeeds; i++) {
		seeds[i] = (i * 1000)/numSeeds;
	}
	return Init(20, 10, 20, 0.7, 0.1, seeds, 1);
}

bool GA::RunAllSeeds() {
	for (int i = 0; i < m_numSeeds; ++i) {
		if (!RunSeed(m_seeds[i]))
			return false;
	}
	return true;
}

bool GA::RunSeed(const int seed) {
	// Set the new seed
	m_currentSeed = seed;
	m_seedCounter++;
	srand(m_currentSeed);

	cout << "running on seed (" << seed << "): " << m_seedCounter << "/" << m_numSeeds << endl;

	// Randomize
	m_parents->Randomize();
	
	for(int g = 0; g < m_numGens; ++g) {
		cout << *m_parents << endl;
		for(int i = 0; i < m_popSize; i += 2) {
			// Select
			m_parents->SelectProportional();

			// Breed
			m_parents->CloneChildrenFromSelected(m_children, i, i + 1);

			// Crossover
			m_children->CrossoverOnePoint(i, i + 1);

			// Mutate
			m_children->Mutate(i, i + 1);

			// Evaluate
			m_children->Evaluate(i, i + 1);
		}

		// Record Statistics
		if (m_bestIndividual < m_children->m_best) 
			m_bestIndividual = m_children->m_best;

		// Children become parents
		Population* temp = m_parents;
		m_parents = m_children;
		m_children = temp;

		m_children->ResetStats();
	}

	cout << "Best found is: " << m_bestIndividual << endl;
	return true;
}

float GA::RandFrac() {
	return ((float) (rand() % RAND_FRAC_PREC)) / (float) RAND_FRAC_PREC;
}
