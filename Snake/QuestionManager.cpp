#include "QuestionManager.h"

// Constructor to open the font file and set the first state of the game to finding the first number.
QuestionManager::QuestionManager() : questionText(font)
{
	QuestionManager::currentQuestionState = QuestionState::FindFirstNumber;

	firstNumber = 0;
	secondNumber = 0;
	answer = 0;

	if (!font.openFromFile("assets/Times New Roman Bold.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
		exit(1);
	}

	questionText.setFont(font);
	questionText.setCharacterSize(24);
	questionText.setFillColor(sf::Color::White);
	questionText.setOutlineThickness(1.5f);
	questionText.setOutlineColor(sf::Color::Black);
}

// Updates the Game State depending on what item has been collected.
QuestionManager::QuestionEvent QuestionManager::OnItemCollected(int collectedNumber)
{
	switch (currentQuestionState)
	{
	case QuestionState::FindFirstNumber:
		firstNumber = collectedNumber;
		currentQuestionState = QuestionState::FindSecondNumber;
		return QuestionEvent::PickedFirstNumber;

	case QuestionState::FindSecondNumber:
		secondNumber = collectedNumber;
		currentQuestionState = QuestionState::FindAnswer;
		answer = firstNumber * secondNumber;
		return QuestionEvent::PickedSecondNumber;

	case QuestionState::FindAnswer:
		QuestionEvent lastState = (collectedNumber == answer) ? QuestionEvent::CorrectAnswer : QuestionEvent::WrongAnswer;
		currentQuestionState = QuestionState::FindFirstNumber;
		return lastState;
	}
	return QuestionEvent::None;
}

// Returns the value of the answer.
int QuestionManager::GetAnswerValue()
{
	return answer;
}

// Draws the current question on the window, depending on what game state we are in.
void QuestionManager::DrawCurrentQuestionOnScreen(sf::RenderWindow& window)
{
	switch (currentQuestionState)
	{
	case QuestionState::FindFirstNumber:
		questionText.setString("? x ? = ?");
		break;

	case QuestionState::FindSecondNumber:
		questionText.setString(std::to_string(firstNumber) + " x ? = ?");
		break;

	case QuestionState::FindAnswer:
		questionText.setString(std::to_string(firstNumber) + " x " + std::to_string(secondNumber) + " = ?");
		break;
	}

	sf::FloatRect screenBounds = questionText.getLocalBounds();
	float screenPositionX = (window.getSize().x - screenBounds.size.x) / 2.f;
	questionText.setPosition({ screenPositionX, 10.f });
	window.draw(questionText);
}

// Resetst the question back to the beginning.
void QuestionManager::ResetQuestion()
{
	QuestionManager::currentQuestionState = QuestionState::FindFirstNumber;

	firstNumber = 0;
	secondNumber = 0;
	answer = 0;

	if (!font.openFromFile("assets/Times New Roman Bold.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
		exit(1);
	}

	questionText.setFont(font);
	questionText.setCharacterSize(24);
	questionText.setFillColor(sf::Color::White);
}