#include "NumberManager.h"
#include <iostream>

// Constructor for Number manager, opens the font file and sets all the values of the font.
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

// Spawns new numbers and pushes them to the back of the vector.
void NumberManager::SpawnNumber(int value, sf::Vector2i gridPos)
{
	NumberItem newNumber;
	newNumber.numberValue = value;
	newNumber.gridPos = gridPos;

	activeNumbers.push_back(newNumber);
}

// Draws the numbers in the vector as a string on the window.
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

// Checks if the number is at a specific grid position.
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

// Gets the value of the number at a specific grid position.
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

// Clears all the numbers inside the vector.
void NumberManager::ClearAllNumbers()
{
	activeNumbers.clear();
}