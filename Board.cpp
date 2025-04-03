#include "Board.h"
#include "Crawler.h"
#include <iostream>
#include <fstream>
#include <list>

Board board;
using namespace std;

Board::Board() {}

Board::~Board() {}

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

void Board::displayAll() {
    for (Crawler* crawler : board.crawlers) {
        cout << "Crawler{" << crawler->getId() << ", {" << crawler->getPosition().x << ", " << crawler->getPosition().y << "}, " << crawler->getDirection() << ", " << crawler->getSize() << ", " << crawler->isAlive() << "}" << endl;
    }
}

