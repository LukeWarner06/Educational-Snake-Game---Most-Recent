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
    // Creates a random seed at the start.
    srand(time(nullptr));

    // Creates a window of 800x800
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Educational Snake Game");
    window.setFramerateLimit(60);
    
    // Creates the Game Manager class so that functions can be called from it.
    GameManager gameManager;
    gameManager.SetupGame();
    
    // While loop that runs while the window is open, but stops when the window is closed.
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

        // Displays the window on the screen
        window.display();
    }

    return 0;
}