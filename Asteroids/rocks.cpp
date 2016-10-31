/*************************************************************************
* rocks.cpp
* function bodies for the rocks class
* three rocks defined: BigRock, MediumRock, SmallRock
* when a big or medium rock is destroyed, it breaks up into smaller rocks
**************************************************************************/

#include "rocks.h"
#include "uiDraw.h"

#include <vector>

#include <math.h>
#define PI 3.14159
#define DEGTORAD(angle) ((double)angle*PI/180.0)

/*************************************
* advance() advances the rocks
**************************************/
void Rock::advance()
{
	rotate(position, position, rotation);
	position.addX(velocity.getDx());
	position.addY(velocity.getDy());
	rotation += 5;
}

/*******************************************
* default constructor for the big asteroids
********************************************/
BigRock::BigRock(Point tl, Point br)
{
	size = BIG_ROCK_SIZE;
	alive = true;
	rotation = BIG_ROCK_SPIN + random(-50, 50);

	//the rocks should not spawn on top of the ship
	do
	{
		position = { (float)random(tl.getX() + 10, br.getX() - 10), (float)random(br.getY() + 10, tl.getY() - 10) };
	} while (abs(position.getX()) < 30 || abs(position.getY()) < 30);

	int sign;
	do
		sign = random(-1, 2);
	while (sign == 0);
	velocity = { (float)cos(DEGTORAD(rotation)) * sign, (float)sin(DEGTORAD(rotation)) * sign };
}

/*****************************************************************
* BigRock::breakUp() is called when a large asteroid is hit
*    a large asteroid breaks up into two medium asteroids and
*    one small asteroid
******************************************************************/
int BigRock::breakUp(std::vector<Rock*> & rocks)
{
	/*
	The first medium asteroid has the same velocity as the original large one
	plus 1 pixel/frame in the up direction.
	The second medium asteroid has the same velocity as the original large one
	plus 1 pixel/frame in the down direction.
	The small asteroid has the original velocity plus 2 pixels/frame to the right.
	*/

	MediumRock * med;
	SmallRock * sma;

	med = new MediumRock;
	med->setPoint(position);
	med->setVelocity({ velocity.getDx(), velocity.getDy() + 1 });
	rocks.push_back(med);

	med = new MediumRock;
	med->setPoint(position);
	med->setVelocity({ velocity.getDx(), velocity.getDy() - 1 });
	rocks.push_back(med);

	sma = new SmallRock;
	sma->setPoint(position);
	sma->setVelocity({ velocity.getDx() + 2, velocity.getDy() });
	rocks.push_back(sma);

	//kill the original large rock
	kill();

	return 20;	//20 points for destroying a large rock
}

/**********************************************
* default constructor for the medium asteroids
***********************************************/
MediumRock::MediumRock()
{
	size = MEDIUM_ROCK_SIZE;
	rotation = MEDIUM_ROCK_SPIN;
	alive = true;
}

/***********************************************************
* MediumRock::breakUp() is called when a medium rock is hit
*    a medium rock breaks up into two small rocks
************************************************************/
int MediumRock::breakUp(std::vector<Rock*> & rocks)
{
	/*
	The first small asteroid has the same velocity as the original medium one
	plus 3 pixel/frame to the right.
	The second, 3 pixels/frame to the left.
	*/
	SmallRock * sma;

	sma = new SmallRock;
	sma->setPoint(position);
	sma->setVelocity({ velocity.getDx() + 3, velocity.getDy() });
	rocks.push_back(sma);

	sma = new SmallRock;
	sma->setPoint(position);
	sma->setVelocity({ velocity.getDx() - 3, velocity.getDy() });
	rocks.push_back(sma);

	//kill the original medium rock
	kill();
	return 50;	//50 points for destroying a medium rock
}

/**********************************************
* default constructor for the small asteroids
***********************************************/
SmallRock::SmallRock()
{
	size = SMALL_ROCK_SIZE;
	rotation = SMALL_ROCK_SPIN;
	alive = true;
}

/**********************************************************
* SmallRock::breakUp() is called when a small rock is hit
*    a small rock is simply destroyed
***********************************************************/
int SmallRock::breakUp(std::vector<Rock*> & rocks)
{
	kill();
	return 100;	//100 points for destroying a small rock
}
