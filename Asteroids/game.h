/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "rocks.h"
//includes flying.h (velocity.h, point.h) and uiDraw.h
#include "ship.h"
//includes bullet.h and flying.h (velocity.h point.h)
#include "uiInteract.h"
#include "wormhole.h"
#include "ship-types.h"

/*
* Game class defines and advances the game
*/
class Game
{
public:
	Game(Point tl, Point br);
	~Game();

	void advance();
	void handleInput(const Interface & ui);
	void draw(const Interface & ui);
	void displayMenu();
	void displayCommands();
	bool isPaused() { return pause; }

private:
	void handleCollisions();
	void cleanUpZombies();

	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	Ship * spaceship;				//ship pointer
	std::vector<Bullet*> bullets;	//vector of bullet objects
	std::vector<Rock*> rocks;		//vector of rock pointers
	Wormhole * worm[2];				//array of wormhole pointers

	int wormholeCounter;			//time in between activating wormholes
	int points;						//points accumulated for destroying asteroids
	bool pause;						//boolean variable for the game state: active or paused
};


#endif /* GAME_H */
