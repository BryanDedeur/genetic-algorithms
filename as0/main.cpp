/*
	Author: Bryan Dedeurwaerder
	Date: 9/5/2021
	Project: CS 790K Genetic Algorithms As0
	Professor: Dr. Sushil Louis
*/

#include <iostream>
#include <math.h>

using namespace std;

const int SEARCH_SPACE_SIZE = 729; // 3^6 = 729 possible states
const int STATE_SIZE = 6; // 6 elements per state, 3 missionaries, 3 cannibals
const int MAX_LOCATIONS = 3; // 3 locations, left river, boat, right river

bool isFinalState(short unsigned int state[]) {
	// final state when everyone is on right side of river
	for (int i = 0; i < 6; ++i)
		if (state[i] != 2)
			return false;
	return true;
}

bool isIllegalState(short unsigned int state[]) {
	// go through each element in state and count where people are at
	int counters [STATE_SIZE] = {0}; // {0: m on left, 1: m on boat, 2: m on right, 3: c on left, 4: c on boat, 5: c on right}
	for (int i = 0; i < STATE_SIZE; ++i)
		counters[state[i]]++;

	// illegal if too many people on boat
	if (counters[1] + counters[4] > 2) 
		return true;
	
	// illegal if more cannibals than missionaries on left river
	if (counters[3] > counters[0])
		return true;

	// illegal if more cannibals than missionaries on right river
	if (counters[5] > counters[2])
		return true;

	// illegal if cannibals row alone?

	return false;
}

void recursiveSearch(short unsigned int searchSpace[][STATE_SIZE], int depth, int state, int element) {
	if (state < SEARCH_SPACE_SIZE) {
		if (isFinalState(searchSpace[state])) {
			// add solution with depth
		} else if (!isIllegalState(searchSpace[state])) { // continue searching
			depth++;
			// copy previous state
			if (state != 0) {
				for (int i = 0; i < STATE_SIZE; ++i) {
					searchSpace[state][i] = searchSpace[state - 1][i];
				}
			}

			if (searchSpace[state][element] >= MAX_LOCATIONS - 1) {
				element++;
			}

			if (element > STATE_SIZE) {
				return;
			}

			searchSpace[state][element]++;
			state += searchSpace[state][element] * pow(MAX_LOCATIONS, element); 
			recursiveSearch(searchSpace, depth, state, element);

			for (int i = element + 1; i < STATE_SIZE; i++) {
				recursiveSearch(searchSpace, depth, state, i);
			}

		}
	}

}

void printSearchSpace(short unsigned int searchSpace[][STATE_SIZE]) {
	for (int i = 0; i < SEARCH_SPACE_SIZE; ++i) {
		cout << i << ": ";
		for (int j = 0; j < STATE_SIZE; ++j) {
			cout << searchSpace[i][j];
		}
		cout << endl;
	}
}

int main()
{
	// Initialize the search space
	short unsigned int searchSpace [SEARCH_SPACE_SIZE][STATE_SIZE] = {0}; // 6 elements per state
	// // int l = 0;
	// // for (int i = 0; i < STATE_SIZE; ++i) {
	// // 	for (int j = i; j < STATE_SIZE; ++j) {
	// // 		for (int k = 0; k < MAX_LOCATIONS; ++k) {
	// // 			searchSpace[i * j][j] = k;
	// // 		}
	// // 	}
	// // }

	// int l = 0;
	// int j = 0;
	// for (int i = 0; i < SEARCH_SPACE_SIZE; ++i) {
	// 	// copy previous state
	// 	if (i > 0) {
	// 		for (int k = 0; k < STATE_SIZE; ++k) {
	// 			searchSpace[i][k] = searchSpace[i][k - 1];
	// 		}
	// 	}

	// 	searchSpace[i][l] = j;

	// 	l++;
	// 	if (l >= STATE_SIZE) 
	// 		l = 0;
		
	// 	j++;
	// 	if (j >= MAX_LOCATIONS) 
	// 		j = 0;
		
	// }

	recursiveSearch(searchSpace, 0, 0, 0);
	printSearchSpace(searchSpace);

	return 0;
}

