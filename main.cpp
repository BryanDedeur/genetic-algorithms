/*
	Author: Bryan Dedeurwaerder
	Date: 9/5/2021
	Project: CS 790K Genetic Algorithms As0
	Professor: Dr. Sushil Louis
*/

#include <iostream> 	// cout
#include <math.h> 		// pow
#include <string.h> 	// memcpy
#include <vector>		// for cache

using namespace std;

const int STATE_SIZE = 7; 					// 7 elements per state, 3 missionaries, 3 cannibals
const int SEARCH_SPACE_SIZE = 128; 			// 2^7 = 128 possible states
const int MAX_LOCATIONS = 2; 				// 2 locations, left river, right river
const int GROUP_SIZE = 3; 					// 3 missionaries or 3 cannibals
const int NUM_PEOPLE = 6;					// 3 missionaries and 3 cannibals
const int BOAT_CAPACITY = 3; 				// 2 seats
const short unsigned int RIGHT_RIVER = 1;	// right river
const short unsigned int LEFT_RIVER = 0;	// left river

bool vistedSearchSpace [SEARCH_SPACE_SIZE] = {0};

int bestDepth = 10000;

short unsigned int* searchSpaceBinary[SEARCH_SPACE_SIZE][STATE_SIZE] = {0};


// ---------------------------------------- HELPER FUNCTIONS -------------------------------------------------

short unsigned int* deepStateCopy(short unsigned int original[]) {
	short unsigned int *newState = new short unsigned int[STATE_SIZE]();
	memcpy(newState, original, sizeof(short unsigned int) * STATE_SIZE);
	return newState;
}

int binaryToInt(short unsigned int state[]) {
	int value = 0;
	for (int i = NUM_PEOPLE; i >= 0; i--)
		if (state[i] == 1)
			value += pow(2, i);
	return value;
}

short unsigned int* intToBinary(int value) {
	short unsigned int *binary = new short unsigned int[STATE_SIZE]();
	for (int i = NUM_PEOPLE; i >= 0; i--)
		if (value >= pow(2, i)) {
			binary[i] = 1;
			value -= pow(2, i);
		}
	return binary;
}

void printState(short unsigned int state[]) {
	for (int j = 0; j < STATE_SIZE; ++j) 
		cout << state[j];
	cout << endl;
}

void printSearchSpace(short unsigned int searchSpace[][STATE_SIZE]) {
	for (int i = 0; i < SEARCH_SPACE_SIZE; ++i) {
		cout << i << ": ";
		printState(searchSpace[i]);
	}
}

int differences(short unsigned int* bin1, short unsigned int* bin2) {
	int count = 0;
	for (int i = 0; i < STATE_SIZE; ++i) 
		if (bin1[i] != bin2[i])
			count++;
	return count;
}

// ----------------------------------- TREE LOGIC FOR PATH FINDING -------------------------------------------

struct node { 
	int decimalState; 
	short unsigned int* binaryState;

	node* parent;
	vector<struct node*> children;
	int depth;

	void print() {
		printState(binaryState);
	}
	void printSolution() {
		vector<struct node*> solutionStates = vector<struct node*>();
		node* current = this;
		while(current != nullptr) {
			solutionStates.push_back(current);
			current = current->parent;
		}
		for (int i = solutionStates.size() - 1; i >= 0; --i) {
			solutionStates[i]->print();
		}
	}
}; 

int treeSize = 0;

node* makeNode(node* par, int value) {
	struct node* newNode = new struct node();
	if (par != nullptr) {
		par->children.push_back(newNode);
		newNode->depth = par->depth + 1;
	} else {
		newNode->depth = 0;
	}
	treeSize++;
	newNode->parent = par;
	newNode->decimalState = value;
	newNode->binaryState = intToBinary(value);
	newNode->children = vector<struct node*>();
	return newNode;
}

vector<node*> solutionLeafNodes = vector <node*>();
vector<node*> nonSolutionLeafNodes = vector <node*>();

bool visitedInTree(node* node) {
	return vistedSearchSpace[node->decimalState];
}

// search up the tree to see if another node matches the node
int numberOfVisitsInBranch(node* node) {
	int value = node->decimalState;
	int counter = 0;
	node = node->parent;
	while(node != nullptr) {
		if (node->decimalState == value) 
			counter++;
		node = node->parent;
	}
	return counter;
}

