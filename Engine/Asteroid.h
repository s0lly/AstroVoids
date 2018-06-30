#pragma once

#include "MainWindow.h"
#include "Rect.h"
#include <vector>

class Asteroid
{
public:
	void Init(Vec2 a, float r, Color in_c, Vec2 in_moveSpeed);

	void Move();
	void Scale(float scale);
	void Rotate(float angle);

	void undoMove();

	bool IsAtLocation(Vec2 loc);

	float GetRadius();
	Vec2 GetLoc();
	
	Color GetColor();

	bool CheckCollision(Vec2 playerTL, Vec2 playerBR);

	float GetOrientation();
	void SetOrientation(float in_orient);

	float GetMoveSpeedX();
	float GetMoveSpeedY();

	void SetMoveSpeedX(float a);
	void SetMoveSpeedY(float a);

	Vec2 GetTL();
	Vec2 GetBR();

private:

	Circle circle;

	Vec2 moveSpeed = { 0.0f, 0.0f };


};