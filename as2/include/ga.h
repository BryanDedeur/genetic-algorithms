#ifndef GA_H_
#define GA_H_

#include <Population.h>
#include <Options.h>

class GA {
public:
	GA(int argc, char *argv[]);
	virtual ~GA();

	//--------------------------------
	Population *parent;
	Population *child;
	Options options;


	void SetupOptions(int argc, char*argv[]);

	void Init();
	void Run();
private:
};

#endif /* GA_H_ */