// ---------------------------------------- PROBLEM LOGIC ----------------------------------------------------

bool isFinalState(node* node) {
	// final state when everyone is on right side of river
	for (int i = 0; i < STATE_SIZE; ++i)
		if (node->binaryState[i] != 1)
			return false;
	return true;
}

bool isIllegalState(node* node) {
	// go through each element in state and count where people are at
	int counters [2] = {0}; // {0: m on right, 1: c on right}
	int i = 0;
	for (; i < GROUP_SIZE; ++i)
		if (node->binaryState[i] == 1)
			counters[0]++;
	for (; i < NUM_PEOPLE; ++i)
		if (node->binaryState[i] == 1)
			counters[1]++;

	// printState(node->binaryState);
	// cout << "Is left bank illegal? " << (GROUP_SIZE - counters[1] > GROUP_SIZE - counters[0] && GROUP_SIZE - counters[0] != 0) << ": " << GROUP_SIZE - counters[0] << " , " << GROUP_SIZE - counters[1] << endl;
	// cout << "Is right bank illegal? " << (counters[1] > counters[0]  && counters[0] != 0) << ": " << counters[0] << " , " << counters[1] << endl;
	
	// illegal if more cannibals than missionaries on left river
	if (GROUP_SIZE - counters[1] > GROUP_SIZE - counters[0] && (GROUP_SIZE - counters[0] != 0))
		return true;

	// illegal if more cannibals than missionaries on right river
	if (counters[1] > counters[0] && counters[0] != 0)
		return true;

	return false;
}

// prototype because recursive function needs to know this exists
void transferPeople(struct node* parent); 

void recursiveSearch(struct node* currentNode) {
	//vistedSearchSpace[currentNode->decimalState] = true;
	if (isFinalState(currentNode)) {
		// add solution with depth
		if (currentNode->depth < bestDepth) {
			bestDepth = currentNode->depth;
		}
		vistedSearchSpace[currentNode->decimalState] = false;
		solutionLeafNodes.push_back(currentNode);
		//if (currentNode->depth < 13)
		//cout << "Solution found at depth: " << currentNode->depth << endl;
	} else if (!isIllegalState(currentNode)) { // continue searching
		if (currentNode->depth + 1 < bestDepth) {
			transferPeople(currentNode);
		}
	} else {
		nonSolutionLeafNodes.push_back(currentNode);
	}
}

void transferPeople(struct node* currentNode) {
	// attempt as many boat passenger configurations as we can from the current state
	for (int j = 0; j < NUM_PEOPLE; ++j) {
		for (int p = 1; p <= BOAT_CAPACITY; ++p) {
			int passengers = 0;
			// create a new state
			short unsigned int* stateCopy = deepStateCopy(currentNode->binaryState);
			short unsigned int startingSideOfRiver = stateCopy[6];
			bool somethingChanged = false;
			stateCopy[6] = 1 - startingSideOfRiver; // set oposite river starting point
			for (int k = j; k < NUM_PEOPLE; ++k) {
				if (stateCopy[k] == startingSideOfRiver) {
					// transfer person to oposite side
					somethingChanged = true;
					stateCopy[k] = 1 - startingSideOfRiver;
					passengers++;
					if (passengers == p) 
						break;
				}
			}
			// sometimes nothing changes, ignore it
			if (somethingChanged) {
				node* child = makeNode(currentNode, binaryToInt(stateCopy));
				if (numberOfVisitsInBranch(child) < 1) {
					if (!vistedSearchSpace[child->decimalState]) {
						//vistedSearchSpace[child->decimalState] = true;
						recursiveSearch(child);
					}
				}
			}
		}
	}
}

int main()
{
	struct node* rootNode = makeNode(nullptr, 0);

	recursiveSearch(rootNode);

	// find best solution and print it
	int bestDepth = 9999999;
	struct node* bestSolution = nullptr;
	for (int i = 0; i < solutionLeafNodes.size(); i++) {
		if (solutionLeafNodes[i]->depth < bestDepth) {
			bestDepth = solutionLeafNodes[i]->depth;
			bestSolution = solutionLeafNodes[i];
		}
	}
	cout << "Searched paths: " << nonSolutionLeafNodes.size() + solutionLeafNodes.size() << endl;
	cout << "Best Solution: depth " << bestSolution->depth << endl;

	bestSolution->printSolution();




	return 0;
}

