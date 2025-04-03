#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>

class Board {
private:
    std::vector<Crawler*> crawlers;

public:
    // Constructor
    Board();

    // Deconstructor
    ~Board();

    // Methods
    void init(); // Feature 1
    void displayAll(); // Feature 2
    void findById(); // Feature 3
    void tap(); // Feature 4
};

#endif //BOARD_H