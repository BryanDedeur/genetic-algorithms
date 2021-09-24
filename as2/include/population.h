#ifndef POPULATION_H_
#define POPULATION_H_

#include "individual.h"

class GA; // forward declaration

class Population {
	friend class Individual;
	public:
		Population(GA* ga);
		~Population();

		bool Init();
		bool Evaluate();

		// void Generation(Population *child);
		// void Report(unsigned long int gen);
		// void Statistics();

		// int ProportionalSelector();
		// void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		// void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		// void OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

	private:
		GA* m_ga;

		Individual *m_members;
		int m_numMembers; // 2x pop size
		int m_numAncestors; // 1x pop size

		// statistics
		double m_minFitness;
		double m_maxFitness;
		double m_sumFitness;
		double m_aveFitness;
};

#endif /* POPULATION_H_ */