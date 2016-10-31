/*********************************
* velocity.h
* defines the velocity class
**********************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
public:
	Velocity();
	Velocity(float, float);
	float getDx();
	float getDy();
	void setDx(float);
	void setDy(float);
private:
	float velX;	//velocity variable for the x-axis
	float velY; //velocity variable for the y-axis
};


#endif