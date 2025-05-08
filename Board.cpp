#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Util.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#include "Slider.h"

using namespace std;

// Creating our instance of board
Board board;

// Constructor
Board::Board() {
}

// Deconstructor
Board::~Board() {
	// Deleting each crawler and then clear all pointers
	for (Bug *bug: bugs) {
		delete bug;
	}
	bugs.clear();
}

// Feature 1
// Init the board, adding all the required bugs from the text file
void Board::init() {
	// Setting up our grid
	// 0 means no bug, otherwise it will contain the bug ID
	for (int x = 0; x < 10; ++x) {
		for (int y = 0; y < 10; ++y) {
			grid[x][y] = 0;
		}
	}

	// Creating an input stream from the text file
	// CLion working directory is different so for now, we can directly link to the file
	ifstream fin("bugs.txt");

	if (fin) {
		string line;

		while (getline(fin, line)) {
			// Creating the new variables for this new bug
			char type = line[0];
			int id = stoi(line.substr(2, 3));
			Position position = {stoi(line.substr(6, 1)), stoi(line.substr(8, 1))};
			Direction direction = static_cast<Direction>(stoi(line.substr(10, 1)));
			int size = stoi(line.substr(12, 1));
			bool alive = true;

			// Then add this bug to the bugs vector
			Bug *newBug = nullptr;

			switch (type) {
				case 'C': {
					newBug = new Crawler(id, position, direction, size, alive);
					break;
				} case 'H': {
					int hopLength = stoi(line.substr(14, 1));
					newBug = new Hopper(id, position, direction, size, alive, hopLength);
					break;
				} case 'S': {
					newBug = new Slider(id, position, direction, size, alive);
					break;
				}
			}

			// Add this bug to the needed places if its created
			if (newBug) {
				bugs.push_back(newBug);
				grid[position.x][position.y] = newBug->getId();
				newBug->getPath().push_back(position);
			}
		}
	} else {
		cout << "File does not exist" << endl;
	}
}

// Feature 2
// Display all bugs in the current instances vector
void Board::displayAll() {
	for (Bug *bug: bugs) {
		int id = bug->getId();
		Position position = bug->getPosition();
		string direction = getDirecName(bug->getDirection());
		int size = bug->getSize();
		string alive = bug->isAlive() ? "Alive" : "Dead";

		// Check for bug type
		if (dynamic_cast<Crawler *>(bug)) {
			cout << id << " Crawler" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
					alive << endl;
		} else if (dynamic_cast<Hopper *>(bug)) {
			Hopper *hopper = dynamic_cast<Hopper *>(bug);
			int hopLength = hopper->getHopLength();

			cout << id << " Hopper" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
					alive << " " << hopLength << endl;
		} else if (dynamic_cast<Slider *>(bug)) {
			cout << id << " Slider" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
					alive << endl;
		}
	}
}

// Util
// Display a single bugs info
void Board::displayBugInfo(Bug *bug) {
	// Creating the needed parameters
	int id = bug->getId();
	Position position = bug->getPosition();
	string direction = getDirecName(bug->getDirection());
	int size = bug->getSize();
	string alive = bug->isAlive() ? "Alive" : "Dead";

	// Check for bug type
	if (dynamic_cast<Crawler *>(bug)) {
		cout << id << " Crawler" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
				alive << endl;
	} else if (dynamic_cast<Hopper *>(bug)) {
		Hopper *hopper = dynamic_cast<Hopper *>(bug);
		int hopLength = hopper->getHopLength();

		cout << id << " Hopper" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
				alive << " " << hopLength << endl;
	} else if (dynamic_cast<Slider *>(bug)) {
		cout << id << " Slider" << " (" << position.x << ", " << position.y << ") " << size << " " << direction << " " <<
				alive << endl;
	}
}

// Util
// Return a bug info string
string Board::returnBugInfo(Bug *bug) {
	// Creating the needed parameters
	string id = to_string(bug->getId());
	string direction = to_string(bug->getDirection());
	string size = to_string(bug->getSize());
	string alive = to_string(bug->isAlive());

	// Check for bug type
	if (dynamic_cast<Crawler*>(bug)) {
		return "Crawler " + id + " [s:" + size + ", d:" + direction + ", a?:" + alive + "]";
	}

	if (dynamic_cast<Hopper*>(bug)) {
		// Create a pointer to that bug and use it to grab the hopper length
		Hopper *hopper = dynamic_cast<Hopper*>(bug);
		string hopLength = to_string(hopper->getHopLength());

		return "Hopper " + id + " [s:" + size + ", d:" + direction + ", a?:" + alive + ", hl:" + hopLength + "]";
	}

	if (dynamic_cast<Slider*>(bug)) {
		return "Slider " + id + " [s:" + size + ", d:" + direction + ", a?:" + alive + "]";
	}
}

// Feature 3
// Find a bug in the vector that matches with the passed in ID
void Board::findById(int id) {
	for (Bug *bug: bugs) {
		if (bug->getId() == id) {
			displayBugInfo(bug);
			break;
		}
	}
}

