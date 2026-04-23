#include "Snake.h"
#include <SFML/Window/Keyboard.hpp>

Snake::Snake()
{
	snakeHead = nullptr;
	snakeTail = nullptr;
	isAlive = false;
	hasEatenCorrectAnswer = false;
}

void Snake::DrawSnake(sf::RenderWindow& window, int tileSize)
{
	

	Node* prev = nullptr;
	Node* current = snakeHead;

	while (current != nullptr)
	{
		Node* next = current->nextNode;

		float x = current->nodePosition.x * tileSize;
		float y = current->nodePosition.y * tileSize;

		float padding = 4.f;
		float size = tileSize - padding;

		sf::RectangleShape snakeSegmentShape(sf::Vector2f(size, size));
		snakeSegmentShape.setPosition({ x + padding / 2.f, y + padding / 2.f });
		snakeSegmentShape.setFillColor(sf::Color::Green);
		snakeSegmentShape.setOutlineThickness(2.f);
		snakeSegmentShape.setOutlineColor(sf::Color::Black);

		if (current == snakeHead)
		{
			snakeSegmentShape.setFillColor(sf::Color(0, 200, 0));
			window.draw(snakeSegmentShape);

			float eyeRadius = tileSize * 0.12f;
			sf::CircleShape eye(eyeRadius);
			eye.setFillColor(sf::Color::White);

			sf::CircleShape pupil(eyeRadius / 2.f);
			pupil.setFillColor(sf::Color::Black);

			float offsetX1, offsetY1, offsetX2, offsetY2;

			switch (currentSnakeDirection)
			{
			case Direction::Right:
				offsetX1 = tileSize * 0.65f; offsetY1 = tileSize * 0.25f;
				offsetX2 = tileSize * 0.65f; offsetY2 = tileSize * 0.65f;
				break;
			case Direction::Left:
				offsetX1 = tileSize * 0.15f; offsetY1 = tileSize * 0.25f;
				offsetX2 = tileSize * 0.15f; offsetY2 = tileSize * 0.65f;
				break;
			case Direction::Up:
				offsetX1 = tileSize * 0.25f; offsetY1 = tileSize * 0.15f;
				offsetX2 = tileSize * 0.65f; offsetY2 = tileSize * 0.15f;
				break;
			case Direction::Down:
				offsetX1 = tileSize * 0.25f; offsetY1 = tileSize * 0.65f;
				offsetX2 = tileSize * 0.65f; offsetY2 = tileSize * 0.65f;
				break;
			}

			eye.setPosition({ x + offsetX1, y + offsetY1 });
			window.draw(eye);

			eye.setPosition({ x + offsetX2, y + offsetY2 });
			window.draw(eye);

			float pupilOffset = eyeRadius / 2.f;

			pupil.setPosition({ x + offsetX1 + pupilOffset, y + offsetY1 + pupilOffset });
			window.draw(pupil);

			pupil.setPosition({ x + offsetX2 + pupilOffset, y + offsetY2 + pupilOffset });
			window.draw(pupil);
		}
		else if (next == nullptr)
		{
			snakeSegmentShape.setFillColor(sf::Color(0, 150, 0));
			window.draw(snakeSegmentShape);

			sf::CircleShape tailCircle(size / 2.f);
			tailCircle.setFillColor(sf::Color(0, 150, 0));
			tailCircle.setPosition({ x + padding / 2.f, y + padding / 2.f });
			window.draw(tailCircle);
		}

		else
		{
			sf::Vector2i dirFrom = GetDirection(prev->nodePosition, current->nodePosition);
			sf::Vector2i dirTo = GetDirection(current->nodePosition, next->nodePosition);

			if (dirFrom == dirTo)
			{
				snakeSegmentShape.setFillColor(sf::Color::Green);
				window.draw(snakeSegmentShape);
			}
			else
			{
				snakeSegmentShape.setFillColor(sf::Color::Green);
				window.draw(snakeSegmentShape);

				sf::CircleShape corner(size / 2.f);
				corner.setFillColor(sf::Color::Green);

				if ((dirFrom.x == 1 && dirTo.y == 1) || (dirTo.x == 1 && dirFrom.y == 1))
				{
					corner.setPosition({ x + padding / 2.f, y + padding / 2.f });
				}

				else if ((dirFrom.y == 1 && dirTo.x == -1) || (dirTo.y == 1 && dirFrom.x == -1))
				{
					corner.setPosition({ x + padding / 2.f, y + padding / 2.f });
				}

				else if ((dirFrom.x == -1 && dirTo.y == -1) || (dirTo.x == -1 && dirFrom.y == -1))
				{
					corner.setPosition({ x + padding / 2.f, y + padding / 2.f });
				}

				else if ((dirFrom.y == -1 && dirTo.x == 1) || (dirTo.y == -1 && dirFrom.x == 1))
				{
					corner.setPosition({ x + padding / 2.f, y + padding / 2.f });
				}

				window.draw(corner);
			}
		}

		prev = current;
		current = next;
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
	if (snakeHead == nullptr)
	{
		return sf::Vector2i(0, 0);
	}
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