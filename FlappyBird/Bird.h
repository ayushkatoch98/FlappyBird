#pragma once
#include <SFML/Graphics.hpp>
#include "PipeSpawner.h"
#include "Background.h"

class Bird {

private:
	bool jumpInput;
	bool isAlive;

	int windowHeight;
	int windowWidth;

	float speed;
	float jumpForce;


	sf::Vector2f gravity;
	sf::Vector2f velocity;

	sf::Texture texture;
	sf::Sprite bird;

public:

	Bird(int windowHeight, int windowWidth);

	void render(sf::Vector2f newVelocity, sf::RenderWindow& window);

	void update(float deltaTime, sf::RenderWindow& window);

	bool collisionFloor(sf::RectangleShape* background);
	bool collisionObstacles(PipeSpawner::Obstacle obstacle);

	void jump();

	void setIsAlive(bool isAlive) { this->isAlive = isAlive; }


private:

	sf::Texture loadTexture(std::string fileName);
};