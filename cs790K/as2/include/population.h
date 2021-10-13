#ifndef POPULATION_H_
#define POPULATION_H_

#include "individual.h"
#include <ostream>
using namespace std;

class GA; // forward declaration

class Population {
	friend class Individual;
	public:
		Population(GA* ga);
		~Population();

		bool Init();
		void Randomize();

		// void Generation(Population *child);
		// void Report(unsigned long int gen);
		// void Statistics();
		void ResetStats();

		void CloneChildrenFromSelected(const Population* childPopulation, const int& child1, const int& child2);

		// Selection
		void SelectProportional();

		// Crossovers
		// void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		// void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
		void CrossoverOnePoint(const int& child1, const int& child2);

		// Mutators
		void Mutate(const int& child1, const int& child2);

		// Evaluate
		void Evaluate(const int& child1, const int& child2);

		// operator overloading
		friend ostream& operator<<(ostream& os, const Population& pop);
		Individual m_best;

		// statistics
		double m_minFitness;
		double m_maxFitness;
		double m_sumFitness;

	private:
		GA* m_ga;

		Individual *m_members;
		int m_totalMembers;

		int m_selected1;
		int m_selected2;
		int* m_selectionCounts;


};

#endif /* POPULATION_H_ */