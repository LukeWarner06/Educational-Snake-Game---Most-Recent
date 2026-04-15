#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>

void Snake::DrawSnake(sf::RenderWindow& window, int tileSize)
{
	sf::RectangleShape snakeSegmentShape(sf::Vector2f(tileSize, tileSize));
	snakeSegmentShape.setFillColor(sf::Color::Green);

	Node* current = snakeHead;
	while (current != nullptr)
	{
		snakeSegmentShape.setPosition(sf::Vector2f(current->nodePosition.x * tileSize, current->nodePosition.y * tileSize));

		window.draw(snakeSegmentShape);
		current = current->nextNode;
	}
}

void Snake::CreateSnake()
{
	ClearSnake();

	Node* newTail = new Node;
	newTail->nodePosition = sf::Vector2i(8, 10);
	newTail->nextNode = nullptr;

	Node* newMiddle = new Node;
	newMiddle->nodePosition = sf::Vector2i(9, 10);
	newMiddle->nextNode = newTail;

	Node* newHead = new Node;
	newHead->nodePosition = sf::Vector2i(10, 10);
	newHead->nextNode = newMiddle;

	snakeHead = newHead;
	snakeTail = newTail;

	isAlive = true;

	currentSnakeDirection = Direction::Right;

	hasEatenCorrectAnswer = false;
}

void Snake::ClearSnake()
{
	Node* current = snakeHead;
	while (current != nullptr)
	{
		Node* nextItem = current->nextNode;
		delete current;
		current = nextItem;
	}

	snakeHead = nullptr;
	snakeTail = nullptr;
	isAlive = false;
}

Snake::~Snake()
{
	ClearSnake();
}

void Snake::MoveSnake()
{
	sf::Vector2i newHeadPosition;
	switch (currentSnakeDirection)
	{
	case Direction::Up:
		newHeadPosition = snakeHead->nodePosition + sf::Vector2i(0, -1);
		break;

	case Direction::Down:
		newHeadPosition = snakeHead->nodePosition + sf::Vector2i(0, 1);
		break;

	case Direction::Left:
		newHeadPosition = snakeHead->nodePosition + sf::Vector2i(-1, 0);
		break;

	case Direction::Right:
		newHeadPosition = snakeHead->nodePosition + sf::Vector2i(1, 0);
		break;
	}

	Node* newHead = new Node;
	newHead->nodePosition = newHeadPosition;
	newHead->nextNode = snakeHead;

	snakeHead = newHead;

	if (hasEatenCorrectAnswer)
	{
		hasEatenCorrectAnswer = false;
	}

	else
	{
		Node* current = newHead->nextNode;
		while (current->nextNode != snakeTail)
		{
			current = current->nextNode;
		}

		current->nextNode = nullptr;
		delete snakeTail;
		snakeTail = current;
	}

	Node* current = snakeHead->nextNode;
	while (current->nextNode != nullptr)
	{
		if (newHeadPosition == current->nodePosition)
		{
			isAlive = false;
			ClearSnake();
			return;
		}
		current = current->nextNode;
	}

	lastSnakeDirection = currentSnakeDirection;
}

void Snake::SetDirection(Direction newSnakeDirection)
{
	if (lastSnakeDirection == Direction::Up && newSnakeDirection != Direction::Down)
	{
		currentSnakeDirection = newSnakeDirection;
	}
	else if (lastSnakeDirection == Direction::Down && newSnakeDirection != Direction::Up)
	{
		currentSnakeDirection = newSnakeDirection;
	}
	else if (lastSnakeDirection == Direction::Right && newSnakeDirection != Direction::Left)
	{
		currentSnakeDirection = newSnakeDirection;
	}
	else if (lastSnakeDirection == Direction::Left && newSnakeDirection != Direction::Right)
	{
		currentSnakeDirection = newSnakeDirection;
	}
}

void Snake::CorrectAnswerEaten()
{
	hasEatenCorrectAnswer = true;
}

void Snake::WrongAnswerEaten()
{
	hasEatenCorrectAnswer = false;

	Node* current = snakeHead;

	if (current->nextNode == nullptr)
	{
		isAlive = false;
		ClearSnake();
		return;
	}

	while (current->nextNode != snakeTail)
	{
		current = current->nextNode;
	}

	current->nextNode = nullptr;
	delete snakeTail;
	snakeTail = current;

	if (snakeHead == snakeTail)
	{
		isAlive = false;
		ClearSnake();
	}
}

bool Snake::IsAlive()
{
	return isAlive;
}

sf::Vector2i Snake::GetHeadPosition()
{
	return snakeHead->nodePosition;
}

bool Snake::isGridPositionOnSnake(sf::Vector2i pos)
{
	Node* current = snakeHead;
	while (current != nullptr)
	{
		if (current->nodePosition == pos)
		{
			return true;
		}
		current = current->nextNode;
	}
	return false;
}