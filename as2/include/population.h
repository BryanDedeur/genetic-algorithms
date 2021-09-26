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

		void IncrementChildrenIndicies(int startIndex);
		void MakeChildrenFromSelected();

		// Selection
		void SelectProportional();

		// Crossovers
		// void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		// void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		void CrossoverOnePoint();

		// Mutators
		void Mutate();


		// Evaluate


	private:
		GA* m_ga;

		Individual *m_members;
		int m_numMembers; // 2x pop size
		int m_numAncestors; // 1x pop size

		int m_selected1;
		int m_selected2;
		int m_child1;
		int m_child2;

		// statistics
		double m_minFitness;
		double m_maxFitness;
		double m_sumFitness;
		double m_aveFitness;


};

#endif /* POPULATION_H_ */