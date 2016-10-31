/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class methods
 *********************************************************************/

#include "game.h"

 //for sounds
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#endif //Windows

using namespace std;

#define STARTUP_ROCK_NUM 10

//constructor for the Game class
Game::Game(Point tl, Point br)
	: topLeft(tl)			//top left point of the screen
	, bottomRight(br)		//bottom right point of the screen
	, points(0)				//no points at the start of the game
	, wormholeCounter(200)	//wait 200 frames before releasing the wormholes
	, pause(false)		    //game starts active
{
	//create a new original ship
	spaceship = new Original;

	//create rocks to begin the game
	for (int i = 0; i < STARTUP_ROCK_NUM; i++)
	{
		BigRock * newRock = new BigRock(topLeft, bottomRight);
		rocks.push_back(newRock);
	}

	//create the wormholes
	//wormholes are neither active nor alive when created
	worm[0] = new Wormhole(topLeft, bottomRight);
	worm[1] = new Wormhole(topLeft, bottomRight);
}

//destructor for the Game class
Game::~Game()
{
	//decide how to end the game
	//clean things up at the end of the game

	//delete any allocated rocks
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i] != NULL)
			delete rocks[i];
	}
}

/***********************************************
* advance() advances the game one unit of time
************************************************/
void Game::advance()
{
	//advance the ship
	//check for wrapping
	spaceship->setPoint(spaceship->checkWrapping(spaceship->getPoint(), bottomRight, topLeft));
	spaceship->advance();

	//advance the asteroids
	//if there are no asteroids left, create a new set of large rocks
	if (rocks.size() == 0)
	{
		for (int i = 0; i < STARTUP_ROCK_NUM; i++)
		{
			BigRock * newRock = new BigRock(topLeft, bottomRight);
			rocks.push_back(newRock);
		}
	}
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			//check for wrapping
			rocks[i]->setPoint(rocks[i]->checkWrapping(rocks[i]->getPoint(), bottomRight, topLeft));

			//move forward
			rocks[i]->advance();
		}
	}

	//advance the bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			//check for wrapping
			bullets[i]->setPoint(bullets[i]->checkWrapping(bullets[i]->getPoint(), bottomRight, topLeft));

			//move forward
			bullets[i]->advance(spaceship->getFirePower());
		}
	}

	//decrement wormhole counter and check for activation
	if (wormholeCounter > 0)
		wormholeCounter--;
	else
	{
		if (!worm[0]->isAlive() && !worm[0]->isActive())
		{
			#ifdef _WIN32 || _WIN64
			//PlaySound("C:\\WORMHOLE.WAV", NULL, SND_SYNC);
			#endif
		}
		worm[0]->activate();
		worm[1]->activate();

		if (worm[0]->getLifeline() == 1)
		{
			wormholeCounter = 1000;
			worm[0] = new Wormhole(topLeft, bottomRight);
			worm[1] = new Wormhole(topLeft, bottomRight);
			
			#ifdef _WIN32 || _WIN64
			//PlaySound("C:\\WORMHOLE.WAV", NULL, SND_SYNC);
			#endif
		}
	}
	//advance the wormholes (but they don't move)
	//only need to check if one is alive
	if (worm[0]->isAlive())
	{
		worm[0]->advance();
		worm[1]->advance();
	}

	handleCollisions();
	cleanUpZombies();
}

/********************************************
* handleInput() accepts input from the user
*********************************************/
void Game::handleInput(const Interface & ui)
{
	//pause or resume the game
	if (ui.isEsc())
	{
		if (pause)
			pause = false;
		else
			pause = true;
	}

	//only control the ship when it is alive
	if (spaceship->isAlive() && !pause)
	{
		if (ui.isLeft())
		{
			spaceship->rotateLeft();
		}

		if (ui.isRight())
		{
			spaceship->rotateRight();
		}

		if (ui.isUp())
		{
			spaceship->setThrustAngle(spaceship->getAngle() + 90);
			spaceship->thrust();
		}

		if (ui.isSpace())
		{
			spaceship->fireWeapon(bullets);
		}

		if (ui.isOne())
		{
			spaceship->changeShip(spaceship, 1);
		}

		if (ui.isTwo())
		{
			spaceship->changeShip(spaceship, 2);
		}

		if (ui.isThree())
		{
			spaceship->changeShip(spaceship, 3);
		}
	}

	//other keystrokes may be pressed at any time

	if (ui.isDown())
	{
		displayCommands();
	}

	if (ui.isEnd())
	{
		//closes the program
		exit(0);
	}
}

