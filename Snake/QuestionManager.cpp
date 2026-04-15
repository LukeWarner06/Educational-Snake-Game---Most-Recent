#include "QuestionManager.h"

Snake snake;

QuestionManager::QuestionManager()
{
	QuestionManager::currentQuestionState = QuestionState::FindFirstNumber;

	firstNumber = 0;
	secondNumber = 0;
	answer = 0;

}

void QuestionManager::OnItemCollected(int collectedNumber)
{
	switch (currentQuestionState)
	{
	case QuestionState::FindFirstNumber:
		firstNumber = collectedNumber;
		currentQuestionState = QuestionState::FindSecondNumber;
		break;

	case QuestionState::FindSecondNumber:
		secondNumber = collectedNumber;
		currentQuestionState = QuestionState::FindAnswer;
		answer = firstNumber * secondNumber;
		break;

	case QuestionState::FindAnswer:
		if (collectedNumber == answer)
		{
			snake.CorrectAnswerEaten();
		}
		else
		{
			snake.WrongAnswerEaten();
		}

		currentQuestionState = QuestionState::FindFirstNumber;
		break;
	}
}
