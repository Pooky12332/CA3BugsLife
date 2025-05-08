#include "Bug.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

// Constructor
Bug::Bug(int id, Position position, Direction direction, int size, bool alive) : id(id), position(position.x, position.y), direction(direction), size(size), alive(alive) {};

// Deconstructor
Bug::~Bug() {}

// Methods
bool Bug::isWayBlocked() {
	// Assuming that 0 to 9 is our 10 grid places, meaning that they are the limit values
	// If no direction is at limit, then we return false
	switch (direction) {
		case North: return position.y == 9;
		case East: return position.x == 9;
		case South: return position.y == 0;
		case West: return position.x == 0;
		default: return false;
	}
}

// Getters
int Bug::getId() const {
	return id;
}

Position Bug::getPosition() const {
	return position;
}

Direction Bug::getDirection() const {
	return direction;
}

int Bug::getSize() const {
	return size;
}

bool Bug::isAlive() const {
	return alive;
}

// We return a refrence to the path so subclasses can modify it
list<Position>& Bug::getPath() {
	return path;
}

// Setters
void Bug::setId(int id) {
	this -> id = id;
}

void Bug::setPosition(Position position) {
	this -> position = position;
}

void Bug::setDirection(Direction direction) {
	this -> direction = direction;
}

void Bug::setSize(int size) {
	this -> size = size;
}

void Bug::setAlive(bool alive) {
	this -> alive = alive;
}