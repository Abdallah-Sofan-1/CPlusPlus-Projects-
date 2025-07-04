#include <iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixed = 5 };

struct stQuestion
{
	int Number1 = 0, Number2 = 0, CorrectAnswer = 0, PlayerAnswer = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};



short ReadHowManyQuestions()
{
	short Number = 0;
	do
	{
		cout << "How Many Question Do You Want To Answer? ";
		cin >> Number;
		cout << endl;
	} while (Number < 1 || Number > 10);

	return Number;
}

int ReadNumberBetween(string Message, int From, int To)
{
	int Number = 0;
	do
	{
		cout << Message << endl;
		cin >> Number;
		cout << endl;
	} while (Number < From || Number > To);

	return Number;
}
enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{

		cout << "Enter Question Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel<1 || QuestionLevel > 4);
	
	return (enQuestionLevel)QuestionLevel;
}
enOperationType ReadOpType()
{
	short OpType;
	do
	{

		cout << "Enter Operation Type[1] Sum, [2] Sub, [3] Mul, [4] Div, [5] Mix  ? "  ;
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType) OpType;
	
}
short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
		{
			QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
		}
	
	if (OpType == enOperationType::Mixed)
	{
		OpType = (enOperationType)RandomNumber(1, 4);
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
		{
		case enQuestionLevel::Easy:
			Question.Number1 = RandomNumber(0, 10);
			Question.Number2 = RandomNumber(0, 10);
			
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
			Question.QuestionLevel = QuestionLevel;
			return Question;

		case enQuestionLevel::Med:
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
			Question.QuestionLevel = QuestionLevel;
			return Question;

		case enQuestionLevel::Hard:
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
			Question.QuestionLevel = QuestionLevel;
			return Question;
	}

	return Question;
}
void GenerateQuizzQuestions(stQuizz & Quizz)
{
	for (short  Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}


void EndGameScreenColor(bool isPass)
{
	if (isPass)
		system("color 2F");
	else
		system("color 4F");
}

string GetOpTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	case enOperationType::Mixed:
		return "Mix";

	}
}
void PrintQuestion(stQuizz &Quizz, short QuestionNumber)
{
	cout << '\n';
	cout << "Question [" << QuestionNumber + 1 << "] Out From" << '[' << Quizz.NumberOfQuestions << ']' << endl << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_________\n";
}
int ReadQuestionAnswer()
{
	short UserAnswer = 0;
	cin >> UserAnswer;
	return UserAnswer;

}

void SetScreenColor(bool CorrectAnswer)
{
	if (CorrectAnswer == 1)
				system("color 2F");
			else
				system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz &Quizz,short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Wrong Answer :-(\n";
		cout << "The Right Answer Is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	
	}
	else
		{
			Quizz.QuestionList[QuestionNumber].AnswerResult = true;
			Quizz.NumberOfRightAnswers++;
			cout << "Corrcet Answer :-)\n";
			
		}

	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionAsnwers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

string GetFinalResultText(bool isPass)
{
	if (isPass)
		return "Pass :-)\n";
	else 
		return "Fail :-(\n";
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string QLevel[4] = { "Easy", "Med", "Hard", "Mix" };
	return QLevel[QuestionLevel - 1];
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "_______________________________________________________________" << endl << endl;
	
	cout << "Final Result is" << GetFinalResultText(Quizz.isPass);
	cout << "_______________________________________________________________" << endl << endl;
	
	cout << "Number Of Questions:             " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level:                 " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operation Type:                  " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Correct Answers:       " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers:         " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n_______________________________________________________________";
	EndGameScreenColor(Quizz.isPass);
}

void PlayMathGame()
{
	stQuizz Quizz;
	
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionAsnwers(Quizz);
	PrintQuizzResults(Quizz);
}
void StartGame()
{

	char PlayAgain = 'Y';
	do
	{

		ResetScreen();
		PlayMathGame();
		

		cout << "\nDo You Want To Play Again? Y/N ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}
int main()
{
	srand(unsigned(time(NULL)));

	StartGame();
	return 0;
}
