#ifndef SLIDER_H
#define SLIDER_H
#include "Bug.h"

class Slider : public Bug {
public:
	// Constructor
	Slider(int id, Position position, Direction direction, int size, bool alive);

	// Deconstuctor
	~Slider() override;

	// Methods
	void move() override;
};

#endif //SLIDER_H