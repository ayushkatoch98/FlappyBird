#include "PipeSpawner.h"
#include <iostream>


#define OBSTACLE_FREQUENCY 1.f
#define PRE_LOAD_OBSTACLE 4
#define OBSTACLE_MAX_GAP 300.f
#define OBSTACLE_MIN_GAP 200.f
#define OBSTACLE_SPEED 100.f;
#define PIPE_SCALE 1.2f

#define PIPE_BOTTOM_Y_MIN_OFFSET -100.f
#define PIPE_BOTTOM_Y_MAX_OFFSET 50.f

#define PIPE_TOP_Y_MIN_OFFSET -150.f
#define PIPE_TOP_Y_MAX_OFFSET -100.f




float PipeSpawner::generateRandomNumber(float min, float max) {

	std::mt19937 rng(this->rd());    // Random-number engine used (Mersenne-Twister in this case)
	
	std::uniform_int_distribution<int> uni((int) min, (int) max); // Guaranteed unbiased

	return (float) uni(rng);
}

PipeSpawner::PipeSpawner(int windowHeight, int windowWidth) {
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;

	this->score = 1;
	this->frequency = OBSTACLE_FREQUENCY;
	this->fileName = "./Images/pipe-green.png";

	this->obstacles.reserve(PRE_LOAD_OBSTACLE);

	this->texture = this->loadTexture(this->fileName);

	this->velocity = sf::Vector2f(0.f, 0.f);

	this->obstacleSpeed = OBSTACLE_SPEED;

	this->activeObstacleIndex = 0;

	this->loadObstacles();

	this->invisibleWall = sf::RectangleShape();
	this->invisibleWall.setPosition(sf::Vector2f(0.f, 0.f));
	this->invisibleWall.setSize(sf::Vector2f(40.f, this->windowHeight));
	this->invisibleWall.setFillColor(sf::Color(0, 255, 0, 122));
}

sf::Texture PipeSpawner::loadTexture(std::string fileName) {
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Counldn't load texture" << std::endl;
		exit(1);
	}
	return texture;
}

sf::Vector2f getSpriteSize(sf::Sprite sprite) {
	sf::Vector2u textSize = sprite.getTexture()->getSize();
	sf::Vector2f spriteScale = sprite.getScale();
	sf::Vector2f size;

	size.x = textSize.x * spriteScale.x;
	size.y = textSize.y * spriteScale.y;

	return size;
	
}

void PipeSpawner::loadObstacles() {

	float initialX = this->windowWidth;
	float h;
	float w;

	for (int i = 0; i < PRE_LOAD_OBSTACLE; i++) {
		Obstacle obstacle;
		obstacle.index = i;
		if (i == 0) {
			obstacle.isActive = true;
			this->activeObstacleIndex = 0;
		}
		// setting textures
		obstacle.setTexture(this->texture);

	

		// bottom
		obstacle.bottom.setScale(sf::Vector2f(PIPE_SCALE, PIPE_SCALE));
		
		
		h = obstacle.bottom.getGlobalBounds().height;
		w = obstacle.bottom.getGlobalBounds().width;

		obstacle.bottom.setPosition(sf::Vector2f(initialX, 
			this->windowHeight - h + generateRandomNumber(PIPE_BOTTOM_Y_MIN_OFFSET, PIPE_BOTTOM_Y_MAX_OFFSET)));

		// top

		h = obstacle.top.getGlobalBounds().height;
		w = obstacle.top.getGlobalBounds().width;

		obstacle.top.setOrigin(sf::Vector2f(w, h));

		obstacle.top.setScale(sf::Vector2f(PIPE_SCALE, PIPE_SCALE));

		obstacle.top.setPosition(sf::Vector2f(initialX, 
			generateRandomNumber(PIPE_TOP_Y_MIN_OFFSET, PIPE_TOP_Y_MAX_OFFSET)));
		obstacle.top.rotate(180.f);


		obstacle.scoreWall.setPosition(sf::Vector2f(initialX - 2.0f, 0.f));
		obstacle.scoreWall.setSize(sf::Vector2f(w + 10.0f, this->windowHeight));
		obstacle.scoreWall.setFillColor(sf::Color(255, 0, 0, 128));
		
		
		
		// appending
		this->obstacles.push_back(obstacle);
			
		initialX += generateRandomNumber(OBSTACLE_MAX_GAP, OBSTACLE_MAX_GAP);

	}

}

void PipeSpawner::render(sf::RenderWindow& window, Obstacle obstacle) {

	window.draw(obstacle.top);
	window.draw(obstacle.bottom);
	window.draw(obstacle.scoreWall);

}



void PipeSpawner::update(float deltaTime, sf::RenderWindow& window) {

	

	float newX;

	if (this->obstacles[this->activeObstacleIndex].top.getGlobalBounds().intersects(this->invisibleWall.getGlobalBounds())) {
		if (this->obstacles[this->activeObstacleIndex].isActive) {
			this->score++;
		}
		this->obstacles[this->activeObstacleIndex].isActive = false;
		
		this->activeObstacleIndex++;
		if (this->activeObstacleIndex >= PRE_LOAD_OBSTACLE) {
			this->activeObstacleIndex = 0;
		}

		this->obstacles[this->activeObstacleIndex].isActive = true;
	}



	for (int i = 0; i < this->obstacles.size(); i++) {

		if (this->pause) {
			this->render(window, this->obstacles[i]);
			continue;
		}

		newX = this->obstacles[i].bottom.getPosition().x - this->obstacleSpeed * deltaTime;
		
		if (newX + this->obstacles[i].bottom.getGlobalBounds().width <= 0.f) {

			newX = this->obstacles.size() * generateRandomNumber(OBSTACLE_MAX_GAP, OBSTACLE_MAX_GAP);

		}

		
		this->obstacles[i].setPositionX(newX);

		this->render(window, this->obstacles[i]);
		
	}

}


