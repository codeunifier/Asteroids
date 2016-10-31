/****************************************************
* ship-types.cpp
* member function bodies for the three ship types
* X-Wing shoots lasers instead of regular bullets
*****************************************************/

#include "ship-types.h"

//default constructor for the original ship
Original::Original() : Ship()
{
	thrustAmount = 1;
	shipSize = 5;
	firePower = 10;
}

/************************************************************************
* DRAW Original Ship
* Draw the original Asteroids spaceship on the screen
*************************************************************************/
void Original::draw(const Interface & ui)
{
	// ultra simple point
	struct PT
	{
		int x;
		int y;
	};

	// draw the ship                                                 
	const PT pointsShip[] =
	{ // top   r.wing   r.engine l.engine  l.wing    top
		{ 0, 6 },{ 6, -6 },{ 2, -3 },{ -2, -3 },{ -6, -6 },{ 0, 6 }
	};

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < sizeof(pointsShip) / sizeof(PT); i++)
	{
		Point pt(position.getX() + pointsShip[i].x,
			position.getY() + pointsShip[i].y);
		rotate(pt, position, angle);
		glVertex2f(pt.getX(), pt.getY());
	}
	glEnd();

	// draw the flame if necessary
	if (ui.isUp() && alive)
	{
		const PT pointsFlame[3][5] =
		{
			{ { -2, -3 },{ -2, -13 },{ 0, -6 },{ 2, -13 },{ 2, -3 } },
			{ { -2, -3 },{ -4,  -9 },{ -1, -7 },{ 1, -14 },{ 2, -3 } },
			{ { -2, -3 },{ -1, -14 },{ 1, -7 },{ 4,  -9 },{ 2, -3 } }
		};
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
		int iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlame[iFlame][i].x,
				position.getY() + pointsFlame[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}
		glColor3f(1.0, 1.0, 1.0); // reset to white                                  
		glEnd();
	}
}

/******************************************************************
* fireWeapon() fires the ship's weapon(s)
*    if the ship is upgraded, two bullets are fired with each shot
*******************************************************************/
void Original::fireWeapon(vector<Bullet*> & bullets)
{
	//limit on number of bullets
	if (bullets.size() <= 7)
	{
		Bullet * newBullet = new Normal;
		newBullet->fire(position, angle + 90);
		bullets.push_back(newBullet);
	}
}

//default constructor for Serenity
Serenity::Serenity() : Ship()
{
	thrustAmount = 1.4;
	shipSize = 25;
	firePower = 20;
}

