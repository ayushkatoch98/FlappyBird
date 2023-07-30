#include "Background.h"
#include <iostream>


#define PRE_LOAD_BG 3
#define BG_SPEED 150.0f

Background::Background(int windowHeight, int windowWidth, std::string filename, float screenPercent, bool positionTop) {

	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;

	this->pause = false;

	this->speed = BG_SPEED;

	this->bgTex = this->loadTexture(filename);


	for (int i = 0; i < PRE_LOAD_BG; i++) {

		this->bg[i] = sf::Sprite();
		this->bg[i].setTexture(this->bgTex);


		this->bg[i].setScale(windowWidth / (float) this->bg[i].getTexture()->getSize().x, ((screenPercent * windowHeight) / 100) / this->bg[i].getTexture()->getSize().y);

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
	window.draw(this->bg[2]);

}


void Background::update(float deltaTime, sf::RenderWindow& window) {


	if (this->pause) {
		this->render(window);
		return;
	}
	for (int i = PRE_LOAD_BG - 1; i >= 0; i--) {

		// reset bg position
		if (this->bg[i].getPosition().x + this->bg[i].getGlobalBounds().width <= 0.f) {
			int x = i - 1;
			if (x < 0) {
				x = PRE_LOAD_BG - 1;
			}
			this->bg[i].setPosition(this->bg[x].getPosition().x + this->bg[x].getGlobalBounds().width, this->bg[i].getPosition().y);
		}
		// move 
		
		float newX = -(this->speed * deltaTime);
		this->bg[i].move(newX, 0.f);
	}

		
	this->render(window);

}