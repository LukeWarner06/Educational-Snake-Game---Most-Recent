#pragma once
#include "Snake.h"
#include <vector>
#include "NumberManager.h"

class GameManager
{
private:
	Snake snake;
	NumberManager numberManager;

	const int GRID_WIDTH = 20;
	const int GRID_HEIGHT = 20;

	bool isGameRunning;
	bool canChangeDirection;

	sf::Clock clock;
	float timer = 0.f;
	float delay = 0.15f;

public:
	void SetupGame();
	void UpdateSnakeGame();
	void DrawSnakeGame(sf::RenderWindow& window);
	void HandleInput();

	bool isGridSpaceOccupied(sf::Vector2i gridPos);
};

