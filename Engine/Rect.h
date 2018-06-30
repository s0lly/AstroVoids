#pragma once

#include "Colors.h"
#include "Vec2.h"
#include <math.h>


enum class WorldOjectType
{
	Triangle,
	Rectangle,
	Circle
};

class WorldObject
{
public:

	bool isAtLocation(Vec2 loc)
	{

	}

	Color GetColor()
	{
		return c;
	}


private:

	Color c;


};




class Line
{
public:

	static constexpr Vec2 OUTOFMAP = { -3.15167f, -3.15167f };

	static bool CheckIntersect(float p0_x, float p0_y, float p1_x, float p1_y,
		float p2_x, float p2_y, float p3_x, float p3_y)
	{
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		if ((-s2_x * s1_y + s1_x * s2_y) == 0 || (-s2_x * s1_y + s1_x * s2_y) == 0)
		{
			return false;
		}

		float s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0.0f && s <= 1.0f && t >= 0.0f && t <= 1.0f)
		{
			return true; // Collision
		}

		return false; // No collision
	}

public:

	void Init(Vec2 a, Vec2 b)
	{
		m = (b.y - a.y) / (b.x - a.x);
		c = a.y - a.x * m;
	}

	float GetY(float x)
	{
		return m * x + c;
	}

	float GetX(float y)
	{
		return (y - c) / m;
	}

	float m;
	float c;

private:

};





class Triangle
{
public:



