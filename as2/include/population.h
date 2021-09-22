#ifndef POPULATION_H_
#define POPULATION_H_

#include <individual.h>

class GA; // forward declaration

class Population {
public:
	Population(GA* ga);
	virtual ~Population();
	//------------------------

	Options options;
	Individual *members[MAXPOP];
	double avg, min, max, sumFitness;


	void Init();
	void Evaluate();
	void Generation(Population *child);
	void Report(unsigned long int gen);
	void Statistics();

	int ProportionalSelector();
	void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

};

#endif /* POPULATION_H_ */