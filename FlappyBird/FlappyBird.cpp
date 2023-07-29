#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

#define SCREEN_HEIGHT 885
#define SCREEN_WIDTH 500


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Birds!");
    
    Game game(SCREEN_HEIGHT, SCREEN_WIDTH);

    window.setFramerateLimit(60u);
    float deltaTime;
       
    sf::Clock clock;
    sf::Time time;


    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            
            game.event(event);
            
        }

        
        game.update(deltaTime, window);

        
    }

    return 0;
}