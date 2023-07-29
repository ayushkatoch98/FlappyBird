#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <queue>

class PipeSpawner {

public:
	struct Obstacle {
		bool isActive;
		int index;

		sf::Vector2f pos;
		sf::Sprite top;
		sf::Sprite bottom;
		sf::RectangleShape scoreWall;




		Obstacle() {
			pos = { 0.f, 0.f };
			isActive = false;
			index = 0;
		}

		void setPositionX(float x) {
			this->top.setPosition(x, this->top.getPosition().y);
			this->bottom.setPosition(x, this->bottom.getPosition().y);
			//this->scoreWall.setPosition(x, this->scoreWall.getPosition().y);
		}

		void setTexture(sf::Texture& texture) {
			this->top.setTexture(texture);
			this->bottom.setTexture(texture);
		}

		void setTexture(sf::Texture topPipe, sf::Texture bottomPipe) {
			this->top.setTexture(topPipe);
			this->bottom.setTexture(bottomPipe);
		}

	};

private:

	

	int windowHeight;
	int windowWidth;
	
	int score;
	int activeObstacleIndex;

	float frequency; // in seconds
	float obstacleSpeed;

	bool pause;

	std::random_device rd;

	sf::Vector2f velocity;

	std::string fileName;

	sf::Texture texture;

	std::vector<Obstacle> obstacles;

	sf::RectangleShape invisibleWall;

public:
	PipeSpawner(int windowHeight, int windowWidth);
	void update(float deltaTime, sf::RenderWindow& window);

	Obstacle getActiveObstacle() { return this->obstacles[this->activeObstacleIndex]; }

	void setPause(bool pause) { this->pause = pause; }

	int getScore() { return this->score; }

private:
	sf::Texture loadTexture(std::string fileName);
	float generateRandomNumber(float min, float max);

	void loadObstacles();

	void render(sf::RenderWindow& window, Obstacle obstacle);



};
