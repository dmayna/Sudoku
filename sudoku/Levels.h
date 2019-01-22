#pragma once
#include <vector>
using namespace std;
class Levels
{
public:
	Levels(void);
	Levels(string inFile) { filename = inFile; }
	virtual void selectGrid(void);
	void loadGrid(void);
	void printGrid(void);
	void printAnswer(void);
	void prindHorizontalBorder(void);
	void playGame(void);
	bool endOfGame(void);
	void blink(string, int, int, int, int);
	void SetColor(int color);
	double getAverage(void);
protected:
	vector<pair<string, char>> mAnswer_Row;
	vector<vector<pair<string, char>>> mAnswer_Grid;
	string filename;
	bool playing;
	int score;
	int gridNumBegin;
	int gridNumEnd;
	int answerNumBegin;
	int answerNumEnd;
	double average;
	string scoreFilename;
};