	void Init(Vec2 in_a, Vec2 in_b, Vec2 in_c, Color in_color)
	{
		vertices[0] = in_a;
		vertices[1] = in_b;
		vertices[2] = in_c;
		color = in_color;

		topLeft.x = vertices[0].x;
		topLeft.y = vertices[0].y;
		botRight.x = vertices[0].x;
		botRight.y = vertices[0].y;


		for (int i = 1; i < 3; i++)
		{

			if (topLeft.x > vertices[i].x)
			{
				topLeft.x = vertices[i].x;
			}
			if (topLeft.y > vertices[i].y)
			{
				topLeft.y = vertices[i].y;
			}

			if (botRight.x < vertices[i].x)
			{
				botRight.x = vertices[i].x;
			}
			if (botRight.y < vertices[i].y)
			{
				botRight.y = vertices[i].y;
			}

		}

		area = 0.5f *(-vertices[1].y * vertices[2].x + vertices[0].y * (-vertices[1].x + vertices[2].x) + vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * vertices[2].y);

		//area = (botRight.x - topLeft.x) * (botRight.y - topLeft.y) * 0.5f;

		centroid = { (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0f, (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0f };
	}

	bool IsAtLocation(Vec2 loc)
	{

		if (loc.x > topLeft.x && loc.x < botRight.x && loc.y > topLeft.y && loc.y < botRight.y)
		{

			float s = 1.0f / (2.0f * area)*(vertices[0].y*vertices[2].x - vertices[0].x * vertices[2].y + (vertices[2].y - vertices[0].y)*loc.x + (vertices[0].x - vertices[2].x)*loc.y);
			float t = 1.0f / (2.0f * area)*(vertices[0].x*vertices[1].y - vertices[0].y * vertices[1].x + (vertices[0].y - vertices[1].y)*loc.x + (vertices[1].x - vertices[0].x)*loc.y);

			if (s >= 0.0f && t >= 0.0f && (1 - s - t) >= 0.0f)
			{
				return true;
			}
		}

		return false;

	}

	void Move(Vec2 distance)
	{
		Init({ vertices[0].x + distance.x * (float)cos(orientation) - distance.y * (float)sin(orientation), vertices[0].y + distance.y * (float)cos(orientation) + distance.x * (float)sin(orientation) },
			 { vertices[1].x + distance.x * (float)cos(orientation) - distance.y * (float)sin(orientation), vertices[1].y + distance.y * (float)cos(orientation) + distance.x * (float)sin(orientation) },
			 { vertices[2].x + distance.x * (float)cos(orientation) - distance.y * (float)sin(orientation), vertices[2].y + distance.y * (float)cos(orientation) + distance.x * (float)sin(orientation) },
			 color);
	}

	void Scale(float size)
	{
		Init((vertices[0] - centroid) * size + centroid, (vertices[1] - centroid) * size + centroid, (vertices[2] - centroid) * size + centroid, color);
	}

	void Rotate(float angle)
	{
		orientation += angle;

		Init({ (vertices[0].x - centroid.x) * (float)cos(angle) - (vertices[0].y - centroid.y) * (float)sin(angle) + centroid.x, (vertices[0].y - centroid.y) * (float)cos(angle) + (vertices[0].x - centroid.x) * (float)sin(angle) + centroid.y },
			 { (vertices[1].x - centroid.x) * (float)cos(angle) - (vertices[1].y - centroid.y) * (float)sin(angle) + centroid.x, (vertices[1].y - centroid.y) * (float)cos(angle) + (vertices[1].x - centroid.x) * (float)sin(angle) + centroid.y },
			 { (vertices[2].x - centroid.x) * (float)cos(angle) - (vertices[2].y - centroid.y) * (float)sin(angle) + centroid.x, (vertices[2].y - centroid.y) * (float)cos(angle) + (vertices[2].x - centroid.x) * (float)sin(angle) + centroid.y },
			 color);
	}


	Vec2 vertices[3];
	Vec2 centroid;

	float orientation = 0.0f;

	float area;

	Vec2 topLeft;
	Vec2 botRight;

	Color color;

private:

};





class Rect
{
public:

	void Init(Vec2 in_a, Vec2 in_b, Vec2 in_c, Vec2 in_d, Color in_color)
	{
		triangles[0].Init(in_a, in_b, in_d, in_color);
		triangles[1].Init(in_c, in_d, in_b, in_color);
		color = in_color;
		topLeft.x = triangles[0].topLeft.x < triangles[1].topLeft.x ? triangles[0].topLeft.x : triangles[1].topLeft.x;
		topLeft.y = triangles[0].topLeft.y < triangles[1].topLeft.y ? triangles[0].topLeft.y : triangles[1].topLeft.y;
		botRight.x = triangles[0].botRight.x > triangles[1].botRight.x ? triangles[0].botRight.x : triangles[1].botRight.x;
		botRight.y = triangles[0].botRight.y > triangles[1].botRight.y ? triangles[0].botRight.y : triangles[1].botRight.y;
	}

	bool IsAtLocation(Vec2 loc)
	{

		return (triangles[0].IsAtLocation(loc) || triangles[1].IsAtLocation(loc));
		
	}

	void Move(Vec2 distance)
	{
   		triangles[0].Move(distance);
		triangles[1].Move(distance);

		topLeft.x = triangles[0].topLeft.x < triangles[1].topLeft.x ? triangles[0].topLeft.x : triangles[1].topLeft.x;
		topLeft.y = triangles[0].topLeft.y < triangles[1].topLeft.y ? triangles[0].topLeft.y : triangles[1].topLeft.y;
		botRight.x = triangles[0].botRight.x > triangles[1].botRight.x ? triangles[0].botRight.x : triangles[1].botRight.x;
		botRight.y = triangles[0].botRight.y > triangles[1].botRight.y ? triangles[0].botRight.y : triangles[1].botRight.y;
	}

	Triangle triangles[2];

	Color color;

	Vec2 topLeft;
	Vec2 botRight;

private:

};

class Circle
{
public:

	void Init(Vec2 a, float r, Color in_c)
	{
		mid = a;
		radius = r;
		radiusSqrd = r * r;
		color = in_c;

		topLeft.x = a.x - r;
		topLeft.y = a.y - r;
		botRight.x = a.x + r;
		botRight.y = a.y + r;
	}

	void Move(Vec2 distance)
	{
		Init({ mid.x + distance.x * (float)cos(orientation) - distance.y * (float)sin(orientation), mid.y + distance.y * (float)cos(orientation) + distance.x * (float)sin(orientation) }, radius, color);
	}

	void Scale(float size)
	{
		Init(mid, radius * size, color);
	}

	void Rotate(float angle)
	{
		orientation += angle;

		if (orientation < 0.0f)
		{
			Rotate(2.0f * 3.14159f);
		}
		if (orientation > (2.0f * 3.14159f))
		{
			Rotate(-(2.0f * 3.14159f));
		}
	}

	bool IsAtLocation(Vec2 loc)
	{
		if (loc.x > mid.x - radius && loc.x < mid.x + radius && loc.y > mid.y - radius && loc.y < mid.y + radius)
		{
			return (pow(loc.x - mid.x, 2) + pow(loc.y - mid.y, 2) < radiusSqrd);
		}

		return false;

	}

	Vec2 mid;
	float radius;
	float radiusSqrd;

	Color color;

	float orientation = 0.0f;

	Vec2 topLeft;
	Vec2 botRight;

private:

};








