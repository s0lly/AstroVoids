#include "Asteroid.h"


void Asteroid::Init(Vec2 a, float r, Color in_c, Vec2 in_moveSpeed)
{
	circle.Init(a, r, in_c);
	moveSpeed = in_moveSpeed;
}

void Asteroid::Move()
{
	circle.Move(moveSpeed);
}

void Asteroid::Scale(float scale)
{
	circle.Scale(scale);
}

void Asteroid::Rotate(float angle)
{
	circle.Rotate(angle);
}

void Asteroid::undoMove()
{
	circle.Move({ -moveSpeed.x,-moveSpeed.y });
}

bool Asteroid::IsAtLocation(Vec2 loc)
{
	return circle.IsAtLocation(loc);
}

float Asteroid::GetRadius()
{
	return circle.radius;
}

Vec2 Asteroid::GetLoc()
{
	return circle.mid;
}

float Asteroid::GetOrientation()
{
	return circle.orientation;
}

Color Asteroid::GetColor()
{
	return circle.color;
}

bool Asteroid::CheckCollision(Vec2 playerTL, Vec2 playerBR)
{
	if (playerTL.x < GetBR().x
		&& playerTL.y < GetBR().y
		&& playerBR.x > GetTL().x
		&& playerBR.y > GetTL().y)
	{
		return true;
	}

	return false;
}

void Asteroid::SetOrientation(float in_orient)
{
	circle.orientation = in_orient;
}

void Asteroid::SetMoveSpeedX(float a)
{
	moveSpeed.x = a;
}

void Asteroid::SetMoveSpeedY(float a)
{
	moveSpeed.y = a;
}

float Asteroid::GetMoveSpeedX()
{
	return moveSpeed.x;
}

float Asteroid::GetMoveSpeedY()
{
	return moveSpeed.y;
}

Vec2 Asteroid::GetTL()
{
	return circle.topLeft;
}

Vec2 Asteroid::GetBR()
{
	return circle.botRight;
}
