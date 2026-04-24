#include "GameManager.h"
#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

GameManager::GameManager() : scoreText(scoreFont), gameOverText(scoreFont), finalScoreText(scoreFont)
{
	if (!scoreFont.openFromFile("assets/Times New Roman Bold.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
		exit(1);
	}

	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	gameOverText.setFont(scoreFont);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(sf::Color::White);

	finalScoreText.setFont(scoreFont);
	finalScoreText.setCharacterSize(28);
	finalScoreText.setFillColor(sf::Color::White);

	currentBackgroundColor = sf::Color(0, 0, 0, 100);
	backgroundFlashTimer = 0.f;

	soundManager.Load("collect", "sounds/collect.wav");
	soundManager.Load("correct", "sounds/correct.wav");
	soundManager.Load("wrong", "sounds/wrong.wav");
	soundManager.Load("grow", "sounds/grow.wav");
	soundManager.Load("shrink", "sounds/shrink.wav");
	soundManager.Load("gameover", "sounds/gameover.wav");
}

void GameManager::DrawScoreText(sf::RenderWindow& window)
{
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition({ 10.f, 10.f });
	window.draw(scoreText);
}

void GameManager::SpawnRandomPosition(sf::Vector2i& randomGridPos, const std::vector<sf::Vector2i>& existingPositions)
{
	bool tooClose;

	do {
		tooClose = false;
		randomGridPos.x = std::rand() % GRID_WIDTH;
		randomGridPos.y = std::rand() % GRID_HEIGHT;

		if (isGridSpaceOccupied(randomGridPos))
		{
			tooClose = true;
			continue;
		}

		for (const auto& pos : existingPositions)
		{
			int dx = randomGridPos.x - pos.x;
			int dy = randomGridPos.y - pos.y;

			int distanceSquared = (dx * dx) + (dy * dy);

			if (distanceSquared < 25)
			{
				tooClose = true;
				break;
			}
		}
	} while (tooClose);
}

void GameManager::SpawnNewNumber()
{
	sf::Vector2i randomGridPos;
	generatedNumbers.clear();

	std::vector<sf::Vector2i> newPositions;

	for (int i = 0; i < difficultyScaling; i++)
	{
		SpawnRandomPosition(randomGridPos, newPositions);
		newPositions.push_back(randomGridPos);
		int newNumber = rand() % difficultyScaling + 1;
		while (std::find(generatedNumbers.begin(), generatedNumbers.end(), newNumber) != generatedNumbers.end())
		{
			newNumber = rand() % difficultyScaling + 1;
		}
		generatedNumbers.push_back(newNumber);
		numberManager.SpawnNumber(newNumber, randomGridPos);
	}
}

void GameManager::SetupGame()
{
	snake.CreateSnake();

	correctAnswerCounter = 0;
	amountOfTimes5CorrectReached = 0;
	difficultyScaling = 5;

	isGameRunning = true;
	canChangeDirection = true;
	timer = 0.f;
	score = 0;
	delay = 0.15f;

	numberManager.ClearAllNumbers();
	questionManager.ResetQuestion();
	SpawnNewNumber();
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

void GameManager::HandleNumberCollection()
{
	sf::Vector2i snakeHeadPosition = snake.GetHeadPosition();

	if (numberManager.IsNumberAtPosition(snakeHeadPosition))
	{
		int collectedNumber = numberManager.GetNumberValueAtGridPosition(snakeHeadPosition);
		numberManager.RemoveNumberAtGridPosition(snakeHeadPosition);
		soundManager.Play("collect");
		QuestionManager::QuestionEvent collectedResult = questionManager.OnItemCollected(collectedNumber);

		if (collectedResult == QuestionManager::QuestionEvent::PickedFirstNumber)
		{
			numberManager.ClearAllNumbers();
			SpawnNewNumber();
		}

		else if (collectedResult == QuestionManager::QuestionEvent::PickedSecondNumber)
		{
			numberManager.ClearAllNumbers();
			int correctAnswer = questionManager.GetAnswerValue();
			int wrongAnswer1 = questionManager.GetAnswerValue() + rand() % 5 + 2;
			int wrongAnswer2 = questionManager.GetAnswerValue() - rand() % 5 - 2;

			sf::Vector2i randomGridPos;
			
			SpawnRandomPosition(randomGridPos, existingPositions);

			numberManager.SpawnNumber(correctAnswer, randomGridPos);

			SpawnRandomPosition(randomGridPos, existingPositions);

			numberManager.SpawnNumber(wrongAnswer1, randomGridPos);

			SpawnRandomPosition(randomGridPos, existingPositions);

			numberManager.SpawnNumber(wrongAnswer2, randomGridPos);

			SpawnRandomPosition(randomGridPos, existingPositions);
		}

		else if (collectedResult == QuestionManager::QuestionEvent::CorrectAnswer)
		{
			snake.CorrectAnswerEaten();
			correctAnswerCounter++;
			soundManager.Play("correct");
			score += 100;
			if (correctAnswerCounter >= 5)
			{
				score * 2;
				difficultyScaling = 10;
				amountOfTimes5CorrectReached++;
				correctAnswerCounter = 0;
			}

			if (amountOfTimes5CorrectReached == 2)
			{
				difficultyScaling = 12;
			}
			delay *= 0.95f;
			numberManager.ClearAllNumbers();
			SpawnNewNumber();
		}

		else if (collectedResult == QuestionManager::QuestionEvent::WrongAnswer)
		{
			snake.WrongAnswerEaten();
			soundManager.Play("wrong");
			correctAnswerCounter = 0;
			score -= 100;
			delay *= 1.05f;
			numberManager.ClearAllNumbers();
			SpawnNewNumber();
		}
	}
}

void GameManager::HandleSnakeCollision()
{
	sf::Vector2i snakeHeadPosition = snake.GetHeadPosition();

	if (snakeHeadPosition.x < 0 || snakeHeadPosition.x >= GRID_WIDTH || snakeHeadPosition.y < 0 || snakeHeadPosition.y >= GRID_HEIGHT)
	{
		GameOver();
	}
}

void GameManager::UpdateSnakeGame()
{
	if (!isGameRunning)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			if (restartKeyReleased)
			{
				SetupGame();
				restartKeyReleased = false;
			}
		}
		else
		{
			restartKeyReleased = true;
		}
		return;
	}

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

			HandleNumberCollection();

			HandleSnakeCollision();
		}
	}

	if (!snake.IsAlive() && isGameRunning)
	{
		GameOver();
	}
}

