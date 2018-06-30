#include "World.h"

void World::Init(Vec2 in_loc)
{
	rectBorderLeft.Init({ -1.0f, -1.0f }, { 1.0f, -1.0f }, { 1.0f, height + 1.0f }, { -1.0f, height + 1.0f }, Colors::Blue);
	rectBorderRight.Init({ width - 1.0f, -1.0f }, { width + 1.0f, -1.0f }, { width + 1.0f, height + 1.0f }, { width - 1.0f, height + 1.0f }, Colors::Blue);
	rectBorderTop.Init({ -1.0f, -1.0f }, { width + 1.0f, -1.0f }, { width + 1.0f, 1.0f }, { -1.0f, 1.0f }, Colors::Blue);
	rectBorderBot.Init({ -1.0f, height - 1.0f }, { width + 1.0f, height - 1.0f }, { width + 1.0f, height + 1.0f }, { -1.0f, height + 1.0f }, Colors::Blue);


	playerTriangle.Init({ (in_loc.x - 1.0f),(in_loc.y + 1.0f) }, { (in_loc.x),(in_loc.y - 1.0f) }, { (in_loc.x + 1.0f),(in_loc.y + 1.0f) }, Colors::Yellow);


	for (int i = 0; i < maxAsteroids; i++)
	{
		float radius = 20.0f;
		float orientation = 3.14159f / 2;

		asteroids.push_back(Asteroid());
		asteroids[i].Init({ 0.0f - radius, height / 2.0f }, radius, Color(255, 0, 255), { 0.0f, - (1.0f / radius) });
		asteroids[asteroids.size() - 1].SetOrientation(orientation);
	}
}

void World::Update()
{
	// Spawn new asteroid

	if (spawnCounter > spawnCounterMax)
	{
		spawnCounter = 0.0f;

		Vec2 mid = { 0.0f, height / 2.0f };
		float radius = 20.0f;
		float orientation = 3.14159f / 2;

		asteroids.push_back(Asteroid());
		asteroids[asteroids.size() - 1].Init({ mid.x - radius, mid.y }, radius, Color(255, 0, 255), { 0.0f, -(1.0f / radius) });
		asteroids[asteroids.size() - 1].SetOrientation(orientation);
	}
	else
	{
		spawnCounter += spawnCounterTick;
	}


	// Update bullet life

	for (int i = 0; i < bullets.size(); )
	{
		if (!(bullets[i].IsAliveOnUpdate()))
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			i++;
		}
	}


	// Move Objects

	for (int i = 0; i < asteroids.size(); i++)
	{
		MoveAsteroid(i);
	}



	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].Move();
	}

	
	rectBorderLeft.Move({ wallSpeedX, 0.0f });
	rectBorderRight.Move({ -wallSpeedX, 0.0f });
	rectBorderTop.Move({ 0.0f, wallSpeedY });
	rectBorderBot.Move({ 0.0f, -wallSpeedY });


	rectBorderTop.Move({ wallSpeedX, 0.0f });
	rectBorderBot.Move({ wallSpeedX, 0.0f });


	widthCurrentStart += wallSpeedX;
	widthCurrentEnd -= wallSpeedX;

	heightCurrentStart += wallSpeedY;
	heightCurrentEnd -= wallSpeedY;


	// Collision Detection

	// Bullets & Asteroids

	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < asteroids.size(); j++)
		{
			if (bullets[i].CheckCollision(asteroids[j]))
			{
				float radius = asteroids[j].GetRadius();
				Vec2 mid = asteroids[j].GetLoc();
				float orientation = asteroids[j].GetOrientation();

				bullets.erase(bullets.begin() + i);
				asteroids.erase(asteroids.begin() + j);

				if (radius >= 2.1f)
				{
					

					asteroids.push_back(Asteroid());
					asteroids[asteroids.size() - 1].Init({ mid.x - (radius / 2.0f) * cos(orientation), mid.y - (radius / 2.0f) * sin(orientation) }, radius / 2.0f, Color(255, 0, 255), { 0.0f, -(1.0f / radius) });

					float newOrientation1 = orientation - 3.14159f / 6.5;
					newOrientation1 = newOrientation1 < 0.0f ? (2.0f * 3.14159f) + newOrientation1 : newOrientation1;
					newOrientation1 = newOrientation1 >(2.0f * 3.14159f) ? newOrientation1 - (2.0f * 3.14159f) : newOrientation1;

					asteroids[asteroids.size() - 1].SetOrientation(newOrientation1);
					
					asteroids.push_back(Asteroid());
					asteroids[asteroids.size() - 1].Init({ mid.x + (radius / 2.0f) * cos(orientation), mid.y + (radius / 2.0f) * sin(orientation) }, radius / 2.0f, Color(255, 0, 255), { 0.0f, -(1.0f / radius) });

					float newOrientation2 = orientation + 3.14159f / 6.5;
					newOrientation2 = newOrientation2 < 0.0f ? (2.0f * 3.14159f) + newOrientation2 : newOrientation2;
					newOrientation2 = newOrientation2 >(2.0f * 3.14159f) ? newOrientation2 - (2.0f * 3.14159f) : newOrientation2;

					asteroids[asteroids.size() - 1].SetOrientation(newOrientation2);
				}

				i--;
				j = (int)asteroids.size();

				score++;
			}
		}
		
	}

	// Player and Asteroids

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i].CheckCollision(playerTriangle.topLeft, playerTriangle.botRight))
		{
			playerHasCollided = true;
		}
	}

	// Asteroids and Walls

	

	for (int i = 0; i < asteroids.size(); i++)
	{

		if (asteroids[i].CheckCollision(rectBorderLeft.topLeft, rectBorderLeft.botRight))
		{
			if (asteroids[i].GetOrientation() >= (3.14159f) && asteroids[i].GetOrientation() < (3.14159f * 2.0f))
			{
				asteroids[i].undoMove();
				if (asteroids[i].GetOrientation() > (3.14159f * 3.0f / 2.0f))
				{
					asteroids[i].Rotate(((3.14159f * 2.0f) - asteroids[i].GetOrientation()) * 2.0f);
				}
				else
				{
					asteroids[i].Rotate(-(asteroids[i].GetOrientation() - (3.14159f)) * 2.0f);
				}
				
			}
		}
		if (asteroids[i].CheckCollision(rectBorderRight.topLeft, rectBorderRight.botRight))
		{
			asteroids[i].undoMove();
			if (asteroids[i].GetOrientation() < (3.14159f / 2.0f))
			{
				asteroids[i].Rotate((0.0f - asteroids[i].GetOrientation()) * 2);
			}
			else
			{
				asteroids[i].Rotate(((3.14159f) - asteroids[i].GetOrientation()) * 2.0f);
			}
		}

		if (asteroids[i].CheckCollision(rectBorderTop.topLeft, rectBorderTop.botRight))
		{
			asteroids[i].undoMove();
			if (asteroids[i].GetOrientation() < (3.14159f / 2.0f))
			{
				asteroids[i].Rotate(((3.14159f / 2.0f) - asteroids[i].GetOrientation()) * 2);
			}
			else
			{
				asteroids[i].Rotate(((3.14159f * 3.0f / 2.0f) - asteroids[i].GetOrientation()) * 2.0f);
			}
		}
		if (asteroids[i].CheckCollision(rectBorderBot.topLeft, rectBorderBot.botRight))
		{
			asteroids[i].undoMove();
			if (asteroids[i].GetOrientation() < (3.14159f))
			{
				asteroids[i].Rotate(((3.14159f / 2.0f) - asteroids[i].GetOrientation()) * 2);
			}
			else
			{
				asteroids[i].Rotate(((3.14159f * 3.0f / 2.0f) - asteroids[i].GetOrientation()) * 2.0f);
			}
		}
	}

	// Player and Walls
	
	if (playerTriangle.topLeft.x < rectBorderLeft.botRight.x
		|| playerTriangle.botRight.x > rectBorderRight.topLeft.x
		|| playerTriangle.topLeft.y < rectBorderTop.botRight.y
		|| playerTriangle.botRight.y > rectBorderBot.topLeft.y)
	{
		playerHasCollided = true;
	}

}

