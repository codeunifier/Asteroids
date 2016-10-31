/******************************************************************
* ship.cpp
* member functions for the ship class not defined in ship.h
* ship can move across the screen, fire a weapon, and be upgraded
*******************************************************************/

#include "ship-types.h"
#include "bullet.h"
#include "uiDraw.h"

#include <vector>

#include <math.h>
#define PI 3.14159
#define DEGTORAD(angle) ((double)angle*PI/180.0)

//default constructor for the ship class
Ship::Ship()
	: angle(0)				//starting angle is 0 degrees (facing up)
	, lives(3)				//ship starts with 3 lives
	, awardedLives(0)		//ship starts out with no awarded lives
	, deathTimer(0)			//ship starts out alive, with no death timer
{
	position = { 0, 0 };	//starting position in the center of the screen
	alive = true;
}

/*************************************************************
* advance() advances the ship - thrusters must be activated
**************************************************************/
void Ship::advance()
{
	if (alive)
	{
		if (velocity.getDx() != 0 || velocity.getDy() != 0)
			slowDown();

		position.addX(velocity.getDx());
		position.addY(velocity.getDy());
	}
	else if (deathTimer > 0)
		deathTimer--;
	else
		alive = true;
}

/*******************************************************
* thrust() applies the ship's thrusters and moves it
********************************************************/
void Ship::thrust()
{
	velocity.setDx(velocity.getDx() + thrustAmount*cos(DEGTORAD(thrustAngle)));
	velocity.setDy(velocity.getDy() + thrustAmount*sin(DEGTORAD(thrustAngle)));
}

/***********************************************************
* slowDown() decreases the velocity, slowing down the ship
************************************************************/
void Ship::slowDown()
{
	if (velocity.getDx() > 0)
		velocity.setDx(velocity.getDx() - (shipSize / 170.));
	else if (velocity.getDx() < 0)
		velocity.setDx(velocity.getDx() + (shipSize / 170.));

	if (velocity.getDy() > 0)
		velocity.setDy(velocity.getDy() - (shipSize / 170.));
	else if (velocity.getDy() < 0)
		velocity.setDy(velocity.getDy() + (shipSize / 170.));
}

/****************************************************************************
* blowUp() is called when the ship hits an asteroid and must be annihilated
*****************************************************************************/
void Ship::blowUp()
{
	alive = false;
	position = { 0, 0 };
	velocity = { 0, 0 };
	angle = 0;
	lives--;
	deathTimer = 200;
}

/********************************************************************************
* updateLives() accepts the points and adds a new life for every 10,000 points
* returns true when a new life has been granted
*********************************************************************************/
bool Ship::updateLives(int points)
{
	int temp = 0;
	if (points > 10000)
	{
		for (int i = points; i >= 10000; i -= 10000)
			temp++;

		lives += temp - awardedLives;

		if (temp > awardedLives)
		{
			awardedLives++;
			return true;
		}
		else
			return false;
	}
	else
	{
		awardedLives = 0;
		return false;
	}
}

/**************************************************************
* changeShip() swaps the current ship out for a different one
***************************************************************/
void Ship::changeShip(Ship * &spaceship, int type)
{
	Ship * oldShip = spaceship;

	//set the game's ship to a new ship type
	switch (type)
	{
	case 1:
		spaceship = new Original;
		break;
	case 2:
		spaceship = new Serenity;
		break;
	case 3:
		spaceship = new X_Wing;
		break;
	}

	spaceship->setPoint(oldShip->getPoint());
	spaceship->setVelocity(oldShip->getVelocity());
	spaceship->setAngle(oldShip->getAngle());

	delete oldShip;
}