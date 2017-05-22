/**************************************************************
* rocks.h
* defines the Rock base class and three children
*	-BigRock
*	-MediumRock
*	-SmallRock
***************************************************************/

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 18
#define MEDIUM_ROCK_SIZE 12
#define SMALL_ROCK_SIZE 7

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flying.h"
#include <vector>

//base Rock class - dependent on Flying class
class Rock : public Flying
{
public:
	//getters
	int getSize() { return size; }
	int getRotation() { return rotation; }

	//setters
	void setRotation(int rot) { rotation = rot; }

	void advance();
	virtual int breakUp(std::vector<Rock*> & rocks) = 0;
	virtual void draw() = 0;

protected:
	int size;		//size of the rock
	int rotation;	//rotation angle of the rock

private:
};

//Big Rock class - dependent on Rock class
class BigRock : public Rock
{
public:
	BigRock(Point, Point);
	
	int breakUp(std::vector<Rock*> & rocks);
	void draw() { drawLargeAsteroid(position, rotation); }
};

//Medium Rock class - dependent on Rock class
class MediumRock : public Rock
{
public:
	MediumRock();

	int breakUp(std::vector<Rock*> & rocks);
	void draw() { drawMediumAsteroid(position, rotation); }
};

//Small Rock class - dependent on Rock class
class SmallRock : public Rock
{
public:
	SmallRock();

	int breakUp(std::vector<Rock*> & rocks);
	void draw() { drawSmallAsteroid(position, rotation); }
};


#endif /* rocks_h */
