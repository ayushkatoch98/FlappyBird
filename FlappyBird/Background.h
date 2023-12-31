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

	sf::Sprite bg[3];

public:

	Background(int windowHeight, int windowWidth, std::string filename, float screenPercent, bool positionTop);
	sf::Texture loadTexture(std::string fileName);
	void update(float deltaTime, sf::RenderWindow& window);

	sf::Sprite* getBg() { return this->bg; }

	void setPause(bool pause) { this->pause = pause; }

private:

	void render(sf::RenderWindow& window);
};