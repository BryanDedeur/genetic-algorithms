#include "ga.h"

GA::GA(Evaluator* eval) {
	m_settingsFile = "";
	m_resultsFile = "";
	m_population = nullptr;
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
	m_bestIndividual = 0;
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
	m_px = probX;
	m_pm = probM;
	m_numSeeds = numSeeds;
	m_seeds = seeds;

	m_population = new Population(this);
	if (!m_population->Init())
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
	int* seeds = new int[1];
	seeds[0] = 0;
	return Init(4, 4, 20, 0.7, 0.01, seeds, 1);
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

	// Initialize
	if (!m_population->Init())
		return false;
	
	for(int i = 1; i < m_numGens; ++i) {
		// Select
		// Crossover
		// Mutate
		// Evaluate

		// 	parent->Generation(child);
		// 	child->Evaluate();
		// 	child->Statistics();
		// 	child->Report(i);

		// 	Population *tmp = parent;
		// 	parent = child;
		// 	child = tmp;
	}
	return true;
}
