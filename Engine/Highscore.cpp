#include "Highscore.h"
#include <iostream>
#include <iomanip>
#include <fstream>

void Highscore::Init()
{
	std::ifstream txtHighScore;

	txtHighScore.open("highscore.txt");
	if (!txtHighScore)
	{
		highScore = 0;
	}
	else
	{
		txtHighScore >> highScore;
	}

	txtHighScore.close();

}


void Highscore::Update(int in_score)
{
	if (in_score > highScore)
	{
		highScore = in_score;
	}

}

void Highscore::Save(int in_score)
{
	if (in_score >= highScore)
	{
		std::ofstream myfile;
		myfile.open("highscore.txt");

		myfile << in_score;

		myfile.close();
	}
}

int Highscore::Get()
{
	return highScore;
}
