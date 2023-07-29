#pragma once
#include <SFML/Graphics.hpp>


class Background {

private:

	int windowHeight;
	int windowWidth;

	bool pause;

	float speed;

	int activeBg;
	sf::Texture bgTex;

	sf::RectangleShape bg[2];

public:

	Background(int windowHeight, int windowWidth, std::string filename, float screenPercent, bool positionTop);
	sf::Texture loadTexture(std::string fileName);
	void update(float deltaTime, sf::RenderWindow& window);

	sf::RectangleShape* getBg() { return this->bg; }

	void setPause(bool pause) { this->pause = pause; }

private:

	void render(sf::RenderWindow& window);
};