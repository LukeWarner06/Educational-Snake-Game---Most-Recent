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
	Direction lastSnakeDirection;

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

