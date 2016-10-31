/******************************
* wormhole.h
* defines the wormhole class
*******************************/

#ifndef WORMHOLE_H
#define WORMHOLE_H

#include "point.h"
#include "uiDraw.h"

class Wormhole
{
public:
	//non-default constructor
	Wormhole(Point tl, Point br);	

	//getters
	Point getPoint() { return position; }
	int getSize() { return 20; }
	int getLifeline() { return lifeline; }
	bool isActive() { return active; }
	bool isAlive() { return alive; }

	//setters
	void kill() { alive = false; active = false; }
	void setPoint(Point p) { position = p; }
	void activate();
	
	void draw();
	void advance();
	void cooldown();

private:
	Point position;			//position of the wormhole
	bool active;			//if active (and alive), the wormhole will teleport an object
	int cooldownTimer;		//after teleporting, the wormhole cools down
	int lifeline;			//lifeline of the wormhole
	bool alive;				//if alive, wormhole will be drawn
};

#endif