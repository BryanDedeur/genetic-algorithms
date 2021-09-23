#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

class GA; // forward declaration

class Individual {
	public:
		Individual(GA* ga);
		~Individual();

		bool Init();
		void Mutate(double pm);

	private:
		GA* m_ga;
		double m_fitness;
		int chromosome[1];
};

#endif /* INDIVIDUAL_H_ */