#pragma once

#include "Asteroid.h"
#include "Vec2.h"
#include "Rect.h"

class Bullet
{
public:

	void Init(Vec2 playerLoc, float in_orientation, Vec2 playerMoveSpeed);

	void Move();

	bool IsAliveOnUpdate();

	bool IsAtLocation(Vec2 cameraViewLoc);

	Color GetColor();

	bool CheckCollision(Asteroid& asteroid);

private:

	Vec2 loc;

	Rect rect;

	Vec2 moveSpeed = { 0.0f, 0.0f };

	float speed = 2.0f;

	float lifeSpan = 0.0f;
	float lifeSpanMax = 80.0f;
};