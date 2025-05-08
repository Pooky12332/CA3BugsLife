#include "Hopper.h"
#include "Bug.h"
#include <stdlib.h>
#include <cstdlib>

using namespace std;

// Constructor
Hopper::Hopper(int id, Position position, Direction direction, int size, bool alive, int hopLength) : Bug(id, position, direction, size, alive), hopLength(hopLength) {}

// Deconstructor
Hopper::~Hopper() {}

// Methods
void Hopper::move() {
	// Check if way is blocked, rand direction if true
	while (isWayBlocked()) {
		Direction newDirection = static_cast<Direction> ((rand() % 4) + 1);
		setDirection(newDirection);
	}

	// Get pos
	Position pos = getPosition();

	// Make the movement
	switch (getDirection()) {
		case North: pos.y = min(pos.y + hopLength, 9); break;
		case East: pos.x = min(pos.x + hopLength, 9); break;
		case South: pos.y = max(pos.y - hopLength, 0); break;
		case West: pos.x = max(pos.x - hopLength, 0); break;
	}

	// Update the position and lists
	setPosition(pos);
	getPath().push_back(pos);
}

int Hopper::getHopLength() const {
	return hopLength;
}

void Hopper::setHopLength(int hopLength) {
	this -> hopLength = hopLength;
}