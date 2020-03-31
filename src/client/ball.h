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
	float grav;
	bool isOut;
	bool isHit;

public:
    Ball();
	Ball(float xIn, float yIn, float zIn);
	~Ball(){}
	void draw();
	void update(float nx, float ny, float nz, float nvx, float nvy, float nvz);
	void GetPosition(float &xOut, float &yOut, float &zOut);
	void SetPosition(float nx, float ny, float nz);
	void GetVelocity(float &vxOut, float &vyOut, float &vzOut);
	void SetVelocity(float nvx, float nvy, float nvz);
	void SetActivity(bool activity);

	bool IsActive();
	void Move(float dt);
	void CollisionCheck(float x0, float y0, float z0);
	void HitCheck(float x0, float y0, float z0, float x1, float y1, float z1);
};

#endif
