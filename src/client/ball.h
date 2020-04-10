/*
This class defines the ball.
*/

#ifndef BALL_H
#define BALL_H

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include "Entity.h"
#include "fssimplewindow.h"

using namespace std;

class Ball: public Entity {
private:
	float x, y, z;
	float vx, vy, vz;
	float rad;

public:
    Ball();
	Ball(float xIn, float yIn, float zIn);
	~Ball(){}
	void draw();
	void update(float nx, float ny, float nz);

};

#endif
