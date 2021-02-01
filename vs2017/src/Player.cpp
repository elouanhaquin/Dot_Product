#include "Player.h"



Player::Player()
{
	sprite.setFillColor(sf::Color::Blue);


}


Player::~Player()
{
}

void Player::move(Vector2D<int> position)
{
	Vector2D<float> vec(false, position.X() - height / 2, position.Y() - width / 2, 0);
	sprite.setPosition(vec.toSfVector());

}
