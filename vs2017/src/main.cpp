#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <GameManager.h>

int main()
{
	srand(time(NULL));
	GameManager game;
	game.start();
	game.loop();
	game.end();
	return 0;
}
