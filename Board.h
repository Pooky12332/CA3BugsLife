#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include "Hopper.h"
#include <vector>
#include <list>
#include <string>

using namespace std;

class Board {
private:
	vector<Bug*> bugs;
	int grid[10][10];

public:
	// Constructor
	Board();

	// Deconstructor
	~Board();

	// Methods
	void init(); // Feature 1
	void displayAll(); // Feature 2
	void displayBugInfo(Bug* bug); // Util
	string returnBugInfo(Bug* bug); // Util
	void findById(int id); // Feature 3
	Bug* getById(int id); // Util
	void tap(); // Feature 4
	void displayAllPaths(); // Feature 5
	void exit(); // Feature 6
	void displayAllCells(); // Feature 7
	void simulate(); // Feature 8

	// Getters
	vector<Bug*>& getBugs(); // Util
};

#endif //BOARD_H