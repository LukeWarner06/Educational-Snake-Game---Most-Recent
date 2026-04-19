/*
    Snake - Start Project

    This project is set up to link to SFML (a library supporting 2D graphics, sound, user input and networing)
    There is a subdirectory in the project called SFML-3.0.0 containing SFML headers and libraries
    The project settings are configured to look for these files

    SFML reference: https://www.sfml-dev.org/documentation/3.0.0/
    SFML Tutorials: https://www.sfml-dev.org/tutorials/3.0/
*/

#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Snake.h"

int main()
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Educational Snake Game");
    window.setFramerateLimit(60);
    
    GameManager gameManager;
    gameManager.SetupGame();
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        gameManager.UpdateSnakeGame();

        gameManager.ClearBackground(window);
        gameManager.DrawSnakeGame(window);

        window.display();
    }

    return 0;
}