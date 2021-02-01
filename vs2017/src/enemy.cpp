#include <Enemy.h>


Enemy::Enemy(Vector2D<int> position_mouse): distance_traveled(0), inversed(false), speed (0.002f)
{
	readConfigFile();
	float x = rand() % 1280;
	float y = rand() % 720;
	catched_mouse = false;

	while (x - position_mouse.X() < 400 && x - position_mouse.X() > -400)
		x = rand() % 1280;
	
		 
	while (y - position_mouse.Y() < 200 && y - position_mouse.Y() > -200) 
		y = rand() % 720;
		
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(x, y);
	sprite.setOrigin(sprite.getSize().x/2, sprite.getSize().y / 2);
	triangle = sf::VertexArray(sf::Triangles, 3);

}

Enemy::Enemy(const Enemy & other)
{	

	float x = rand() % 1280;
	float y = rand() % 720;
	speed = 0.002f;
	distance_traveled = 0;
	inversed = false;
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(x, y);
	catched_mouse = false;
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
	triangle = sf::VertexArray(sf::Triangles, 3);
	initView();
	
}


Enemy::~Enemy()
{
}


void Enemy::readConfigFile()
{	
		std::fstream fichier("../assets/config.ini", std::ios::in | std::ios::out );  

		if (fichier)
		{			
			std::string word1, word2, word3;
			fichier >> word1 >> word2 >> length_detection >> word3;
			fichier >> word1 >> word2 >> angle_detection >> word3;
			fichier.close();
		}
		else
			std::cout << "FILE DOESN'T EXIST" << std::endl;
}

void Enemy::initView()
{
	readConfigFile();

	vec_pos_triangle_left = Vector2D<float>(true, length_detection, angle_detection/2 , 0);
	vec_pos_triangle_right = Vector2D<float>(true, length_detection, -angle_detection/2 , 0);

	vec_pos_triangle_left.set_X(vec_pos_triangle_left.X() + sprite.getPosition().x);
	vec_pos_triangle_left.set_Y(vec_pos_triangle_left.Y() + sprite.getPosition().y);

	vec_pos_triangle_right.set_X(vec_pos_triangle_right.X() + sprite.getPosition().x);
	vec_pos_triangle_right.set_Y(vec_pos_triangle_right.Y() + sprite.getPosition().y);

	triangle[0].position = sprite.getPosition();
	triangle[1].position = vec_pos_triangle_left.toSfVector();
	triangle[2].position = vec_pos_triangle_right.toSfVector();

}

void Enemy::lookForPlayer(Entity & player)
{
	Vector2D<float> posPlayer(false, player.getRectangleShape().getPosition().x+25- sprite.getPosition().x, player.getRectangleShape().getPosition().y + 25 - sprite.getPosition().y, 0);
	Vector2D<float> posTriangleCornerLeft(false, triangle[1].position.x - sprite.getPosition().x, triangle[1].position.y - sprite.getPosition().y, 0);
	Vector2D<float> posTriangleCornerRight(false, triangle[2].position.x - sprite.getPosition().x, triangle[2].position.y - sprite.getPosition().y, 0);


	if(posPlayer.angle_With(posTriangleCornerLeft) < angle_detection && posPlayer.angle_With(posTriangleCornerRight) < angle_detection && posPlayer.X() < length_detection )
	{
		setTriangleColor("Red");
		saw_mouse = true;
	}
	else	
	{
		setTriangleColor("White");
		saw_mouse = false;
	}


}

void Enemy::move(Entity& player)
{
	if(saw_mouse)
	{
		Vector2D<float> posTarget(false, player.getRectangleShape().getPosition().x - sprite.getPosition().x, player.getRectangleShape().getPosition().y - sprite.getPosition().y, 0);
		sprite.move(posTarget.X() * speed, posTarget.Y() * speed);
		rotate(player);
	}

	
}

void Enemy::rotate(Entity & player)
{

	Vector2D<float> posPlayer(false, player.getRectangleShape().getPosition().x , player.getRectangleShape().getPosition().y , 0);
	Vector2D<float> pos = sprite.getPosition();
	float angle = pos.angle_Rotate(posPlayer) -90;
	
		
	sprite.setRotation(angle);

	vec_pos_triangle_left = Vector2D<float>(true, length_detection, angle_detection / 2 + angle , 0);
	vec_pos_triangle_right = Vector2D<float>(true, length_detection, -angle_detection / 2 + angle, 0);

	vec_pos_triangle_left.set_X(vec_pos_triangle_left.X() + sprite.getPosition().x);
	vec_pos_triangle_left.set_Y(vec_pos_triangle_left.Y() + sprite.getPosition().y);

	vec_pos_triangle_right.set_X(vec_pos_triangle_right.X() + sprite.getPosition().x);
	vec_pos_triangle_right.set_Y(vec_pos_triangle_right.Y() + sprite.getPosition().y);

	triangle[0].position = sprite.getPosition();
	triangle[1].position = vec_pos_triangle_left.toSfVector();
	triangle[2].position = vec_pos_triangle_right.toSfVector();


}


void Enemy::setTriangleColor(std::string Color)
{
	if (Color == "Red") 
	{
		triangle[0].color = sf::Color(255, 0, 0, 120);
		triangle[1].color = sf::Color(255, 0, 0, 0);
		triangle[2].color = sf::Color(255, 0, 0, 0);
	}
	if (Color == "White")
	{
		triangle[0].color = sf::Color(255, 255, 255, 120);
		triangle[1].color = sf::Color(255, 255, 255, 0);
		triangle[2].color = sf::Color(255, 255, 255, 0);
	}
}
