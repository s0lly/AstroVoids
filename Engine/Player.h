#pragma once
#include "Rect.h"
#include "World.h"
#include "Bullet.h"
#include "Camera.h"


class Player
{
public:

	void Init(Vec2 in_loc);

	void Update(World& world, Camera& playerCamera);

	void Accelerate();
	void Break();
	void RotateLeft();
	void RotateRight();
	void RotateCancel();

	void ShootBullet(World& world);


	void Move(World& world, Camera& playerCamera, Vec2 distance);

	void Scale(World& world, Camera& playerCamera, float scale);

	void Rotate(World& world, Camera& playerCamera, float angle);


private:

	Vec2 loc;
	Vec2 moveSpeed;
	float rotateSpeed;

	float accelerationSpeedChange = 0.04f;
	float breakSpeedChange = 0.02f;

	float maxAcceleration = 1.6f;

	float RotateSpeedChange = 0.08f;

	float accelerationAtrophy = 0.01f;

	
};