// Util
// Return a bug object by ID
Bug* Board::getById(int id) {
	for (Bug *bug: bugs) {
		if (bug->getId() == id) {
			return bug;
		}
	}
}


// Feature 4
// Tap the board to move all the bugs in their given directions
void Board::tap() {
	// Clear the grid of all bugs
	for (int x = 0; x < 10; ++x) {
		for (int y = 0; y < 10; ++y) {
			grid[x][y] = 0;
		}
	}

	// Create a position map, to track bugs
	map<Position, vector<Bug*>> positionMap;

	// Move all alive bugs and add to the map
	for (Bug* bug : bugs) {
		if (bug->isAlive()) {
			bug->move();
			Position pos = bug->getPosition();

			if (pos.x < 0 || pos.x >= 10 || pos.y < 0 || pos.y >= 10) {
				cout << "Bug " << bug->getId() << " has invalid position: (" << pos.x << ", " << pos.y << ")" << endl;
			}

			positionMap[pos].push_back(bug);
		}
	}

	// Check for 2 bugs or more on a cell
	for (auto& [pos, bugs] : positionMap) {
		// Ignore if only 1 bug on cell
		if (bugs.size() <= 1) {
			continue;
		}

		// Find the pointer for the biggest bug in the cell and save it to a pointer
		Bug* biggest = bugs[0];

		for (Bug* b : bugs) {
			if (b->getSize() > biggest->getSize()) biggest = b;
		}

		// Kill all smaller bugs and tally the sizes
		int gain = 0;

		for (Bug* bug : bugs) {
			if (bug != biggest) {
				gain += bug->getSize();
				bug->setAlive(false);
			}
		}

		// Update the biggest bug and the grid
		biggest->setSize(biggest->getSize() + gain);

		for (Bug* bug : bugs) {
			if (bug->isAlive()) {
				Position pos = bug->getPosition();
				grid[pos.y][pos.x] = bug->getId();
			}
		}
	}
}

// Feature 5
// View the position history of all bugs
void Board::displayAllPaths() {
	for (Bug *bug: bugs) {
		// Start the line
		cout << "Bug " << bug->getId() << " path: ";

		// Display each possition
		for (const Position &pos: bug->getPath()) {
			cout << "(" << pos.x << ", " << pos.y << ") ";
		}

		// Then end off the line
		cout << endl << endl;
	}
}

// Feature 6
// Write all of the paths to a file and the status
void Board::exit() {
	ofstream fout("paths.txt");

	// If we cant find the file
	if (!fout) {
		cout << "Failed to open paths.txt for writing." << endl;
		return;
	}

	for (Bug* bug : bugs) {
		// Get and store the bug type
		string type;

		if (dynamic_cast<Crawler*>(bug)) {
			type = "Crawler";
		} else if (dynamic_cast<Hopper*>(bug)) {
			type = "Hopper";
		} else if (dynamic_cast<Slider*>(bug)) {
			type = "Slider";
		}

		// Output the info on the bug
		fout << to_string(bug->getId()) << " " << type << " (" << to_string(bug->getPosition().x) << ", " << to_string(bug->getPosition().y) << ") " << to_string(bug->getSize()) << " " << getDirecName(bug->getDirection()) << " " << (bug->isAlive() ? "Alive" : "Dead") << endl;

		// Output the path that the bug followed
		fout << "Path: ";

		list<Position>& path = bug->getPath();
		for (Position& pos : path) {
			fout << "(" << pos.x << "," << pos.y << ") ";
		}
		fout << "\n\n";
	}
	fout.close();
}

// Feature 7
// Display the whole grid and what bugs occupy each square
void Board::displayAllCells() {
	for (int x = 0; x < 10; ++x) {
		for (int y = 0; y < 10; ++y) {
			if (grid[x][y] == 0) {
				cout << "(" << x << ", " << y << ") Empty" << endl;
			} else {
				cout << "(" << x << ", " << y << ") " << returnBugInfo(getById(grid[x][y])) << endl;
			}
		}
	}
}

// Feature 8
// Simlutate until there is one bug left one the board
void Board::simulate() {
	int round = 0;

	while (true) {
		int aliveCount = 0;
		// Reset the grid before checking positions
		for (int x = 0; x < 10; ++x) {
			for (int y = 0; y < 10; ++y) {
				grid[x][y] = 0;
			}
		}

		// Count the number of alive bugs and update the grid positions
		for (Bug* bug : bugs) {
			if (bug->isAlive()) {
				aliveCount++;
				Position pos = bug->getPosition();
				grid[pos.x][pos.y] = bug->getId();
			}
		}

		// If only one or fewer bugs are alive, end the simulation
		if (aliveCount <= 1) {
			break;
		}

		// Actually tap
		tap();
		round++;

		// Display results

		sleep(1);
	}
}

vector<Bug*>& Board::getBugs() {
	return bugs;
}