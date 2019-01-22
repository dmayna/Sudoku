#include "pch.h"
#include "Levels.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <Windows.h>
using namespace std;

Levels::Levels()
{
	filename = "sudokuVeryEasy.txt";
	scoreFilename = "veryEasyScore.txt";
	playing = true;
	score = 100;
	average = getAverage();
}

void Levels::loadGrid(void)
{
	// create file object
	ifstream file(filename);
	string line = "";
	int index = 0;
	int answerIndex = 0;
	// read file one line at a time ignoring the comma
	while (getline(file, line, ','))
	{
		// allow string to be read one word at a time
		stringstream lineStream(line);
		// string to hold word from line
		string cell;
		// iterate through the line and store cell in vector
		while (getline(lineStream, cell))
		{
			index++;
			if (index > gridNumBegin && index <= gridNumEnd)
			{
				//cout << cell << " | " << index << "\n";
				mAnswer_Row.clear();
				for (auto i = cell.begin(); i != cell.end(); i++)
				{
					if (*i == '0')
					{
						mAnswer_Row.push_back(pair<string, char>("Answer", *i));
					}
					else
					{
						mAnswer_Row.push_back(pair<string, char>("Grid", *i));
					}
				}
				mAnswer_Grid.push_back(mAnswer_Row);
			}
			else if (index <= answerNumEnd && index > answerNumBegin)
			{
				int s = 0;
				for (auto it = cell.begin(); it != cell.end(); it++)
				{
					if (mAnswer_Grid[answerIndex][s].second == '0')
					{
						mAnswer_Grid[answerIndex][s].second = *it;
					}
					s++;
				}
				answerIndex++;
			}
		}
		cout << "\n";
	}
	file.close();
}

void Levels::selectGrid(void)
{
	// select correct file name baased on difficulty
	// select random grids file
	srand(time(NULL));
	int randomNumber = std::rand() % 10;
	if (randomNumber == 0)
	{
		gridNumBegin = (9 * randomNumber) + 1;
		gridNumEnd = 9 * (randomNumber + 1);
		answerNumBegin = 9 * (randomNumber + 1);
		answerNumEnd = 9 * (randomNumber * +2);
	}
	else
	{
		gridNumBegin = 9 * (randomNumber * 2);
		gridNumEnd = 9 * ((randomNumber * 2) + 1);
		answerNumBegin = 9 * ((randomNumber * 2) + 1);
		answerNumEnd = 9 * ((randomNumber * 2) + 2);
	}
	loadGrid();
	printAnswer();
}

void Levels::prindHorizontalBorder(void)
{
	char border = 205;
	for (int i = 0; i < 35; i++)
	{
		cout << border;
	}
}

void Levels::printGrid(void)
{
	system("CLS");
	int horizontalIndex = 0;
	// used to keep track of columns to print correct border
	int verticalIndex;
	cout << char(201); prindHorizontalBorder(); cout << char(187) << "\n";
	for (auto i = mAnswer_Grid.begin(); i != mAnswer_Grid.end(); i++)
	{
		verticalIndex = 1;
		cout << char(186) << " ";
		for (auto j = i->begin(); j != i->end(); j++)
		{
			//cout << char(186) << " ";
			if (j->first == "Grid")
			{
				SetColor(1);
				cout << j->second << " ";
				SetColor(7);
			}
			else if (j->first == "userAnswer")
			{
				SetColor(2);
				cout << j->second << " ";
				SetColor(7);
			}
			else
			{
				cout << "  ";
			}
			if (verticalIndex % 3 == 0)
			{
				cout << char(186) << " ";
			}
			else
			{
				cout << "| ";
			}
			verticalIndex++;
		}
		cout << "\n";
		horizontalIndex++;
		//print border for middle rows
		if (horizontalIndex % 3 == 0 && horizontalIndex != 9)
		{
			cout << char(204); prindHorizontalBorder(); cout << char(185) << "\n";
		}
	}
	cout << char(200); prindHorizontalBorder(); cout << char(188) << "\n";
}

void Levels::printAnswer(void)
{
	// used to keep track of rows to print correct border
	int horizontalIndex = 0;
	// used to keep track of columns to print correct border
	int verticalIndex;
	cout << char(201); prindHorizontalBorder(); cout << char(187) << "\n";
	for (auto i = mAnswer_Grid.begin(); i != mAnswer_Grid.end(); i++)
	{
		verticalIndex = 1;
		cout << char(186) << " ";
		for (auto j = i->begin(); j != i->end(); j++)
		{
			//cout << char(186) << " ";
			if (j->first == "Grid")
			{
				SetColor(1);
				cout << j->second << " ";
				SetColor(7);
			}
			else
			{
				SetColor(2);
				cout << j->second << " ";
				SetColor(7);
			}
			if (verticalIndex % 3 == 0)
			{
				cout << char(186) << " ";
			}
			else
			{
				cout << "| ";
			}
			verticalIndex++;
		}
		cout << "\n";
		horizontalIndex++;
		//print border for middle rows
		if (horizontalIndex % 3 == 0 && horizontalIndex != 9)
		{
			cout << char(204); prindHorizontalBorder(); cout << char(185) << "\n";
		}
	}
	cout << char(200); prindHorizontalBorder(); cout << char(188) << "\n";
}

