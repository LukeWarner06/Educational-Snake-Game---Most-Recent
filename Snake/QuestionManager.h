#pragma once
#include "GameManager.h"
#include "Snake.h"

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

	QuestionState currentQuestionState;

public:
	QuestionManager();

	void OnItemCollected(int collectedNumber);
};

