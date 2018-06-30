/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	musicSound(L"06 Searching.wav"),
	musicStartSound(L"02 Underclocked.wav")
{

	Vec2 worldCenter = { world.width / 2.0f, world.height / 2.0f };
	Vec2 playerCentroid = { ((worldCenter.x - 1.0f) + (worldCenter.x) + (worldCenter.x + 1.0f)) / 3.0f, ((worldCenter.y + 1.0f) + (worldCenter.y - 1.0f) + (worldCenter.y + 1.0f)) / 3.0f };

	player.Init(playerCentroid);
	world.Init(worldCenter);

	worldCamera.Init({ world.width / 2, world.height / 2 }, world.width, world.height, 0.0f);
	playerCamera.Init(playerCentroid, world.width, world.height, 0.0f);

	musicStartSound.Play(1.0f, masterVolumeMax);
	SoundSystem::SetMasterVolume(masterVolume);

	highscore.Init();

}

bool Game::Go()
{
	gfx.BeginFrame();

	ProcessInput();
	UpdateModel();
	ComposeFrame();

	gfx.EndFrame();

	return gameQuit;
}



void Game::ProcessInput()
{
	if (gameStarted)
	{
		if (gameRunning)
		{

			// Modify Player

			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				player.Accelerate();
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				player.Break();
			}

			bool isRotating = false;
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				player.RotateLeft();
				isRotating = true;
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				player.RotateRight();
				isRotating = true;
			}
			if (!isRotating)
			{
				player.RotateCancel();
			}


			if (wnd.kbd.KeyIsPressed('R'))
			{
				playerCamera.Modify(CameraAction::ZoomIn, 1.0f);

			}
			if (wnd.kbd.KeyIsPressed('F'))
			{
				playerCamera.Modify(CameraAction::ZoomOut, 1.0f);

			}


			// Shooting

			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				if (!spaceIsPressed)
				{
					player.ShootBullet(world);
				}
				spaceIsPressed = true;
			}
			else
			{
				spaceIsPressed = false;
			}


			// Select Camera

			if (wnd.kbd.KeyIsPressed('M'))
			{
				playerCamera.TurnOff();
				worldCamera.TurnOn();
			}
			else
			{
				playerCamera.TurnOn();
				worldCamera.TurnOff();
			}


		}
		else // game over
		{
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				gameQuit = true;
			}
		}
	}
	else // game has not started
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			transitionGameStart = true;
			
		}

	}

}

void Game::UpdateModel()
{
	if (gameStarted)
	{
		if (gameRunning)
		{
			player.Update(world, playerCamera);
			world.Update();

			gameRunning = !(world.IsPlayerCollided());

			highscore.Update(world.GetScore());
		}
		else // game over
		{

			masterVolume = masterVolume * 0.98f;

			if (masterVolume < 0.001f)
			{
				masterVolume = 0.001f;
			}

			SoundSystem::SetMasterVolume(masterVolume);

			if (!highscoreIsSaved)
			{
				highscore.Save(world.GetScore());
				highscoreIsSaved = true;
			}
		}
	}
	else // game has not started
	{
		if (transitionGameStart)
		{
			transitionGameStartCounter += transitionGameStartCounterTick;

			masterVolume = masterVolume * 0.98f;
			SoundSystem::SetMasterVolume(masterVolume);
		}
		if (transitionGameStartCounter >= transitionGameStartCounterMax)
		{
			gameStarted = true;
			gameRunning = true;

			SoundSystem::SetMasterVolume(masterVolumeMax);
			masterVolume = masterVolumeMax;

			musicStartSound.StopAll();
			musicSound.Play(1.0f, masterVolume);

		}
	}

}

void Game::ComposeFrame()
{

	if (gameStarted)
	{
		if (gameRunning)
		{
			playerCamera.DrawView(gfx, world);
			worldCamera.DrawView(gfx, world);
		}
		else // game over
		{
			int score = world.GetScore();

			std::stringstream scoreStringStream;
			scoreStringStream << score;

			std::string scoreString = scoreStringStream.str();

			int high = highscore.Get();

			std::stringstream highStringStream;
			highStringStream << high;

			std::string highString = highStringStream.str();

			RetroContent::DrawString(gfx, "GAME OVER", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 2 / 10 }, 6, Color(255, 0, 255));

			RetroContent::DrawString(gfx, "YOUR SCORE WAS", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 5 / 10 }, 2, Color(0, 255, 255));
			RetroContent::DrawString(gfx, scoreString, { gfx.ScreenWidth / 2, gfx.ScreenHeight * 11 / 20 }, 2, Color(0, 255, 255));

			RetroContent::DrawString(gfx, "THE HIGHSCORE IS", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 6 / 10 }, 2, Color(0, 255, 255));
			RetroContent::DrawString(gfx, highString, { gfx.ScreenWidth / 2, gfx.ScreenHeight * 13 / 20 }, 2, Color(0, 255, 255));

			RetroContent::DrawString(gfx, "PRESS ENTER TO QUIT", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 8 / 10 }, 2, Colors::Red);
		}
	}
	else // game has not started
	{
		RetroContent::DrawString(gfx, "ASTROVOIDS", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 1 / 20 }, (3 * transitionGameStartCounter / 5 > 5 ? 3 * transitionGameStartCounter / 5 : 5), Color(255, 0, 255));
		
		if (transitionGameStartCounter == 0)
		{
			int high = highscore.Get();

			std::stringstream highStringStream;
			highStringStream << high;

			std::string highString = highStringStream.str();

			RetroContent::DrawString(gfx, "BY", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 6 / 40 }, 2, Color(255, 0, 255));
			RetroContent::DrawString(gfx, "SOLLY", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 8 / 40 }, 2, Color(255, 0, 255));

			RetroContent::DrawString(gfx, "YOU CANNOT ESCAPE THE VOID SANDWICH", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 14 / 40 }, 1, Color(0, 255, 255));
			RetroContent::DrawString(gfx, "BUT FIGHT ON YOU MUST", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 15 / 40 }, 1, Color(0, 255, 255));
			
			RetroContent::DrawString(gfx, "AVOID THE COLLAPSING WALLS", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 19 / 40 }, 1, Color(0, 255, 255));
			RetroContent::DrawString(gfx, "AND BLAST AWAY THE VOID", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 20 / 40 }, 1, Color(0, 255, 255));

			RetroContent::DrawString(gfx, "UNTIL THE BITTER END", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 22 / 40 }, 2, Colors::Yellow);

			RetroContent::DrawString(gfx, "CURRENT HIGHSCORE", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 26 / 40 }, 1, Color(0, 255, 255));
			RetroContent::DrawString(gfx, highString, { gfx.ScreenWidth / 2, gfx.ScreenHeight * 27 / 40 }, 2, Color(0, 255, 255));

			RetroContent::DrawString(gfx, "PRESS ENTER TO BEGIN", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 32 / 40 }, 2, Colors::Red);

			RetroContent::DrawString(gfx, "CONTROL YOUR SPACESHIP WITH", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 36 / 40 }, 1, Colors::White);
			RetroContent::DrawString(gfx, "THE ARROW KEYS AND SPACEBAR", { gfx.ScreenWidth / 2, gfx.ScreenHeight * 37 / 40 }, 1, Colors::White);
		}
	}

}
