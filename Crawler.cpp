#include "Crawler.h"
#include "Bug.h"
#include <stdlib.h>
#include <cstdlib>

using namespace std;

// Constructor
Crawler::Crawler(int id, Position position, Direction direction, int size, bool alive) : Bug(id, position, direction, size, alive) {};

// Deconstructor
Crawler::~Crawler() {}

// Methods
void Crawler::move() {
	// Check if the bug is at an edge, if it is, pick a random direction
	while (isWayBlocked()) {
		Direction newDirection = static_cast<Direction> ((rand() % 4) + 1);
		setDirection(newDirection);
	}

	// Get the bugs current position
	Position pos = getPosition();

	// Make the movement
	switch (getDirection()) {
		case North: pos.y += 1; break;
		case East: pos.x += 1; break;
		case South: pos.y -= 1; break;
		case West: pos.x -= 1; break;
	}

	// Update the position and lists
	setPosition(pos);
	getPath().push_back(pos);
};