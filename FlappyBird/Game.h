#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "PipeSpawner.h"
#include "Bird.h"

class Game {

private:

	int screenHeight;
	int screenWidth;
	

	Bird *bird;
	PipeSpawner *pipeSpawner;
	Background *sky;
	Background *floor;

	bool gameRunning;
	bool gameStarted;
	bool gameOver;
	bool jumpHold;

	sf::Texture logoTex;
	sf::Texture gameOverTex;
	sf::Texture digits[10];

	sf::RectangleShape gameOverLogo;
	sf::RectangleShape startLogo;
	sf::RectangleShape scores[3];

	sf::Texture loadTexture(std::string fileName);

	void renderScore(sf::RenderWindow& window, int score);
	void reset();
	void gameOverScreen(sf::RenderWindow& window);
	
public:

	Game(int screenHeight, int screenWidth);


	void startScreen(sf::RenderWindow& window);



	sf::RectangleShape createCenterLogo(sf::Texture& texture);

	void update(float deltaTime, sf::RenderWindow& window);
	void event(sf::Event event);

};