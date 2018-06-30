#pragma once
#include "Graphics.h"

class Highscore
{
public:

	void Init();

	void Update(int in_score);

	void Save(int in_score);

	int Get();



private:

	int highScore = 0;


};