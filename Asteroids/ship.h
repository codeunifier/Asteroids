/***********************************************************
* ship.h
* defines the ship base class
* tied to the ship-types file
************************************************************/

#ifndef ship_h
#define ship_h

#define ROTATE_AMOUNT 6
#define SLOW_AMOUNT .05

#include "flying.h"
#include "bullet.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "rocks.h"

#include <vector>

/**************************
* defines the ship class
***************************/
class Ship : public Flying
{
public:
	//getters
	float getAngle() { return angle; }
	int getSize() { return shipSize; }
	int getLives() { return lives; }
	int getFirePower() { return firePower; }

	//setters
	void setAngle(float ang) { angle = ang; }
	void setThrustAngle(float thr) { thrustAngle = thr; }

	void rotateLeft() { angle += ROTATE_AMOUNT; }
	void rotateRight() { angle -= ROTATE_AMOUNT; }

	void blowUp();
	void thrust();
	void advance();
	virtual void draw(const Interface & ui) = 0;
	virtual void fireWeapon(vector<Bullet*> & bullets) = 0;
	bool updateLives(int points);
	void changeShip(Ship* &spaceship, int type);

protected:
	Ship();
	float angle;		//angle the ship is pointing
	float thrustAngle;	//angle in which the ship is moving
	int shipSize;		//size of the ship
	int thrustAmount;	//amount of thrust from the ship's engines
	int firePower;		//becomes bullet speed when drawing bullets

private:
	void slowDown();	//slows the ship down while moving

	int deathTimer;		//timer counting while the ship is dead before respawn
	int lives;			//number of lives
	int awardedLives;	//number of lives awarded for every 10,000 points
};

#endif /* ship_h */
