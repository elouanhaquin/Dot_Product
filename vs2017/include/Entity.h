#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Vector2D.h>
#include <cmath>

class Entity
{ 
protected:
	sf::RectangleShape sprite;
	float width, height;
	Vector2D<float>* vec;

public:
	Entity();
	~Entity();
	sf::RectangleShape& getRectangleShape() { return this->sprite; }

};

