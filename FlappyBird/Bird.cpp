#include <iostream>
#include "Bird.h"

#define BIRD_POS_X 100.f
#define BIRD_SCALE 1.2f
#define BIRD_SPEED 5.0f
#define BIRD_JUMP_FORCE -100.0f

#define GRAVITY 9.81f


Bird::Bird(int windowHeight, int windowWidth) {

	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;

	this->isAlive = true;

	this->speed = BIRD_SPEED;
	this->jumpForce = BIRD_JUMP_FORCE;
	this->gravity = sf::Vector2f(0.f, GRAVITY);
	this->velocity = sf::Vector2f(0.f, 0.f);

	this->jumpInput = false;

	this->texture = this->loadTexture("./Images/bluebird-midflap.png");
	
	this->bird = sf::Sprite();
	this->bird.setTexture(this->texture);
	this->bird.setOrigin(0.f, this->bird.getGlobalBounds().height / 2);
	this->bird.setScale(sf::Vector2f(BIRD_SCALE, BIRD_SCALE));
	this->bird.setPosition(sf::Vector2f(BIRD_POS_X, 30.f));
	

	
}

sf::Texture Bird::loadTexture(std::string fileName) {
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)){
		std::cout << "Counldn't load texture" << std::endl;
		exit(1);
	}
	return texture;
}

void Bird::render(sf::Vector2f newVelocity, sf::RenderWindow &window) {
	
	window.draw(this->bird);
}

void Bird::update(float deltaTime, sf::RenderWindow &window) {

	if (!this->isAlive) {
		this->render(this->velocity, window);
		return;
	}
	
	float r = this->bird.getRotation();

	// going up
	if (this->jumpInput) {
		this->jumpInput = false;
		this->velocity.y = deltaTime * this->speed * this->jumpForce;
		this->velocity.x = 0.f;
		this->bird.move(this->velocity);

		if (!(r >= 270 && r <= 360))
			this->bird.rotate(-90.0f * deltaTime * this->speed);
		
	}
	// falling
	else {
		this->velocity += this->gravity * deltaTime * this->speed;
		this->bird.move(this->velocity);

			this->bird.rotate(5.0f * deltaTime * this->speed);
	
	}


	this->render(this->velocity, window);

}

bool Bird::collisionFloor(sf::RectangleShape *background) {
	sf::FloatRect birdBounds = this->bird.getGlobalBounds();

	for (int i = 0; i < 2; i++) {
		if (birdBounds.intersects(background[i].getGlobalBounds()))
			return true;

	}

	return false;
}


bool Bird::collisionObstacles(PipeSpawner::Obstacle obstacle) {

	sf::FloatRect birdBounds = this->bird.getGlobalBounds();
		
	if (birdBounds.intersects(obstacle.top.getGlobalBounds())
		|| birdBounds.intersects(obstacle.bottom.getGlobalBounds())) {

		return true;
	}	

	return false;

}


void Bird::jump() {

	this->jumpInput = true;

}

