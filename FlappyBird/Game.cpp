#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"

#define SCORE_DIGIT_OFFSET 30.f

Game::Game(int screenHeight, int screenWidth) {

    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    this->gameStarted = false;
    this->gameRunning = false;
	this->gameOver = false;
    this->jumpHold = false;

	this->bird = new Bird(screenHeight, screenWidth);
	this->pipeSpawner = new PipeSpawner(screenHeight, screenWidth);
    this->sky = new Background(screenHeight, screenWidth, "./Images/background-day.png", 80.f, true);
    this->floor = new Background(screenHeight, screenWidth, "./Images/base.png", 20.f, false);

    this->bird->setIsAlive(false);

    this->logoTex = this->loadTexture("./Images/flappybird.png");
    this->gameOverTex = this->loadTexture("./Images/gameover.png");

    this->startLogo = this->createCenterLogo(this->logoTex);
    this->gameOverLogo = this->createCenterLogo(this->gameOverTex);

    for (int i = 0; i < 10; i++) {
        this->digits[i] = this->loadTexture("./Images/" + std::to_string(i) + ".png");
    }


    for (int i = 0; i < 3; i++) {
        this->scores[i] = sf::RectangleShape();

    }

}


void Game::reset() {


    this->gameStarted = false;
    this->gameRunning = false;
    this->gameOver = false;

    delete this->bird;
    delete this->pipeSpawner;
    delete this->sky;
    delete this->floor;

    this->bird = new Bird(this->screenHeight, this->screenWidth);
    this->pipeSpawner = new PipeSpawner(this->screenHeight, this->screenWidth);
    this->sky = new Background(this->screenHeight, this->screenWidth, "./Images/background-day.png", 80.f, true);
    this->floor = new Background(this->screenHeight, this->screenWidth, "./Images/base.png", 20.f, false);

    this->bird->setIsAlive(false);

}

sf::RectangleShape Game::createCenterLogo(sf::Texture &texture) {
    sf::RectangleShape rect;

    rect.setTexture(&texture);
    rect.setSize(sf::Vector2f(this->screenWidth - 100.f, 80.f));

    sf::FloatRect textRect = rect.getLocalBounds();
    rect.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    rect.setPosition(sf::Vector2f(this->screenWidth / 2.0f, this->screenHeight / 2.0f));

    return rect;

}

sf::Texture Game::loadTexture(std::string fileName) {
    sf::Texture texture;
    if (!texture.loadFromFile(fileName)) {
        std::cout << "Counldn't load texture" << std::endl;
        exit(1);
    }
    return texture;
}

void Game::renderScore(sf::RenderWindow& window, int score) {

    int temp = score;
    int lastDigit = 0;
    int i = 0;


    
    if (score >= 100) {
        i = 2;
    }

    if (score >= 10) {
        i = 1;
    }
    
    while (temp != 0) {
        lastDigit = temp % 10;
        temp /= 10;
        this->scores[i].setTexture(&this->digits[lastDigit]);
        

        this->scores[i].setSize(sf::Vector2f(30.f, 50.f));
        sf::FloatRect textRect = this->scores[i].getLocalBounds();
        this->scores[i].setOrigin((textRect.width / 2.0f), 0.f);
        this->scores[i].setPosition(sf::Vector2f((this->screenWidth / 2) + (i * SCORE_DIGIT_OFFSET), 10.f));
        
        window.draw(this->scores[i]);

        i--;
    }



}

void Game::startScreen(sf::RenderWindow &window) {

    window.draw(this->startLogo);


}


void Game::gameOverScreen(sf::RenderWindow& window) {

    window.draw(this->gameOverLogo);
}


void Game::update(float deltaTime, sf::RenderWindow &window) {
    
    window.clear();

    this->sky->update(deltaTime, window);
    if (this->gameRunning) this->pipeSpawner->update(deltaTime, window);
    this->floor->update(deltaTime, window);

    this->bird->update(deltaTime, window);

    this->renderScore(window, this->pipeSpawner->getScore());

    if (this->gameOver) {
        // load gameover screen
        this->gameOverScreen(window);
        window.display();
        return;
    }

    if (!this->gameRunning) {
        // load start screen
        this->startScreen(window);
        window.display();
        return;
    }
    



    if (this->bird->collisionFloor(this->floor->getBg()) || 
        this->bird->collisionObstacles(this->pipeSpawner->getActiveObstacle())) {
            this->bird->setIsAlive(false);
            this->floor->setPause(true);
            this->sky->setPause(true);
            this->pipeSpawner->setPause(true);
            this->gameOver = true;
    }

    
    window.display();


}


void Game::event(sf::Event event) {
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Space) {
            this->jumpHold = false;
        }
    }
	if (event.type == sf::Event::KeyPressed) {

		switch (event.key.code) {

        case sf::Keyboard::Space: {
            if (this->gameRunning){
                
                if (this->jumpHold) return;
                
                this->jumpHold = true;
                this->bird->jump();
                
                
            }
            else{
                
                if (!this->gameOver) {
                    this->gameRunning = true;
                    this->gameStarted = true;
                    this->bird->setIsAlive(true);
                }
            }
            break;
        };

        case sf::Keyboard::R : {
            if (this->gameOver) {
                this->reset();
            }
            break;
        }
                                   

		}


	}
}