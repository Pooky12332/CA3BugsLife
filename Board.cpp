#include "Board.h"
#include "Crawler.h"
#include <iostream>
#include <fstream>
#include <list>

Board board;
using namespace std;

// Util classes
void displaySingle(Crawler* crawler);

// Constructors and deconstructors
Board::Board() {}
Board::~Board() {}

// Feature 1
// Init the board, adding all the required bugs from the text file
void Board::init() {
    // Creating an input stream from the text file
    // CLion working directory is different so for now, we can directly link to the file
    ifstream fin("O:/College/YearTwo/Cpp/Projects/CA3BugsLife/crawler-bugs.txt");

    if (fin) {
        string line;

        while (getline(fin, line)) {
            // Creating the new crawler with its required arguments
            Position startPos = {stoi(line.substr(6, 1)), stoi(line.substr(8, 1))};
            list<Position> path = {startPos};
            Crawler* curCrawler = new Crawler(stoi(line.substr(2, 3)), startPos, Direction(stoi(line.substr(10, 1))), stoi(line.substr(12, 1)), true, path);

            // Then we add this bug to the end of the "crawlers" vector
            board.crawlers.push_back(curCrawler);
        }
    } else {
        cout << "File does not exist" << endl;
    }
}

// Feature 2
// Display all bugs in the current instances vector
void Board::displayAll() {
    for (Crawler* crawler : board.crawlers) {
        cout << "Crawler{" << crawler->getId() << ", {" << crawler->getPosition().x << ", " << crawler->getPosition().y << "}, " << crawler->getDirection() << ", " << crawler->getSize() << ", " << crawler->isAlive() << "}" << endl;
    }
}

// Feature 3
// Find a bug in the vector that matches with the passed in ID
void Board::findById(int id) {
    // Making a crawler object
    Crawler* foundCrawler;

    // Checking the vector for a match
    for (Crawler* crawler : board.crawlers) {
        if (crawler->getId() == id) {
            foundCrawler = crawler;
        }
    }

    // If a match is found, display it
    if (foundCrawler != nullptr) {
        displaySingle(foundCrawler);
    }
}

// Feature 4
// Tap the board to move all the bugs in their given directions
void Board::tap() {
    for (Crawler* crawler : board.crawlers) {
        crawler -> move();
    }
}

// Util Functions
void displaySingle(Crawler* crawler) {
    cout << "Crawler{" << crawler->getId() << ", {" << crawler->getPosition().x << ", " << crawler->getPosition().y << "}, " << crawler->getDirection() << ", " << crawler->getSize() << ", " << crawler->isAlive() << "}" << endl;
}