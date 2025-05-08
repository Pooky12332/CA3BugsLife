#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

using namespace std;

class Hopper : public Bug {
private:
	int hopLength;

public:
	// Constructor
	Hopper(int id, Position position, Direction direction, int size, bool alive, int hopLength);

	// Deconstructor
	~Hopper() override;

	// Methods
	void move() override;

	int getHopLength() const;
	void setHopLength(int hopLength);
};

#endif //HOPPER_H