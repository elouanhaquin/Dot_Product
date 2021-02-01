#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>
#include <list>
#include <string>

#include <Player.h>
#include <enemy.h>



class GameManager
{
private:
	sf::RenderWindow* window;

	std::list<Enemy> list_enemies;
	std::list<Enemy>::iterator iterator_enemies;
	
	Player* player;
	Vector2D<int> mousePos;
	
	int fps;

public:
	GameManager();
	~GameManager();

	void start();
	void loop();
	void end();

	void renderFrame();

	//Movement functions
	void moveEntities();

	//List Functions
	void addingEnemyToList();
	void renderListElements();
	void moveListElements();
	bool isAnyoneMakeCollision();

};

