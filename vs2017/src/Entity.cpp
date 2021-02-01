#include "Entity.h"



Entity::Entity(): width(50.0f), height(50.0f)
{
	vec = new Vector2D<float>(false, width, height, 0.0f);
	sprite.setSize(vec->toSfVector());
}


Entity::~Entity()
{
}