void Levels::playGame(void)
{
	while (playing)
	{
		if (endOfGame())
		{
			if (score == 100)
			{
				cout << "Excellent Player, should try next level\n";
			}
			if (score >= 80 && score < 100)
			{
				cout << " Good player, keep practicing on this level\n";
			}
			if (score >= 60 && score < 80)
			{
				cout << "OK player... keep practicing on this level if you dare\n";
			}
			if (score >= 40 && score < 60)
			{
				cout << "Well.. suggest trying a easier level\n";
			}
			if (score < 40)
			{
				cout << "Watch this video on how to play\n";
			}
			// add score to file for correct level and increment games played variable
			ifstream fin(scoreFilename);
			int gameScoreTotal;
			int gamesPlayed;
			while (fin >> gameScoreTotal >> gamesPlayed)
			{
				gameScoreTotal += score;
				gamesPlayed++;
			}
			average = gameScoreTotal / gamesPlayed;
			// write new total score and games played into file
			ofstream fout(scoreFilename);
			fout << gameScoreTotal << " " << gamesPlayed;
			playing = false;
			break;
		}
		cout << "\n\nScore = " << score;
		cout << "\nEnter 'kill' into grid to quit game\n";
		cout << "Enter 'new' into grid to start a new game\n";
		cout << "Enter the Row and Column number of the box you would like to fill >";
		int choiceRow, choiceCol;
		cin >> choiceRow;
		cin >> choiceCol;
		while (cin.fail() || choiceRow > 9 || choiceCol > 9 || choiceRow < 1 || choiceCol < 1)
		{
			cout << "Error please enter a Row and Column number between 1-9 > ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> choiceRow;
			cin >> choiceCol;
		}
		// if the spot is taken already then alert user and ask again
		while (mAnswer_Grid[choiceRow - 1][choiceCol - 1].first == "Grid" || choiceRow > 9 || choiceCol > 9 || choiceRow < 1 || choiceCol < 1 || mAnswer_Grid[choiceRow - 1][choiceCol - 1].first == "userAnswer")
		{
			cout << "Spot Already Taken! Enter a new Row and Column >";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> choiceRow;
			cin >> choiceCol;
		}
		// otherwise ask user for input into grid
		string userAnswer;
		cout << "Enter  number to enter into grid >";
		// check if user answer is valid
		cin >> userAnswer;
		if (userAnswer == "kill")
		{
			mAnswer_Row.clear();
			mAnswer_Grid.clear();
			exit(1);
		}
		if (userAnswer == "new")
		{
			mAnswer_Row.clear();
			mAnswer_Grid.clear();
			break;
		}
		// if the answer is correct alert user and change the key
		if (mAnswer_Grid[choiceRow - 1][choiceCol - 1].second == userAnswer[0])
		{
			cout << "Correct input\n";
			mAnswer_Grid[choiceRow - 1][choiceCol - 1].first = "userAnswer";
			printGrid();
		}
		else
		{
			// otherwise subtract points 
			// add algorithm fo find correct spot on the grid to blink error
			int row = 0;
			int col = 0;
			if (choiceRow <= 3)
			{
				row = choiceRow;
			}
			if (choiceRow > 3)
			{
				row = choiceRow + 1;
			}
			if (choiceRow > 6)
			{
				row++;
			}
			// find correct col position
			if (choiceCol <= 1)
			{
				col = choiceCol + 3;
			}
			if (choiceCol <= 3)
			{
				col = (choiceCol * 3) + (choiceCol - 2);
			}
			if (choiceCol > 3)
			{
				col = (choiceCol * 3) + (choiceCol - 2);
			}
			// flash error
			blink(userAnswer, 4, 0, col, row);
			system("CLS");
			printGrid();
			cout << "-5 Wrong Answer\n";
			score -= 5;
			cout << "Current Score = " << score;
		}
	}
}

bool Levels::endOfGame(void)
{
	if (score == 0)
	{
		return true;
	}
	for (auto i = mAnswer_Grid.begin(); i != mAnswer_Grid.end(); i++)
	{
		for (auto j = i->begin(); j != i->end(); j++)
		{
			if (j->first == "Answer")
			{
				return false;
			}
		}
	}
	return true;
}

void Levels::blink(string attempt, int ForgC, int BackC = 0, int row = 0, int col = 0)
{
	COORD	pos = { row,col };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	for (int i = 0; i < 5; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ForgC | (BackC << 4));
		cout << attempt;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		Sleep(100);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BackC | (ForgC << 4));
		cout << attempt;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		Sleep(100);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (BackC << 0));
	}
}

void Levels::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

double Levels::getAverage(void)
{
	int total;
	int games;
	ifstream fin(scoreFilename);
	fin >> total >> games;
	if (total == 0 || games == 0)
	{
		return 0;
	}
	else
	{
		return total / games;
	}
}
