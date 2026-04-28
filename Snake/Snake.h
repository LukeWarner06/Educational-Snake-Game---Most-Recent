#pragma once
#include <SFML/Graphics.hpp>

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Snake
{
private:
	struct Node
	{
		sf::Vector2i nodePosition;
		Node* nextNode;
	};

	bool isAlive;
	bool hasEatenCorrectAnswer;
	Node* snakeHead;
	Node* snakeTail;
	Direction currentSnakeDirection;
	Direction queuedDirection;

	int tailX = 8;
	int tailY = 10;

	int bodyX = 9;
	int bodyY = 10;

	int headX = 10;
	int headY = 10;

public:
	Snake();
	~Snake();

	sf::Vector2i GetDirection(sf::Vector2i from, sf::Vector2i to)
	{
		return { to.x - from.x, to.y - from.y };
	}

	void CreateSnake();
	void ClearSnake();
	void SetDirection(Direction newSnakeDirection);
	void MoveSnake();
	void CorrectAnswerEaten();
	void WrongAnswerEaten();
	bool IsAlive();

	void DrawSnake(sf::RenderWindow& window, int tileSize);

	sf::Vector2i GetHeadPosition();

	bool isGridPositionOnSnake(sf::Vector2i pos);
};

