#include "Slider.h"
#include <stdlib.h>
#include <cstdlib>

using namespace std;

// Constructor
Slider::Slider(int id, Position position, Direction direction, int size, bool alive) : Bug(id, position, direction, size, alive) {}

// Deconstructor
Slider::~Slider() {}

// Methods
void Slider::move() {
	// Always set a new direction at random
	Direction newDirection = static_cast<Direction> ((rand() % 4) + 1);
	setDirection(newDirection);

	// Check to see if thats blocked and if it is, then set a new direction
	while (isWayBlocked()) {
		newDirection = static_cast<Direction> ((rand() % 4) + 1);
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
}