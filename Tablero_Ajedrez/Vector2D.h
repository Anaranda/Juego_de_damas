#pragma once
class Vector2D
{
public:
	Vector2D();
	virtual ~Vector2D();
	float x;
	float y;

	void SetVector(float xi, float yi);
	float GetVectorX();
	float GetVectorY();
	Vector2D operator+(Vector2D v);
	Vector2D operator*(float t);
};

Vector2D operator*(float t, Vector2D v);
