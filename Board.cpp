#include "Board.h"
#include "Crawler.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <list>

Board board;
using namespace std;

// Constructors and deconstructors
Board::Board() {}
Board::~Board() {
    // Deleting each crawler and then clear all pointers
    for (Crawler* crawler : crawlers) {
        delete crawler;
    }
    crawlers.clear();
}

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
        cout << "Crawler{" << crawler->getId() << ", {" << crawler->getPosition().x << ", " << crawler->getPosition().y << "}, " << getDirecName(crawler->getDirection()) << ", " << crawler->getSize() << ", " << crawler->isAlive() << "}" << endl;
    }
}

// Util
// Display a single bugs info
void Board::displaySingle(Crawler* crawler) {
    cout << "Crawler{" << crawler->getId() << ", {" << crawler->getPosition().x << ", " << crawler->getPosition().y << "}, " << getDirecName(crawler->getDirection()) << ", " << crawler->getSize() << ", " << crawler->isAlive() << "}" << endl;
}

// Feature 3
// Find a bug in the vector that matches with the passed in ID
void Board::findById(int id) {
    // Making a crawler object
    Crawler* foundCrawler;

    // Checking the vector for a match, if it is, break from the loop
    for (Crawler* crawler : board.crawlers) {
        if (crawler->getId() == id) {
            foundCrawler = crawler;
            break;
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
    // Clearing the existing list in the instance
    board.currentlyOccupied.clear();

    // Currently, there is no way to identify what bug is in what position
    for (Crawler* crawler : board.crawlers) {
        crawler->move();
        board.currentlyOccupied.push_front(crawler->getPosition());
    }
}

// Feature 5
// View the position history of all bugs
// TODO Write this to a file on exit
void Board::displayAllPaths() {
    for (Crawler* crawler : board.crawlers) {
        cout << "Path for Crawler " << crawler->getId() << " facing " << getDirecName(crawler->getDirection()) << ": ";
        for (Position pos : crawler->getPath()) {
            cout << "(" << pos.x << ", " << pos.y << ") ";
        }
        cout << endl;
    }
}

// Feature 6
// Display the whole grid and what bugs occupy each square
// TODO Improve this function and add ID's to the bugs
void Board::displayAllCells() {
    // Iterate through each position
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            // Create a new position
            Position curPos = {x, y};
            bool found = false;

            // Check if the curPos is in the occupied list, if it, display it and break
            for (Position pos : board.currentlyOccupied) {
                if (pos.x == curPos.x && pos.y == curPos.y) {
                    cout << "(" << curPos.x << ", " << curPos.y << ") Crawler" << endl;
                    found = true;
                    break;
                }
            }

            // If the position wasnt found in the currentlyOccupied, then print a blank square
            if (!found) {
                cout << "(" << curPos.x << ", " << curPos.y << ") None" << endl;
            }
        }
    }
}

// Feature 8
void Board::simulate() {

}