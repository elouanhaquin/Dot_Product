#pragma once
#include <Entity.h>
#include <fstream>
#include <string>

#define PI 3.141592f

class Enemy: public Entity 
{
private:
	sf::VertexArray triangle;
	sf::Clock clock;

	Vector2D<float> vec_pos_triangle_left;
	Vector2D<float> vec_pos_triangle_right;

	int length_detection, distance_traveled; 
	float angle_detection, speed;
	bool catched_mouse, inversed, saw_mouse;

public:
	Enemy(Vector2D<int> position);
	Enemy(const Enemy& enemy);
	~Enemy();


	void readConfigFile();
	void initView();
	void lookForPlayer(Entity& player);
	void move(Entity& player);
	void rotate(Entity& player);
	void setTriangleColor(std::string Color);

	sf::VertexArray getVertexArray() { return triangle; }
	
	bool mouseIsCatched() { return this->catched_mouse; }
	bool mouseIsSaw() { return this->saw_mouse; }
};

