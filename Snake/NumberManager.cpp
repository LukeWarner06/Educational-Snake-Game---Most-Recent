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
	numberText.setFillColor(sf::Color::Yellow);
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
		numberText.setOutlineThickness(1.5f);
		numberText.setOutlineColor(sf::Color::Black);

		float gridX = static_cast<float>(item.gridPos.x * 40);
		float gridY = static_cast<float>(item.gridPos.y * 40);

		sf::FloatRect numberRect = numberText.getLocalBounds();
		numberText.setOrigin({ numberRect.position.x + numberRect.size.x / 2.f, numberRect.position.y + numberRect.size.y / 2.f });

		numberText.setPosition({ gridX + 20.f, gridY + 20.f });

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

int NumberManager::GetNumberValueAtGridPosition(sf::Vector2i gridPos)
{
	for (const auto& item : activeNumbers)
	{
		if (item.gridPos == gridPos)
		{
			return item.numberValue;
		}
	}
	return -1;
}


// Removes number at grid position, after finding it using function from earlier.
void NumberManager::RemoveNumberAtGridPosition(sf::Vector2i gridPos)
{
	for (int i = 0; i < activeNumbers.size(); i++)
	{
		if (activeNumbers[i].gridPos == gridPos)
		{
			activeNumbers.erase(activeNumbers.begin() + i);
			return;
		}
	}
}

void NumberManager::ClearAllNumbers()
{
	activeNumbers.clear();
}