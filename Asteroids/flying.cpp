/**********************************************************************
* flying.cpp
* function bodies for the flying class
* class used for objects intending to "fly" or move across the screen
***********************************************************************/

#include "flying.h"
#include <iostream>
using namespace std;

//default constructor for flying class
Flying::Flying()
{
}

//getter for the Point variable
Point Flying::getPoint() const
{
	return position;
}

//setter for the Point variable
void Flying::setPoint(Point position)
{
	this->position = position;
}

//getter for the Velocity variable
Velocity Flying::getVelocity() const
{
	return velocity;
}

//setter for the Velocity variable
void Flying::setVelocity(Velocity velocity)
{
	this->velocity = velocity;
}

/***************************************************************
* returns alive boolean variable
****************************************************************/
bool Flying::isAlive()
{
	return alive;
}

/***************************************************************
* sets the alive boolean variable
****************************************************************/
void Flying::setAlive(bool alive)
{
	this->alive = alive;
}

/**************************************************************
* kill() kills the flying object in the event of a collision
* or when the object leaves the screen
***************************************************************/
void Flying::kill()
{
	alive = false;
}

/*************************************************************
* checkWrapping() checks the position of a flying object and
* wraps it around the screen if it goes off the edges
* pos - position of the object
* br - bottom right point of the screen
* tl - top left point of the screen
**************************************************************/
Point Flying::checkWrapping(Point pos, Point br, Point tl)
{
	Point temp = pos;

	if (pos.getX() > br.getX() || pos.getX() < tl.getX())
	{
		temp.setX(-pos.getX());
		temp.setY(pos.getY());
	}

	if (pos.getY() < br.getY() || pos.getY() > tl.getY())
	{
		temp.setX(pos.getX());
		temp.setY(-pos.getY());
	}

	return temp;
}