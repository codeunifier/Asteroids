/**************************************************************
* flying.h
* defines the flying class
***************************************************************/

#ifndef FLYING_H
#define FLYING_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class Flying
{
public:
	Flying();
	Point getPoint() const;
	void setPoint(Point);
	Velocity getVelocity() const;
	void setVelocity(Velocity);
	bool isAlive();
	void setAlive(bool);
	void kill();
	Point checkWrapping(Point, Point, Point);
protected:
	Point position;		//position of the flying object
	bool alive;			//alive variable for the object
	Velocity velocity;	//velocity of the flying object
	float angle;		//angle of direction the flying object moves
private:
};

#endif