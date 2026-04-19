#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class QuestionManager
{
	enum class QuestionState
	{
		FindFirstNumber,
		FindSecondNumber,
		FindAnswer
	};

private:
	int firstNumber;
	int secondNumber;
	int answer;

	sf::Font font;
	sf::Text questionText;

	QuestionState currentQuestionState;

public:
	QuestionManager();

	enum class QuestionEvent
	{
		None,
		PickedFirstNumber,
		PickedSecondNumber,
		CorrectAnswer,
		WrongAnswer
	};

	QuestionEvent OnItemCollected(int collectedNumber);

	int GetAnswerValue();

	void DrawCurrentQuestionOnScreen(sf::RenderWindow& window);

	void ResetQuestion();
};

