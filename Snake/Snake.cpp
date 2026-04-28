#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>

// Constructor to set everything to their default values.
Snake::Snake()
{
	snakeHead = nullptr;
	snakeTail = nullptr;
	isAlive = false;
	hasEatenCorrectAnswer = false;

	currentSnakeDirection = Direction::Right;
	queuedDirection = Direction::Right;
}

//Draws the snake on the screen bit by bit, starting with head and ending with tail
void Snake::DrawSnake(sf::RenderWindow& window, int tileSize)
{
	Node* current = snakeHead;

	while (current != nullptr)
	{
		float x = current->nodePosition.x * tileSize;
		float y = current->nodePosition.y * tileSize;

		sf::RectangleShape snakeSegmentShape(sf::Vector2f(tileSize - 4.f, tileSize - 4.f));
		snakeSegmentShape.setPosition({ x + 2.f, y + 2.f });
		snakeSegmentShape.setOutlineThickness(2.f);
		snakeSegmentShape.setOutlineColor(sf::Color::Black);

		if (current == snakeHead)
		{
			snakeSegmentShape.setSize(sf::Vector2f(tileSize - 3.f, tileSize - 3.f));
			snakeSegmentShape.setPosition({x + 1.f, y + 1.f});
			snakeSegmentShape.setFillColor(sf::Color(0, 200, 0));
			snakeSegmentShape.setOutlineColor(sf::Color::Yellow);

			sf::CircleShape dot(3.f);
			dot.setFillColor(sf::Color::Yellow);
			dot.setPosition({ x + tileSize / 2.f - 3.f, y + tileSize / 2.f - 3.f });
			window.draw(dot);
		}
		else if (current->nextNode == nullptr)
		{
			snakeSegmentShape.setFillColor(sf::Color(0, 150, 0));
		}
		else
		{
			snakeSegmentShape.setFillColor(sf::Color::Green);
		}
		window.draw(snakeSegmentShape);
		current = current->nextNode;
	}
}

// Creates the actual snake segments within the linked list.
void Snake::CreateSnake()
{
	ClearSnake();

	Node* newTail = new Node;
	newTail->nodePosition = sf::Vector2i(tailX, tailY);
	newTail->nextNode = nullptr;

	Node* newMiddle = new Node;
	newMiddle->nodePosition = sf::Vector2i(bodyX, bodyY);
	newMiddle->nextNode = newTail;

	Node* newHead = new Node;
	newHead->nodePosition = sf::Vector2i(headX, headY);
	newHead->nextNode = newMiddle;

	snakeHead = newHead;
	snakeTail = newTail;

	isAlive = true;

	currentSnakeDirection = Direction::Right;

	hasEatenCorrectAnswer = false;
}

// Empties the linked list completely and updates the game to tell it the snake is no longer alive.
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

// Destructor to clear the snake.
Snake::~Snake()
{
	ClearSnake();
}

// Snake Movement, based off of an enum and switch cases.
void Snake::MoveSnake()
{
	currentSnakeDirection = queuedDirection;

	if (snakeHead == nullptr || !isAlive)
	{
		return;
	}

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

	if (newHeadPosition.y < 2)
	{
		isAlive = false;
		ClearSnake();
		return;
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
}

// sets the current direction and checks if the new direction is the opposite of the current, if it is then the queued direction becomes the same as new direction.
void Snake::SetDirection(Direction newDirection)
{
	if (currentSnakeDirection == Direction::Up && newDirection == Direction::Down) return;
	if (currentSnakeDirection == Direction::Down && newDirection == Direction::Up) return;
	if (currentSnakeDirection == Direction::Left && newDirection == Direction::Right) return;
	if (currentSnakeDirection == Direction::Right && newDirection == Direction::Left) return;

	queuedDirection = newDirection;
}

// Updates boolean to tell game that the right answers been eaten.
void Snake::CorrectAnswerEaten()
{
	hasEatenCorrectAnswer = true;
}

// Updates boolean to tell game the wrong answers been eaten, deletes the tail, checks if theres only 1 segment left in the snake and if so, clears the snake, as its dead.
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

// Returns the value of isAlive.
bool Snake::IsAlive()
{
	return isAlive;
}

// Gets the current position of the snake's head.
sf::Vector2i Snake::GetHeadPosition()
{
	if (snakeHead == nullptr)
	{
		return sf::Vector2i(0, 0);
	}
	return snakeHead->nodePosition;
}

// Checks if the snake is on a specific grid position.
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