bool World::IsPlayerCollided()
{
	return playerHasCollided;
}


Color World::GetObjectColor(Vec2 cameraViewLoc)
{
	// cycle through all world objects

	if (playerTriangle.IsAtLocation(cameraViewLoc))
	{
		return playerTriangle.color;
	}


	if (rectBorderLeft.IsAtLocation(cameraViewLoc))
	{
		return rectBorderLeft.color;
	}
	if (rectBorderRight.IsAtLocation(cameraViewLoc))
	{
		return rectBorderRight.color;
	}
	if (rectBorderTop.IsAtLocation(cameraViewLoc))
	{
		return rectBorderTop.color;
	}
	if (rectBorderBot.IsAtLocation(cameraViewLoc))
	{
		return rectBorderBot.color;
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i].IsAtLocation(cameraViewLoc))
		{
			return asteroids[i].GetColor();
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].IsAtLocation(cameraViewLoc))
		{
			return bullets[i].GetColor();
		}
	}


	return Colors::Black;
}

void World::MovePlayerObject(Vec2 distance)
{

	playerTriangle.Move(distance);

}

void World::ScalePlayerObject(float scale)
{
	playerTriangle.Scale(scale);

}

void World::RotatePlayerObject(float angle)
{
	playerTriangle.Rotate(angle);
}


void World::MoveAsteroid(int asteroidNum)
{
	asteroids[asteroidNum].Move();
}

void World::ScaleAsteroid(int asteroidNum, float scale)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Scale(scale);
	}

}

void World::RotateAsteroid(int asteroidNum, float angle)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Rotate(angle);
	}
}

void World::CreateBullet(Vec2 playerMoveSpeed)
{
	if (bullets.size() < maxBullets)
	{
		bullets.push_back(Bullet());
		bullets[bullets.size() - 1].Init(playerTriangle.centroid, playerTriangle.orientation, playerMoveSpeed);
	}
}

int World::GetScore()
{
	return score;
}
