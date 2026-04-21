#pragma once
#include "Snake.h"
#include <vector>
#include "NumberManager.h"
#include "QuestionManager.h"

class GameManager
{
private:
	Snake snake{};
	QuestionManager questionManager{};
	NumberManager numberManager{};

	std::vector<int> generatedNumbers;
	std::vector<int> answerGeneratedNumbers;
	std::vector<sf::Vector2i> existingPositions;

	const int GRID_WIDTH = 20;
	const int GRID_HEIGHT = 20;

	bool isGameRunning = false;
	bool canChangeDirection = true;

	sf::Color currentBackgroundColor;
	float backgroundFlashTimer;

	sf::Font scoreFont;
	sf::Text scoreText;

	sf::Font gameOverFont;
	sf::Text gameOverText;
	sf::Text finalScoreText;

	sf::Clock clock;
	float timer = 0.f;
	float delay = 0.15f;

	int score = 0;
	int difficultyScaling = 5;
	int correctAnswerCounter = 0;
	int amountOfTimes5CorrectReached = 0;

	bool restartKeyReleased = true;

public:
	GameManager();

	void SetupGame();
	void UpdateSnakeGame();
	void DrawSnakeGame(sf::RenderWindow& window);
	void DrawScoreText(sf::RenderWindow& window);
	void HandleInput();
	void HandleNumberCollection();
	void HandleSnakeCollision();

	void SpawnNewNumber();
	void SpawnRandomPosition(sf::Vector2i& randomGridPos, const std::vector<sf::Vector2i>& existingPositions);

	bool isGridSpaceOccupied(sf::Vector2i gridPos);

	void ClearBackground(sf::RenderWindow& window);

	void GameOver();

	void DrawGameOverScreen(sf::RenderWindow& window);
};

