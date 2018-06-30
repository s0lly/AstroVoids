#include "Camera.h"

void Camera::Init(Vec2 in_pos, float startWidth, float startHeight, float startOrientation)
{
	pos = in_pos;

	width = startWidth;
	height = startHeight;

	orientation = startOrientation;
	cosOrient = cos(orientation);
	sinOrient = sin(orientation);

}

void Camera::Modify(CameraAction action, float changeValue)
{

	if (action == CameraAction::MoveLeft)
	{
		pos.x = pos.x - changeValue * cosOrient;
		pos.y = pos.y - changeValue * sinOrient;
	}
	if (action == CameraAction::MoveRight)
	{
		pos.x = pos.x + changeValue * cosOrient;
		pos.y = pos.y + changeValue * sinOrient;
	}
	if (action == CameraAction::MoveUp)
	{
		pos.y = pos.y - changeValue * cosOrient;
		pos.x = pos.x - changeValue * (-sinOrient);
	}
	if (action == CameraAction::MoveDown)
	{
		pos.y = pos.y + changeValue * cosOrient;
		pos.x = pos.x + changeValue * (-sinOrient);
	}
	
	
	if (action == CameraAction::ZoomIn)
	{
		width = width - 0.16f;
		height = height - 0.09f;
	}
	if (action == CameraAction::ZoomOut)
	{
		width = width + 0.16f * changeValue;
		height = height + 0.09f * changeValue;
	}
	
	
	if (action == CameraAction::TurnLeft)
	{
		orientation = orientation - changeValue;
		cosOrient = cos(orientation);
		sinOrient = sin(orientation);
	}
	if (action == CameraAction::TurnRight)
	{
		orientation = orientation + changeValue;
		cosOrient = cos(orientation);
		sinOrient = sin(orientation);
	}

}

void Camera::DrawView(Graphics& gfx, World& world)
{
	if (drawMode)
	{
		for (int j = 0; j < gfx.ScreenHeight; j++)
		{
			for (int i = 0; i < gfx.ScreenWidth; i++)
			{
				float widthCalc = (width * ((float)i / (float)gfx.ScreenWidth) - width * 0.5f);
				float heightCalc = (height * ((float)j / (float)gfx.ScreenHeight) - height * 0.5f);

				Vec2 pixelToWorld =
				{
					pos.x + widthCalc * cosOrient - heightCalc * sinOrient,
					pos.y + widthCalc * sinOrient + heightCalc * cosOrient
				};

				Color c = world.GetObjectColor(pixelToWorld);

				if (!(pixelToWorld.x < world.widthCurrentStart || pixelToWorld.x > world.widthCurrentEnd || pixelToWorld.y < world.heightCurrentStart || pixelToWorld.y > world.heightCurrentEnd))
				{
					gfx.PutPixel(i, j, c);
				}
			}
		}
	}
}

void Camera::SetPos(Vec2 in_pos)
{
	pos = in_pos;
}

Vec2 Camera::GetPos()
{
	return pos;
}

void Camera::TurnOn()
{
	drawMode = true;
}

void Camera::TurnOff()
{
	drawMode = false;
}

float Camera::GetOrientation()
{
	return orientation;
}

bool Camera::IsOn()
{
	return drawMode;
}
