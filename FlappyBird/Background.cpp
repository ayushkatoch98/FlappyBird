#include "Background.h"
#include <iostream>



#define BG_SPEED 100.f;

Background::Background(int windowHeight, int windowWidth, std::string filename, float screenPercent, bool positionTop) {

	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;

	this->pause = false;

	this->speed = BG_SPEED;

	this->bgTex = this->loadTexture(filename);


	for (int i = 0; i < 2; i++) {

		this->bg[i] = sf::RectangleShape();
		this->bg[i].setTexture(&this->bgTex);
		this->bg[i].setSize(sf::Vector2f(windowWidth, ((screenPercent * windowHeight) / 100)));

		if(positionTop)
			this->bg[i].setPosition(sf::Vector2f(windowWidth * i, 0.f));
		else {
			float h = ((100 - screenPercent) * windowHeight) / 100;
			this->bg[i].setPosition(sf::Vector2f(windowWidth * i, h));
		}

	}


}


sf::Texture Background::loadTexture(std::string fileName) {
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Counldn't load texture" << std::endl;
		exit(1);
	}
	return texture;
}

void Background::render(sf::RenderWindow& window) {

	window.draw(this->bg[0]);
	window.draw(this->bg[1]);

}


void Background::update(float deltaTime, sf::RenderWindow& window) {


	if (this->pause) {
		this->render(window);
		return;
	}
	for (int i = 0; i < 2; i++) {

		float newX = this->bg[i].getPosition().x - (this->speed * deltaTime);

		if (newX + this->bg[i].getSize().x + 2.f <= 0.f) {

			this->bg[i].setPosition(windowWidth - 2.0f, this->bg[i].getPosition().y);
		}
		else this->bg[i].setPosition(newX, this->bg[i].getPosition().y);
	}

		
	this->render(window);

}