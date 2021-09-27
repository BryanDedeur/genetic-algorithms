#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <ostream>
using namespace std;

class GA; // forward declaration

class Individual {
	friend class Population;
	public:
		Individual();
		~Individual();

		bool Init();
		void Randomize();
		double Evaluate();

		// bool BitFlip(int pos, double probability);
		// void BitFlip(double probability);

		// operator overloading
		friend ostream& operator<<(ostream& os, const Individual& ind);
		Individual& operator=(const Individual &rhs);
		bool operator<(const Individual &rhs);


	private:
		float RandFrac();

		GA* m_ga;
		double m_fitness;
		bool* m_chromosome;
		int m_chromLength;
};

#endif /* INDIVIDUAL_H_ */