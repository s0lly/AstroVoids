#pragma once

#include "MainWindow.h"
#include "Graphics.h"
#include "World.h"
#include "Vec2.h"
#include "math.h"


enum class CameraAction
{
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	TurnLeft,
	TurnRight,
	ZoomIn,
	ZoomOut
};


class Camera
{

public:

	void Init(Vec2 in_pos, float startWidth, float startHeight, float startOrientation);

	void Modify(CameraAction action, float changeValue);

	void DrawView(Graphics& gfx, World& world);

	void SetPos(Vec2 in_pos);
	Vec2 GetPos();

	void TurnOn();
	void TurnOff();

	float GetOrientation();

	bool IsOn();


private:

	Vec2 pos = { 50.0f, 50.0f };

	float width = 16.0f;
	float height = 9.0f;

	float orientation = 0.0f;
	float cosOrient;
	float sinOrient;

	bool drawMode;

};