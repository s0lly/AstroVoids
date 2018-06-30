#pragma once

#include "MainWindow.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Rect.h"
#include <vector>


class World
{
public:

	void Init(Vec2 in_loc);

	void Update();

	bool IsPlayerCollided();

	Color GetObjectColor(Vec2 cameraViewLoc);

	void MovePlayerObject(Vec2 distance);
	void ScalePlayerObject(float scale);
	void RotatePlayerObject(float angle);

	void MoveAsteroid(int asteroidNum);
	void ScaleAsteroid(int asteroidNum, float scale);
	void RotateAsteroid(int asteroidNum, float angle);


	void CreateBullet(Vec2 playerMoveSpeed);

	int GetScore();



	static constexpr float width = 120.0f;
	static constexpr float height = 180.0f;

	float widthCurrentStart = 0.0f;
	float widthCurrentEnd = width;

	float heightCurrentStart = 0.0f;
	float heightCurrentEnd = height;

	static constexpr float wallSpeedX = 0.0065f * width / 100.0f;
	static constexpr float wallSpeedY = 0.0065f * height / 100.0f;


private:

	




	// world objects

	Rect rectBorderLeft;
	Rect rectBorderRight;
	Rect rectBorderTop;
	Rect rectBorderBot;

	//Rect rect;
	//Rect rect2;
	//Circle circle;

	Triangle playerTriangle;
	bool playerHasCollided = false;

	//std::vector<WorldObject> worldObjects;

	std::vector<Asteroid> asteroids;
	static constexpr int maxAsteroids = 1;

	std::vector<Bullet> bullets;
	static constexpr int maxBullets = 20;

	float spawnCounter = 0.0f;
	float spawnCounterTick = 1.0f;
	float spawnCounterMax = 500.0f;



	int score = 0;


};