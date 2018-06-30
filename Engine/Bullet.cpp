#include "Bullet.h"

void Bullet::Init(Vec2 playerLoc, float in_orientation, Vec2 playerMoveSpeed)
{
	loc = playerLoc;

	Vec2 a = { playerLoc.x - 0.2f, playerLoc.y - 0.2f };
	Vec2 b = { playerLoc.x + 0.2f, playerLoc.y - 0.2f };
	Vec2 c = { playerLoc.x + 0.2f, playerLoc.y + 0.2f };
	Vec2 d = { playerLoc.x - 0.2f, playerLoc.y + 0.2f };

	rect.Init(a, b, c, d, Colors::Green);

	rect.triangles[0].orientation = in_orientation;
	rect.triangles[1].orientation = in_orientation;

	moveSpeed = playerMoveSpeed;
}

void Bullet::Move()
{
	rect.Move({ moveSpeed.x, moveSpeed.y - speed });
}

bool Bullet::IsAliveOnUpdate()
{
	lifeSpan += 1.0f;
	if (lifeSpan >= lifeSpanMax)
	{
		return false;
	}

	return true;
}

bool Bullet::IsAtLocation(Vec2 cameraViewLoc)
{
	return rect.IsAtLocation(cameraViewLoc);
}

Color Bullet::GetColor()
{
	return rect.color;
}

bool Bullet::CheckCollision(Asteroid& asteroid)
{
	if (rect.topLeft.x < asteroid.GetBR().x
		&& rect.topLeft.y < asteroid.GetBR().y
		&& rect.botRight.x > asteroid.GetTL().x
		&& rect.botRight.y > asteroid.GetTL().y)
	{
		return true;
	}

	return false;
}