/**************************************
* draw() draws the game on the screen
***************************************/
void Game::draw(const Interface & ui)
{
	//draw the ship
	if (spaceship->isAlive())
		spaceship->draw(ui);

	//draw the rocks
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
			rocks[i]->draw();
	}

	//draw the bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
			bullets[i]->draw();
	}

	//draw the wormholes
	if (worm[0]->isAlive())
	{
		worm[0]->draw();
		worm[1]->draw();
	}
}

/******************************************************************************
* handleCollisions() checks if a bullet has hit a rock
*    If a large asteroid gets hit, it breaks apart and becomes 
*		two medium asteroids and one small one
*    If a medium asteroid gets hit, it breaks apart and becomes two 
*		small asteroids
*    If a small asteroid is hit, it is destroyed and removed from the game
*******************************************************************************/
void Game::handleCollisions()
{
	//loop through the rocks
	for (int i = 0; i < rocks.size(); i++)
	{
		//check if the rock is alive
		if (rocks[i]->isAlive())
		{
			//check if the bullet hit a rock
			for (int j = 0; j < bullets.size(); j++)
			{
				//check if the bullet is alive
				if (bullets[j]->isAlive())
				{
					//if (getClosestDistance(bullets[j], *rocks[i]) < rocks[i]->getSize())
					if (fabs(bullets[j]->getPoint().getX() - rocks[i]->getPoint().getX()) < rocks[i]->getSize()
						&& fabs(bullets[j]->getPoint().getY() - rocks[i]->getPoint().getY()) < rocks[i]->getSize())
					{
						//bullet hit a rock
						#ifdef _WIN32 || _WIN64
						//PlaySound("C:\\BANGLARGE.WAV", NULL, SND_ASYNC);
						#endif

						//break up the rock and kill the rock hit
						points += rocks[i]->breakUp(rocks);
						//kill the bullet
						bullets[j]->kill();
					}
				}
			}

			//check if the ship hit a rock
			if (spaceship->isAlive())
			{
				//if (getClosestDistance(serenity, *rocks[i]) < serenity.getSize() + rocks[i]->getSize())
				if (fabs(spaceship->getPoint().getX() - rocks[i]->getPoint().getX()) < spaceship->getSize() + rocks[i]->getSize()
					&& fabs(spaceship->getPoint().getY() - rocks[i]->getPoint().getY()) < spaceship->getSize() + rocks[i]->getSize())
				{
					//ship hit a rock
					#ifdef _WIN32 || _WIN64
					//PlaySound("C:\\BANGLARGE.WAV", NULL, SND_ASYNC);
					#endif

					rocks[i]->breakUp(rocks);
					spaceship->blowUp();
				}
			}
		}
	}

	//check if anything has entered a wormhole
	for (int i = 0; i < 2; i++)
	{
		if (worm[i]->isActive() && worm[i]->isAlive())
		{
			//loop through the rocks
			for (int j = 0; j < rocks.size(); j++)
			{
				if (rocks[j]->isAlive())
				{
					if (fabs(worm[i]->getPoint().getX() - rocks[j]->getPoint().getX()) < rocks[j]->getSize() + worm[i]->getSize()
						&& fabs(worm[i]->getPoint().getY() - rocks[j]->getPoint().getY()) < rocks[j]->getSize() + worm[i]->getSize())
					{
						//rock entered a wormhole
						if (i == 0)
						{
							rocks[j]->setPoint(worm[1]->getPoint());
							worm[1]->cooldown();
						}
						else
						{
							rocks[j]->setPoint(worm[0]->getPoint());
							worm[0]->cooldown();
						}
					}
				}
			}

			//loop through the bullets
			for (int j = 0; j < bullets.size(); j++)
			{
				if (bullets[j]->isAlive())
				{
					if (fabs(worm[i]->getPoint().getX() - bullets[j]->getPoint().getX()) < worm[i]->getSize()
						&& fabs(worm[i]->getPoint().getY() - bullets[j]->getPoint().getY()) < worm[i]->getSize())
					{
						//bullet entered wormhole
						if (i == 0)
						{
							bullets[j]->setPoint(worm[1]->getPoint());
							worm[1]->cooldown();
						}
						else
						{
							bullets[j]->setPoint(worm[0]->getPoint());
							worm[0]->cooldown();
						}
					}

				}
			}

			//check the ship
			if (spaceship->isAlive())
			{
				if (fabs(spaceship->getPoint().getX() - worm[i]->getPoint().getX()) < spaceship->getSize() + worm[i]->getSize()
					&& fabs(spaceship->getPoint().getY() - worm[i]->getPoint().getY()) < spaceship->getSize() + worm[i]->getSize())
				{
					//the ship entered a wormhole
					if (i == 0)
					{
						spaceship->setPoint(worm[1]->getPoint());
						worm[1]->cooldown();
					}
					else
					{
						spaceship->setPoint(worm[0]->getPoint());
						worm[0]->cooldown();
					}
				}

			}
		}
	}
}

