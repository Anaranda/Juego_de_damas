#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = y = 0;
}

Vector2D::~Vector2D()
{
}

void Vector2D::SetVector(float xi, float yi)
{
	x = xi;
	y = yi;
}

float Vector2D::GetVectorX()
{
	return x;
}

float Vector2D::GetVectorY()
{
	return y;
}


Vector2D Vector2D::operator+(Vector2D v)
{
	Vector2D resultado;

	resultado.x = x + v.x;
	resultado.y = y + v.y;

	return resultado;
}

Vector2D Vector2D::operator*(float t)
{
	Vector2D resultado;

	resultado.x = x * t;
	resultado.y = y * t;

	return resultado;
}

Vector2D operator*(float t, Vector2D v)
{
	Vector2D resultado;

	resultado.x = t * v.x;
	resultado.y = t * v.y;

	return resultado;
}
