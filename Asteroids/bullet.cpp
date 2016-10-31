/***********************************************
* bullet.cpp
* function bodies for the bullet class
* bullets are fired and move across the screen
* bullet types are defined in bullet.h
************************************************/

#include "bullet.h"
#include "flying.h"

#include <math.h>
#define PI 3.14159
#define DEGTORAD(angle) ((double)angle*PI/180.0)

/*********************************************************************
* advance() advances the bullet's position
* the slope of an angle is the tangent of that angle (rise over run)
**********************************************************************/
void Bullet::advance(int bulletSpeed)
{
	position.addX(velocity.getDx() * bulletSpeed);
	position.addY(velocity.getDy() * bulletSpeed);

	if (lifeline == 0)
		kill();
	else
		lifeline--;
}

/****************************************************
* fire() fires a bullet
* pos = starting position for the bullet
* angle = directional angle for the bullet's travel
*****************************************************/
void Bullet::fire(Point position, float angle)
{
	this->position = position;
	this->angle = angle;
	velocity.setDx(cos(DEGTORAD(angle)));
	velocity.setDy(sin(DEGTORAD(angle)));
	alive = true;
}