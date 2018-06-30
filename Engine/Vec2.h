#pragma once


class Vec2
{
public:

	Vec2 operator+(const Vec2 rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}

	Vec2 operator+(const float rhs)
	{
		return { x + rhs, y + rhs };
	}

	Vec2 operator-(const Vec2 rhs)
	{
		return { x - rhs.x, y - rhs.y };
	}

	Vec2 operator*(const float rhs)
	{
		return { x * rhs, y * rhs };
	}


	float x;
	float y;

private:



};