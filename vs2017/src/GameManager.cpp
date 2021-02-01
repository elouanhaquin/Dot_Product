#include "GameManager.h"

GameManager::GameManager(): fps (60)
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "dot_product_program");
	player = new Player();
	
	mousePos = sf::Mouse::getPosition(*window);

	Enemy enemy = Enemy(mousePos);

	list_enemies.push_front(enemy);
	iterator_enemies = list_enemies.begin();

	
}


GameManager::~GameManager()
{
	delete window;
	delete player;

}

void GameManager::start()
{
	window->setFramerateLimit(fps);
	window->setMouseCursorVisible(false);

}

void GameManager::loop()
{

	sf::Clock clock; 
	int time_buffer = 0;

	while (window->isOpen())
	{
		sf::Event event;
	
	
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed )
				window->close();	
		
		}
		if (isAnyoneMakeCollision() || list_enemies.front().mouseIsCatched())  //can use mouse is catcehd only with fornt because it will detect if mouse is out of screen
			window->close();

		if (clock.getElapsedTime().asSeconds() > time_buffer + 1)
		{
			addingEnemyToList();
			time_buffer = clock.getElapsedTime().asSeconds();
		}
		moveListElements();
		moveEntities();
		renderFrame();
	}
}

void GameManager::end()
{
}

void GameManager::renderFrame()
{
	window->clear();
	window->draw(player->getRectangleShape());
	renderListElements();
	window->display();
}

void GameManager::moveEntities()
{
	mousePos = sf::Mouse::getPosition(*window);
	player->move(mousePos);
	moveListElements();
}


void GameManager::addingEnemyToList()
{
	Enemy enemy = Enemy(mousePos);
	list_enemies.push_back(enemy);
}

void GameManager::renderListElements()
{
	while (iterator_enemies != list_enemies.end())
	{
		window->draw(iterator_enemies->getVertexArray());
		window->draw(iterator_enemies->getRectangleShape());	
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
}

void GameManager::moveListElements()
{
	while (iterator_enemies != list_enemies.end())
	{
		iterator_enemies->move(*player);
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
}

bool GameManager::isAnyoneMakeCollision()
{
	while (iterator_enemies != list_enemies.end())
	{
		if (iterator_enemies->getRectangleShape().getGlobalBounds().intersects(player->getRectangleShape().getGlobalBounds()))
		{
			iterator_enemies = list_enemies.begin();		
			return true;
		}
		iterator_enemies->lookForPlayer(*player);
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
	return false;
}
