/***********************************************
* bullet.h
* defines the bullet class
* two types of bullets:
*    Normal - like in the original arcade game
*    Laser - because who doesn't like lasers?
************************************************/

#ifndef BULLET_H
#define BULLET_H

#define BULLET_LIFE 50

#include <iostream>

#include "flying.h"

using namespace std;

class Bullet : public Flying
{
public:
	void advance(int bulletSpeed);
	virtual void draw() = 0;
	void fire(Point, float);
protected:
	int lifeline;	//lifeline of the bullet
};

class Normal : public Bullet
{
public:
	Normal() { lifeline = 40; }
	virtual void draw() { drawDot(position); }
};

class Laser : public Bullet
{
public:
	Laser() { lifeline = 50; }
	virtual void draw() { drawRect(position, 10, 1, angle); }
};

#endif
