#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

class Individual {
public:
	Individual(int chromLen);
	virtual ~Individual();

	int chromLength;
	int chromosome[MAX_CHROMLENGTH];
	double fitness;

	void Init();
	void Mutate(double pm);
};

#endif /* INDIVIDUAL_H_ */