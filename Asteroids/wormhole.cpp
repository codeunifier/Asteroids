/***********************************************************************
* wormhole.cpp
* funciton bodies for the wormhole class
* only 2 wormholes with ever be active in the game at a time, and they
*    will always be displayed simultaneously
************************************************************************/

#include "wormhole.h"

//for sounds
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#endif //Windows

//non-default constructor
Wormhole::Wormhole(Point tl, Point br) :
	lifeline(300)		//initialize with 300 frames of life
	, alive(false)		//when constructed, the wormholes are not alive
	, active(false)		//when constructed, the wormholes are not active
{
	position.setX((float)random(tl.getX() + 80, br.getX() - 80));
	position.setY((float)random(br.getY() + 80, tl.getY() - 80));
}

/********************************************
* draw() draws the wormhole on the screen
********************************************/
void Wormhole::draw()
{
	drawSpiral(1, .9, position);
}

/**********************************************************
* advance() decrements timers when the wormholes are active
***********************************************************/
void Wormhole::advance()
{
	if (lifeline > 0)
		lifeline--;
	else
		kill();

	if (cooldownTimer > 0)
		cooldownTimer--;
	else
		active = true;
}

/**********************************************************
* activate() activates the wormhole on initialization and
*    after cooldown
***********************************************************/
void Wormhole::activate()
{
	alive = true;

	if (lifeline == 0)
		lifeline = 300;

	if (cooldownTimer == 0)
		active = true; 
}

/**********************************************************************
* cooldown() sets the cooldown timer and deactivates the wormhole
* the cooldown allows an object teleported to leave the wormhole 
*    without being teleported back and forth between the two wormholes
***********************************************************************/
void Wormhole::cooldown()
{
	cooldownTimer = 50;
	active = false;
}