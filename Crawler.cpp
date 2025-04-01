#include "Crawler.h";

using namespace std;

Crawler::Crawler(int id, Position position, Direction direction, int size, bool alive, list<Position> path) : id(id), position(position), direction(direction), alive(true), path(path) {};

// TODO Alive check for movement
// TODO IsBlocked check for movement

void Crawler::move() {
    switch (direction) {
        case Direction::North: position.y += 1; break;
        case Direction::East: position.x += 1; break;
        case Direction::South: position.y -= 1; break;
        case Direction::West: position.x -= 1; break;
    }

    // Adding our movement to our path list
    path.push_back(position);
}

bool Crawler::isWayBlocked() {
    // Assuming that 0 to 9 is our 10 grid places, meaning that they are the limit values
    // If no direction is at limit, then we return false
    switch (direction) {
        case Direction::North: return position.y == 0;
        case Direction::East: return position.x == 0;
        case Direction::South: return position.y == 9;
        case Direction::West: return position.x == 9;
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