/************************************************************
* cleanUpZombies() removes dead flying objects from the game
*************************************************************/
void Game::cleanUpZombies()
{
	//look for dead rocks
	vector<Rock*>::iterator rockIt = rocks.begin();
	int index = 0;
	while (rockIt != rocks.end())
	{
		Rock * rock = *rockIt;

		if (!rock->isAlive())
		{
			delete rocks[index];
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++;
			index++;
		}
	}

	// Look for dead bullets
	vector<Bullet*>::iterator bulletIt = bullets.begin();
	index = 0;
	while (bulletIt != bullets.end())
	{
		Bullet* bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet->isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...
			// remove from list and advance
			delete bullets[index];
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
			index++;
		}
	}
}

/*************************************************************************
* displayMenu() displays the lives on the top left corner of the screen
* and the total points accumulated. This function also checks the score 
* and adds another life for every 10,000 points
*    the game initializes with 3 lives and 0 points
**************************************************************************/
void Game::displayMenu()
{
	//check points - every 10,000 grants another life
	if (spaceship->updateLives(points))
	{
		#ifdef _WIN32 || _WIN64
		//PlaySound("C:\\LIFE.WAV", NULL, SND_ASYNC);
		#endif
	}

	//draw the lives
	Point pLife(topLeft.getX() + 10, topLeft.getY() - 10);
	for (int i = 0; i < spaceship->getLives(); i++)
	{
		Original ship;
		ship.setPoint(pLife);
		ship.kill();
		Interface ui;
		ship.draw(ui);
		pLife.addX(10);
	}

	//draw the points
	Point pPoints(0, topLeft.getY() - 5);
	drawNumber(pPoints, points);
}

/***********************************************************************
* displayCommands() displays the commands of the game on the top right part
* of the screen
************************************************************************/
void Game::displayCommands()
{
	Point point(bottomRight.getX() - 100, topLeft.getY() - 20);
	drawText(point, "Key commands:");

	point.setY(topLeft.getY() - 50);
	drawText(point, "Select ship type: ");
	point.setY(topLeft.getY() - 65);
	drawText(point, "1. Original");
	point.setY(topLeft.getY() - 80);
	drawText(point, "2. Serenity");
	point.setY(topLeft.getY() - 95);
	drawText(point, "3. X-Wing");

	point.setY(topLeft.getY() - 125);
	drawText(point, "Move with");
	point.setY(topLeft.getY() - 140);
	drawText(point, "arrow keys");

	point.setY(topLeft.getY() - 170);
	drawText(point, "\"END\" to close");
	point.setY(topLeft.getY() - 185);
	drawText(point, "\"ESC\" to pause");
}