#pragma once

#include <Entity.h>

class Player : public Entity
{


public:
	Player();
	~Player();

	void move(Vector2D<int> position);

};

