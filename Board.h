#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <list>

using namespace std;

class Board {
private:
    vector<Crawler*> crawlers;
    list<Position> currentlyOccupied;

public:
    // Constructor
    Board();

    // Deconstructor
    ~Board();

    // Methods
    void init(); // Feature 1
    void displayAll(); // Feature 2
    void displaySingle(Crawler* crawler); // Util
    void findById(int id); // Feature 3
    void tap(); // Feature 4
    void displayAllPaths(); // Feature 5
    void displayAllCells(); // Feature 6
    void simulate(); // Feature 8
};

#endif //BOARD_H