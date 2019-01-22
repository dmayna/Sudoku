#include "pch.h"
#include "SudokuClass.h"
#include <iostream>
#include <string>
using namespace std;

SudokuClass::SudokuClass()
{
	veryEasyLevel = new VeryEasyLevel;
	easyLevel = new EasyLevel;
	mediumLevel = new MediumLevel;
	hardLevel = new HardLevel;
}

void SudokuClass::startGame()
{
	int choice;
	cout << "1. Very Easy\n2. Easy\n3. Medium\n4. Hard\n5. Show Average Scores\n";
	cout << "Enter number to select difficulty > ";
	cin >> choice;
	while (cin.fail() || choice > 5)
	{
		cout << "Error please enter a number between 1-5 > ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice;
	}
	difficultyLevel = choice;

	if (difficultyLevel == 1)
	{
		veryEasyLevel->selectGrid();
		veryEasyLevel->printGrid();
		veryEasyLevel->playGame();
	}
	else if (difficultyLevel == 2)
	{
		easyLevel->selectGrid();
		easyLevel->printGrid();
		easyLevel->playGame();
	}
	else if (difficultyLevel == 3)
	{
		mediumLevel->selectGrid();
		mediumLevel->printGrid();
		mediumLevel->playGame();
	}
	else if (difficultyLevel == 4)
	{
		hardLevel->selectGrid();
		hardLevel->printGrid();
		hardLevel->playGame();
	}
	else if (difficultyLevel == 5)
	{
		showAverages();
	}
	string playAgain;
	cout << "\n\nWould you like to play again ? (Enter 'yes' to play again or anything else to quit) > ";
	cin >> playAgain;
	if (playAgain == "yes")
	{
		cin.clear();
		SudokuClass();
		startGame();
	}
}

void SudokuClass::showAverages()
{
	cout << "\n\nAverage Scores per Level\n";
	cout << "Very Easy: " << veryEasyLevel->getAverage();
	cout << "\nEasy: " << easyLevel->getAverage();
	cout << "\nMedium: " << mediumLevel->getAverage();
	cout << "\nHard: " << hardLevel->getAverage();
	cout << "\n\nPress Start when you're ready to start a game!\n";
	system("PAUSE");
	cin.clear();
	SudokuClass();
	startGame();
}

