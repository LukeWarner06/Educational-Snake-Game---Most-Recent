#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class NumberManager
{
private:
	struct NumberItem {
		sf::Vector2i gridPos;
		int numberValue;
	};

	sf::Font numberFont;
	sf::Text numberText;
	std::vector<NumberItem> activeNumbers;

public:
	NumberManager();

	void SpawnNumber(int value, sf::Vector2i gridPos);
	void DrawNumbers(sf::RenderWindow& window);
	bool IsNumberAtPosition(sf::Vector2i gridPos);
};