void GameManager::DrawSnakeGame(sf::RenderWindow& window)
{
	const int TILE_SIZE = 40;
	snake.DrawSnake(window, TILE_SIZE);

	numberManager.DrawNumbers(window);
	questionManager.DrawCurrentQuestionOnScreen(window);
	DrawScoreText(window);

	if (!isGameRunning)
	{
		window.clear();
		DrawGameOverScreen(window);
	}
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

void GameManager::ClearBackground(sf::RenderWindow& window)
{
	window.clear(currentBackgroundColor);

	for (int row = 0; row < 800; row += 40)
	{
		for (int col = 0; col < 800; col += 40)
		{
			sf::RectangleShape cell(sf::Vector2f(40.f, 40.f));

			if ((row / 40 + col / 40) % 2 == 0)
			{
				cell.setFillColor(sf::Color(0, 81, 215));
			}
			else
			{
				cell.setFillColor(sf::Color(0, 73, 209));
			}

			cell.setPosition(sf::Vector2f(col, row));

			window.draw(cell);
		}
    }
}

void GameManager::GameOver()
{
	isGameRunning = false;
	snake.ClearSnake();

	gameOverText.setString("Game Over!");
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineThickness(1.5f);
	gameOverText.setOutlineColor(sf::Color::White);
	sf::FloatRect gameOverRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(gameOverRect.getCenter());
	gameOverText.setPosition({400.f, 320.f});

	finalScoreText.setString("Score: " + std::to_string(score) + "\nPress 'R' to Restart.");
	finalScoreText.setFillColor(sf::Color::Yellow);
	finalScoreText.setOutlineThickness(1.25f);
	finalScoreText.setOutlineColor(sf::Color::White);
	sf::FloatRect finalScoreRect = finalScoreText.getLocalBounds();
	finalScoreText.setOrigin(finalScoreRect.getCenter());
	finalScoreText.setPosition({ 400.f, 420.f });
}

void GameManager::DrawGameOverScreen(sf::RenderWindow& window)
{
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(window.getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(overlay);

	window.draw(gameOverText);
	window.draw(finalScoreText);
}