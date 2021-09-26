#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

class GA; // forward declaration

class Individual {
	friend class Population;
	public:
		Individual();
		~Individual();

		bool Init();
		double Evaluate();

		bool BitFlip(int pos, double probability);
		void BitFlip(double probability);

	private:
		float RandFrac();

		GA* m_ga;
		double m_fitness;
		bool* m_chromosome;
};

#endif /* INDIVIDUAL_H_ */