#ifndef GA_H_
#define GA_H_

#include "population.h"
#include "evaluator.h"

#include <string>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;

class GA {
	friend class Population;
	friend class Individual;
	public:
		GA(Evaluator* eval);
		~GA();

		bool Init(const unsigned int chromSize, const unsigned int popSize, const unsigned int numGens, const float probX, const float probM, int* seeds, const unsigned int numSeeds);
		bool Init(const string settingsFile);
		bool Init();

		bool RunAllSeeds();
		bool RunSeed(const int seed);

		void GatherGenerationStats(int gen);

		void SaveResults();

		double RandFrac();
		int IntInRange(const int& low, const int& high);
	private:
	
		string m_settingsFile;
		string m_resultsFile;

		Population* m_parents;
		Population* m_children;
		Evaluator* m_evaluator;

		// ga settings
		int m_chromSize;
		int m_popSize;
		int m_numGens;
		float m_px;
		float m_pm;

		// seeds
		int m_currentSeed;
		int m_seedCounter;
		int* m_seeds;
		int m_numSeeds;

		// statistics
		double* m_sumMinFitnessPerGeneration;
		double* m_sumAveFitnessPerGeneration;
		double* m_sumMaxFitnessPerGeneration;
		//double* m_sumObjectiveFunctionValuePerGeneration;

		double m_runTime;
		double m_aveTimePerSeed;
		double m_avefitnessPerSeed;
		double m_stdDeviationFitnessPerSeed;
		double m_aveConvergeGen;
		double m_stdDeviationConvergeGenPerSeed;

		Individual m_bestIndividual;
		Individual m_worstIndividual;
};

#endif /* GA_H_ */