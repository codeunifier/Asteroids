/*******************************************
* velocity.cpp
* function bodies for the velocity class
********************************************/

#include "velocity.h"

using namespace std;

Velocity::Velocity()
{
	velX = 0.0;
	velY = 0.0;
}

Velocity::Velocity(float x, float y)
{
	velX = x;
	velY = y;
}

float Velocity::getDx()
{
	return velX;
}

float Velocity::getDy()
{
	return velY;
}

void Velocity::setDx(float x)
{
	velX = x;
}

void Velocity::setDy(float y)
{
	velY = y;
}