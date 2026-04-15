#include "GameManager.h"
#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>


void GameManager::SetupGame()
{
	snake.CreateSnake();
	isGameRunning = true;
	timer = 0.f;

	sf::Vector2i randomPosition;
	do {
		randomPosition.x = std::rand() % GRID_WIDTH;
		randomPosition.y = std::rand() % GRID_HEIGHT;
	} while (isGridSpaceOccupied(randomPosition));

	numberManager.SpawnNumber(5, randomPosition);
}

void GameManager::HandleInput()
{
	if (!canChangeDirection) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		snake.SetDirection(Direction::Up);
		canChangeDirection = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		snake.SetDirection(Direction::Down);
		canChangeDirection = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		snake.SetDirection(Direction::Left);
		canChangeDirection = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		snake.SetDirection(Direction::Right);
		canChangeDirection = false;
	}
}

void GameManager::UpdateSnakeGame()
{
	sf::Time elapsedSinceLastUpdate = clock.restart();
	timer += elapsedSinceLastUpdate.asSeconds();

	HandleInput();

	if (timer > delay)
	{
		timer = 0.f;
		canChangeDirection = true;

		if (snake.IsAlive())
		{
			snake.MoveSnake();

			sf::Vector2i snakeHeadPosition = snake.GetHeadPosition();

			if (numberManager.IsNumberAtPosition(snakeHeadPosition))
			{
				snake.CorrectAnswerEaten();

				
			}

			if (snakeHeadPosition.x < 0 || snakeHeadPosition.x >= GRID_WIDTH || snakeHeadPosition.y < 0 || snakeHeadPosition.y >= GRID_HEIGHT)
			{
				snake.ClearSnake();
			}
		}
	}
}

void GameManager::DrawSnakeGame(sf::RenderWindow& window)
{
	const int TILE_SIZE = 40;
	snake.DrawSnake(window, TILE_SIZE);

	numberManager.DrawNumbers(window);
}

bool GameManager::isGridSpaceOccupied(sf::Vector2i gridPos)
{
	if (snake.isGridPositionOnSnake(gridPos))
	{
		return true;
	}

	if (numberManager.IsNumberAtPosition(gridPos))
	{
		return true;
	}

	return false;
}