/************************************************
* DRAW Serenity Ship
*    draws the ship as Serenity
*************************************************/
void Serenity::draw(const Interface & ui)
{
	// ultra simple point
	struct PT
	{
		int x;
		int y;
	};

	// draw the ship                                                 
	const PT pointsShip[] =
	{  //see JPEG for corresponding numbers
		{ 1, 25 }			//1. right head top
		,{ 5, 18 }			//2. right head bottom
		,{ 3, 8 }			//3. right neck
		,{ 6, 5 }			//4. right wing top left
		,{ 10, 4 }			//5. right wing top right
		,{ 12, 2 }			//6. right wing to right engine (top)
		,{ 19, 4 }			//7. right engine left curve
		,{ 20, 6 }			//8. right engine top left
		,{ 26, 6 }			//9. right engine top right
		,{ 27, 4 }			//10. right engine right curve
		,{ 25, -5 }		//11. right engine bottom right
		,{ 20, -5 }		//12. right engine bottom left
		,{ 18, -1 }		//13. right engine to right wing (bottom)
		,{ 17, -3 }		//14. right wing bottom right
		,{ 6, -5 } 		//15. right wing bottom left
		,{ 6, -12 }		//16. right wing to bottom engine (top)
		,{ 4, -14 }		//17. right wing to bottom engine (bottom)
		,{ 6, -17 }		//18. bottom engine top right
		,{ 6, -20 }		//19. bottom engine mid right
		,{ 2, -25 }		//20. bottom engine bottom right
		,{ -2, -25 }		//21. bottom engine bottom left
		,{ -6, -20 }		//22. bottom engine mid left
		,{ -6, -17 }		//23. bottom engine top left
		,{ -4, -14 }		//24. bottom engine to left wing (bottom)
		,{ -6, -12 }		//25. bottom engine to left wing (top)
		,{ -6, -5 }		//26. left wing bottom right
		,{ -17, -3 }		//27. left wing bottom left
		,{ -18, -1 }		//28. left engine to left wing (bottom)
		,{ -20, -5 }		//29. left engine bottom right
		,{ -25, -5 }		//30. left engine bottom left
		,{ -27, 4 }		//31. left engine left curve
		,{ -26, 6 }		//32. left engine top left
		,{ -20, 6 }		//33. left engine top right
		,{ -19, 4 }		//34. left engine right curve
		,{ -12, 2 }		//35. left engine to left wing
		,{ -10, 4 }		//36. left wing top left
		,{ -6, 5 }			//37. left wing top right
		,{ -3, 8 }			//38. left neck
		,{ -5, 18 }		//39. left head bottom
		,{ -1, 25 }		//40. left head top
		,{ 1, 25 }			//1. right head top
	};

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < sizeof(pointsShip) / sizeof(PT); i++)
	{
		Point pt(position.getX() + pointsShip[i].x,
			position.getY() + pointsShip[i].y);
		rotate(pt, position, angle);
		glVertex2f(pt.getX(), pt.getY());
	}
	glEnd();

	// draw the flame if necessary
	if (ui.isUp())
	{
		const PT pointsFlameBottom[3][5] =
		{
			{ { -2, -25 },{ -2, -35 },{ 0, -28 },{ 2, -35 },{ 2, -25 } },
			{ { -2, -25 },{ -4,  -31 },{ -1, -29 },{ 1, -38 },{ 2, -25 } },
			{ { -2, -25 },{ -1, -38 },{ 1, -29 },{ 4,  -31 },{ 2, -25 } }
		};

		const PT pointsFlameLeft[3][5] =
		{
			{ { -25, -5 },{ -25, -15 },{ -23, -8 },{ -21, -15 },{ -21, -5 } },
			{ { -25, -5 },{ -27,  -11 },{ -24, -9 },{ -22, -16 },{ -21, -5 } },
			{ { -25, -5 },{ -24, -16 },{ -22, -9 },{ -19,  -11 },{ -21, -5 } }
		};

		const PT pointsFlameRight[3][5] =
		{
			{ { 25, -5 },{ 25, -15 },{ 23, -8 },{ 21, -15 },{ 21, -5 } },
			{ { 25, -5 },{ 27,  -11 },{ 24, -9 },{ 22, -16 },{ 21, -5 } },
			{ { 25, -5 },{ 24, -16 },{ 22, -9 },{ 19,  -11 },{ 21, -5 } }
		};

		glBegin(GL_LINE_STRIP);
		glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

		//draw the flames on the bottom engine
		int iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlameBottom[iFlame][i].x,
				position.getY() + pointsFlameBottom[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		//draw the flames on the left engine
		iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlameLeft[iFlame][i].x,
				position.getY() + pointsFlameLeft[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		//draw the flames on the right engine
		iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlameRight[iFlame][i].x,
				position.getY() + pointsFlameRight[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}

		glColor3f(1.0, 1.0, 1.0); // reset to white                                  
		glEnd();
	}
}

/********************************************
* fireWeapon() fires the ship's weapons
*    two bullets are fired with each shot
*********************************************/
void Serenity::fireWeapon(vector<Bullet*> & bullets)
{
	//limit on number of bullets
	if (bullets.size() <= 14)
	{
		//shoot from the right-hand gun
		Point gun1(position.getX() + 23, position.getY() + 6);
		rotate(gun1, position, angle);
		Bullet * newBullet1 = new Normal;
		newBullet1->fire(gun1, angle + 90);
		bullets.push_back(newBullet1);

		//shoot from the left-hand gun
		Point gun2(position.getX() - 23, position.getY() + 6);
		rotate(gun2, position, angle);
		Bullet * newBullet2 = new Normal;
		newBullet2->fire(gun2, angle + 90);
		bullets.push_back(newBullet2);
	}
}

//default constructor for X-Wing ship
X_Wing::X_Wing()
{
	thrustAmount = 1.2;
	shipSize = 25;
	firePower = 15;
}

/******************************************
* DRAW X-Wing Ship
*    draws the ship as an X-Wing fighter
*******************************************/
void X_Wing::draw(const Interface & ui)
{
	// ultra simple point
	struct PT
	{
		int x;
		int y;
	};

	// draw the ship                                                 
	const PT pointsShip[] =
	{  //see JPEG for corresponding numbers
		{ 1, 23 }			//1. right head top
		,{ 2, 14 }			//2. right head bottom
		,{ 4, 1 }			//3. right neck
		,{ 7, 1 }			//4. right wing top engine top
		,{ 10, -3 }			//5. right wing top engine bottom
		,{ 23, -3 }			//6. right weapon top left
		,{ 24, 13 }			//7. right weapon point
		,{ 25, -3 }			//8. right weapon top right
		,{ 25, -7 }			//9. right weapon bottom right
		,{ 23, -7 }			//10. right weapon bottom left
		,{ 10, -11 }		//11. right wing bottom
		,{ 10, -15 }		//12. right wing bottom engine bottom right
		,{ 7, -15 }			//13. right wing bottom engine bottom left
		,{ 7, -10 }			//14. right wing bottom engine top left
		,{ 6, -8 } 			//15. right wing bottom left
		,{ 2, -13 }			//16. body bottom right
		,{ -2, -13 }		//17. body bottom left
		,{ -6, -8 }			//18. left wing bottom right
		,{ -7, -10 }		//19. left bottom bottom engine top left
		,{ -7, -15 }		//20. left wing bottom engine bottom right
		,{ -10, -15 }		//21. left wing bottom engine bottom left
		,{ -10, -11 }		//22. left wing bottom
		,{ -23, -7 }		//23. left weapon bottom right
		,{ -25, -7 }		//24. left weapon bottom left
		,{ -25, -3 }		//25. left weapon top left
		,{ -24, 13 }		//26. left weapon point
		,{ -23, -3 }		//27. left weapon top right
		,{ -10, -3 }		//28. left wing top left
		,{ -7, 1 }			//29. left wing top right
		,{ -4, 1 }			//30. left neck
		,{ -2, 14 }			//31. left head bottom
		,{ -1, 23 }			//32. left head top
		,{ 1, 23 }			//1. right head top
	};

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < sizeof(pointsShip) / sizeof(PT); i++)
	{
		Point pt(position.getX() + pointsShip[i].x,
			position.getY() + pointsShip[i].y);
		rotate(pt, position, angle);
		glVertex2f(pt.getX(), pt.getY());
	}
	glEnd();

	// draw the flame if necessary
	if (ui.isUp())
	{
		const PT pointsFlameLeft[3][5] =
		{
			{ { -10, -15 },{ -10, -25 },{ -8, -18 },{ -7, -25 },{ -7, -15 } },
			{ { -10, -15 },{ -11,  -21 },{ -9, -19 },{ -7, -26 },{ -7, -15 } },
			{ { -10, -15 },{ -9, -26 },{ -7, -19 },{ -5,  -21 },{ -7, -15 } }
		};

		const PT pointsFlameRight[3][5] =
		{
			{ { 10, -15 },{ 10, -25 },{ 8, -18 },{ 7, -25 },{ 7, -15 } },
			{ { 10, -15 },{ 11,  -21 },{ 9, -19 },{ 7, -26 },{ 7, -15 } },
			{ { 10, -15 },{ 9, -26 },{ 7, -19 },{ 5,  -21 },{ 7, -15 } }
		};

		glBegin(GL_LINE_STRIP);
		glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

		glBegin(GL_LINE_STRIP);
		//draw the flames on the left engine
		int iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlameLeft[iFlame][i].x,
				position.getY() + pointsFlameLeft[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		//draw the flames on the right engine
		iFlame = random(0, 3);
		for (int i = 0; i < 5; i++)
		{
			Point pt(position.getX() + pointsFlameRight[iFlame][i].x,
				position.getY() + pointsFlameRight[iFlame][i].y);
			rotate(pt, position, angle);
			glVertex2f(pt.getX(), pt.getY());
		}

		glColor3f(1.0, 1.0, 1.0); // reset to white                                  
		glEnd();
	}
}

/****************************************
* fireWeapon() fires the ship's weapons
*    two bullets are fired
*****************************************/
void X_Wing::fireWeapon(vector<Bullet*> & bullets)
{
	//limit on number of bullets
	if (bullets.size() <= 14)
	{
		//shoot from the right-hand gun
		Point gun1(position.getX() + 24, position.getY() + 13);
		rotate(gun1, position, angle);
		Bullet * newBullet1 = new Laser;
		newBullet1->fire(gun1, angle + 90);
		bullets.push_back(newBullet1);

		//shoot from the left-hand gun
		Point gun2(position.getX() - 24, position.getY() + 13);
		rotate(gun2, position, angle);
		Bullet * newBullet2 = new Laser;
		newBullet2->fire(gun2, angle + 90);
		bullets.push_back(newBullet2);
	}
}