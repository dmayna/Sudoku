#pragma once
#include "VeryEasyLevel.h"
#include "EasyLevel.h"
#include "MediumLevel.h"
#include "HardLevel.h"

class SudokuClass
{
public:
	SudokuClass();
	void showAverages(void);
	void startGame(void);
private:
	int difficultyLevel;
	VeryEasyLevel * veryEasyLevel;
	EasyLevel * easyLevel;
	MediumLevel * mediumLevel;
	HardLevel * hardLevel;
};

