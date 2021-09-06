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

const int STATE_SIZE = 7; 			// 7 elements per state, 3 missionaries, 3 cannibals
const int SEARCH_SPACE_SIZE = 128; 	// 2^7 = 128 possible states
const int MAX_LOCATIONS = 2; 		// 2 locations, left river, right river
const int GROUP_SIZE = 3; 			// 3 missionaries or 3 cannibals
const int NUM_PEOPLE = 6;
const int BOAT_CAPACITY = 2; 		// 2 seats
const short unsigned int RIGHT_RIVER = 1;
const short unsigned int LEFT_RIVER = 0;

vector<vector<int>> cachedPaths = vector<vector<int>>();
bool vistedSearchSpace [SEARCH_SPACE_SIZE] = {0};


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

void cachePath(short unsigned int state[], int solutionID) {
	int value = binaryToInt(state);
	if (solutionID >= cachedPaths.size()) {
		vector<int> newPath = vector<int>();
		cachedPaths.push_back(newPath);
	}
	cachedPaths[solutionID].push_back(value);
}

bool visited(short unsigned int state[]) {
	int value = binaryToInt(state);
	if (vistedSearchSpace[value])
		return true;
	else
		vistedSearchSpace[value] = true;
	return false;
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

// ------------------------------------------------------------------------------------------------------------

bool isFinalState(short unsigned int state[]) {
	// final state when everyone is on right side of river
	for (int i = 0; i < STATE_SIZE; ++i)
		if (state[i] != 1)
			return false;
	return true;
}

bool isIllegalState(short unsigned int state[]) {
	// go through each element in state and count where people are at
	int counters [2] = {0}; // {0: m on right, 1: c on right}
	int i = 0;
	for (; i < GROUP_SIZE; ++i)
		counters[0]++;
	for (; i < NUM_PEOPLE; ++i)
		counters[1]++;
	
	// illegal if more cannibals than missionaries on left river
	if (GROUP_SIZE - counters[1] > GROUP_SIZE - counters[0])
		return true;

	// illegal if more cannibals than missionaries on right river
	if (counters[1] > counters[0])
		return true;

	return false;
}

// prototype because recursive function needs to know this exists
void transferPeople(short unsigned int state[], int depth); 

int recursiveSearch(short unsigned int state[], int depth) {
	if (!visited(state)) {
		if (isFinalState(state)) {
			// add solution with depth
			cout << "Solution found at depth: " << depth << endl;
			cachePath(state, cachedPaths.size());
			return cachedPaths.size() - 1;
		} else if (!isIllegalState(state)) { // continue searching
			transferPeople(state, depth + 1);
		}
	}
	return -1;
}

void transferPeople(short unsigned int previousState[], int depth) {
	// attempt as many boat passenger configurations as we can from the current state
	for (int j = 0; j < NUM_PEOPLE; ++j) {
		for (int p = 1; p <= BOAT_CAPACITY; ++p) {
			int passengers = 0;
			// create a new state
			short unsigned int* stateCopy = deepStateCopy(previousState);
			short unsigned int startingSideOfRiver = previousState[6];
			bool somethingChanged = false;
			stateCopy[6] = 1 - startingSideOfRiver; // set oposite river starting point
			for (int k = j; k < NUM_PEOPLE; ++k) {
				if (previousState[k] == startingSideOfRiver) {
					// transfer person to oposite side
					somethingChanged = true;
					stateCopy[k] = 1 - startingSideOfRiver;
					passengers++;
					if (passengers == p) 
						break;
				}
			}
			if (somethingChanged) {
				// send state to recursive search
				int solutionId = recursiveSearch(stateCopy, depth);
				if (solutionId > -1) {
					cachePath(stateCopy, solutionId);
				}
			}
		}
	}
}

int main()
{
	// Initialize the search space
	short unsigned int startState[STATE_SIZE] = {0,0,0,0,0,0,0}; // 3 missionaries on left , 3 cannibals on left, boat on left

	recursiveSearch(startState, 0);
	//transferPeople(startState, 0);
	cout << cachedPaths[0].size() << endl;
	//printSearchSpace(searchSpace);

	return 0;
}

