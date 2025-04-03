#include "Crawler.h"

#include <stdlib.h>

using namespace std;

// Constructor
Crawler::Crawler(int id, Position position, Direction direction, int size, bool alive, list<Position> path) : id(id), position(position), direction(direction), size(size), alive(alive), path(path) {};

// Methods
void Crawler::move() {
    // Check if the bug is at an edge
    while (isWayBlocked()) {
        direction = static_cast<Direction> ((rand() % 4) + 1);
    }

    // Make our movement
    switch (direction) {
        case North: position.y += 1; break;
        case East: position.x += 1; break;
        case South: position.y -= 1; break;
        case West: position.x -= 1; break;
    }

    // Adding our movement to our path list
    path.push_back(position);
}

bool Crawler::isWayBlocked() {
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
int Crawler::getId() const {
    return id;
};

Position Crawler::getPosition() const {
    return position;
};

Direction Crawler::getDirection() const {
    return direction;
}

int Crawler::getSize() const {
    return size;
}

bool Crawler::isAlive() const {
    return alive;
}

list<Position> Crawler::getPath() const {
    return path;
}

// Setters
void Crawler::setId(int id) {
    this -> id = id;
}

void Crawler::setPosition(Position position) {
    this -> position = position;
}

void Crawler::setDirection(Direction direction) {
    this -> direction = direction;
}

void Crawler::setSize(int size) {
    this -> size = size;
}

void Crawler::setAlive(bool alive) {
    this -> alive = alive;
}