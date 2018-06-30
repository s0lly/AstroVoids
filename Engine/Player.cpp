#include "Player.h"

void Player::Init(Vec2 in_loc)
{
	loc = in_loc;
	moveSpeed = { 0.0f, 0.0f };
	rotateSpeed = 0.0f;
}

void Player::Update(World & world, Camera & playerCamera)
{

	Rotate(world, playerCamera, rotateSpeed);
	Move(world, playerCamera, moveSpeed);
	

	if (moveSpeed.x > 0.0f)
	{
		moveSpeed.x -= accelerationAtrophy;
	}
	if (moveSpeed.x < 0.0f)
	{
		moveSpeed.x += accelerationAtrophy;
	}
	if (moveSpeed.y > 0.0f)
	{
		moveSpeed.y -= accelerationAtrophy;
	}
	if (moveSpeed.y < 0.0f)
	{
		moveSpeed.y += accelerationAtrophy;
	}

}

void Player::Accelerate()
{
	moveSpeed.y -= accelerationSpeedChange;

	moveSpeed.y = moveSpeed.y < -maxAcceleration ? -maxAcceleration : moveSpeed.y;
}

void Player::Break()
{
	//if (moveSpeed.x > 0.0f)
	//{
	//	moveSpeed.x -= breakSpeedChange;
	//}
	//if (moveSpeed.x < 0.0f)
	//{
	//	moveSpeed.x += breakSpeedChange;
	//}
	//if (moveSpeed.y > 0.0f)
	//{
	//	moveSpeed.y -= breakSpeedChange;
	//}
	//if (moveSpeed.y < 0.0f)
	//{
	//	moveSpeed.y += breakSpeedChange;
	//}

	moveSpeed.y += accelerationSpeedChange;

	moveSpeed.y = moveSpeed.y > +maxAcceleration ? +maxAcceleration : moveSpeed.y;

}

void Player::RotateLeft()
{
	rotateSpeed = -RotateSpeedChange;

	moveSpeed.x = cos(rotateSpeed) * moveSpeed.x + sin(rotateSpeed) * moveSpeed.y;
	moveSpeed.y = -sin(rotateSpeed) * moveSpeed.x + cos(rotateSpeed) * moveSpeed.y;
}

void Player::RotateRight()
{
	rotateSpeed = RotateSpeedChange;

	moveSpeed.x = cos(rotateSpeed) * moveSpeed.x + sin(rotateSpeed) * moveSpeed.y;
	moveSpeed.y = -sin(rotateSpeed) * moveSpeed.x + cos(rotateSpeed) * moveSpeed.y;
}

void Player::RotateCancel()
{
	rotateSpeed = 0.0f;
}

void Player::ShootBullet(World& world)
{
	world.CreateBullet(moveSpeed);
}

void Player::Move(World& world, Camera& playerCamera, Vec2 distance)
{

	world.MovePlayerObject(distance);
	

	if (distance.y > 0.0f)
	{
		playerCamera.Modify(CameraAction::MoveDown, abs(distance.y));
	}
	if (distance.y < 0.0f)
	{
		playerCamera.Modify(CameraAction::MoveUp, abs(distance.y));
	}
	if (distance.x > 0.0f)
	{
		playerCamera.Modify(CameraAction::MoveRight, abs(distance.x));
	}
	if (distance.x < 0.0f)
	{
		playerCamera.Modify(CameraAction::MoveLeft, abs(distance.x));
	}
	

}

void Player::Scale(World & world, Camera & playerCamera, float scale)
{
	world.ScalePlayerObject(scale);
}

void Player::Rotate(World & world, Camera & playerCamera, float angle)
{
	world.RotatePlayerObject(angle);

	if (angle > 0.0f)
	{
		playerCamera.Modify(CameraAction::TurnRight, abs(angle));
	}
	if (angle < 0.0f)
	{
		playerCamera.Modify(CameraAction::TurnLeft, abs(angle));
	}

}

