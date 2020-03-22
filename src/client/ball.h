/*
This class defines the ball.
*/

#ifndef BALL_H
#define BALL_H

#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Entity.h"
#include <fslazywindow.h>

using namespace std;

class Ball: public Entity {
private:
	float x, y, z;
	float vx, vy, vz;
	float initX, initY, initZ;
	float R;
	float g;


public:
	Ball(){}
	Ball(float nx, float ny, float nz);
	~Ball(){}
	void draw();
	void update(float nx, float ny, float nz, float nvx, float nvy, float nvz);
};

#endif