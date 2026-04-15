#include "NumberManager.h"
#include <iostream>

NumberManager::NumberManager() : numberText(numberFont)
{
	if (!numberFont.openFromFile("assets/Times New Roman Bold.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
		exit(1);
	}

	numberText.setFont(numberFont);
	numberText.setCharacterSize(24);
	numberText.setFillColor(sf::Color::White);
}

void NumberManager::SpawnNumber(int value, sf::Vector2i gridPos)
{
	NumberItem newNumber;
	newNumber.numberValue = value;
	newNumber.gridPos = gridPos;

	activeNumbers.push_back(newNumber);
}

void NumberManager::DrawNumbers(sf::RenderWindow& window)
{
	for (const auto& item : activeNumbers)
	{
		numberText.setString(std::to_string(item.numberValue));

		float gridX = static_cast<float>(item.gridPos.x * 40);
		float gridY = static_cast<float>(item.gridPos.y * 40);

		numberText.setPosition({ gridX + 10.f, gridY + 5.f });

		window.draw(numberText);
	}
}

bool NumberManager::IsNumberAtPosition(sf::Vector2i gridPos)
{
	for (const auto& item : activeNumbers)
	{
		if (item.gridPos == gridPos)
		{
			return true;
		}
	}
	return false;
}