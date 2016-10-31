/***********************************************
* ship-types.h
* each ship type inherits from the ship class
* defines the types of ships
* 3 types of ships
*    Original - the original Asteroids ship
*    Serenity - from the TV show Firefly
*    X-Wing - from the Star Wars franchise
***********************************************/

#ifndef SHIPTYPES_H
#define SHIPTYPES_H

#include "ship.h"

/****************************
* ORIGINAL class definition
*****************************/
class Original : public Ship
{
public:
	Original();

	void draw(const Interface & ui);
	void fireWeapon(vector<Bullet*> & bullets);
private:

};

/******************************
* SERENITY class definition
*******************************/
class Serenity : public Ship
{
public:
	Serenity();

	virtual void draw(const Interface & ui);
	virtual void fireWeapon(vector<Bullet*> & bullets);

private:

};

/**************************
* X-WING class definition
***************************/
class X_Wing : public Ship
{
public:
	X_Wing();

	virtual void draw(const Interface & ui);
	virtual void fireWeapon(vector<Bullet*> & bullets);

private:
};

#endif