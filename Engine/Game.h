/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Bullet.h"
#include "RetroContent.h"
#include "Sound.h"
#include "Highscore.h"
#include <string>
#include <sstream>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	bool Go();
private:

	void ProcessInput();
	void UpdateModel();
	void ComposeFrame();


private:
	MainWindow& wnd;
	Graphics gfx;


	Player player;

	World world;

	Sound musicSound;
	Sound musicStartSound;

	Camera worldCamera;
	Camera playerCamera;

	Highscore highscore;

	bool spaceIsPressed = false;
	bool highscoreIsSaved = false;

	bool gameStarted = false;
	bool gameRunning = false;
	bool gameQuit = false;

	float masterVolume = 0.3f;
	float masterVolumeMin = 0.001f;
	float masterVolumeMax = 0.3f;

	bool transitionGameStart = false;
	float transitionGameStartCounter = 0.0f;
	float transitionGameStartCounterTick = 1.0f;
	float transitionGameStartCounterMax = 100.0f;


};