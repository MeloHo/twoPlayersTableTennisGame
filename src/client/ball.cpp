#include "ball.h"
#include <iostream>
// #include <GL/glut.h>
// #include <GL/glu.h>
// #include <GL/gl.h>
#include <math.h>

Ball::Ball()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	R = 0.2f;
}

Ball::Ball(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
	R = 0.2f;
}

void Ball::Draw()
{
	glColor3f(0.99f, 0.64f, 0.06f);
	glEnable(GL_LIGHTING);
	gluSphere(R, 100, 100);
	glDisable(GL_LIGHTING);
}

void Ball::update(float nx, float ny, float nz, float nvx, float nvy, float nvz)
{
	x = nx;
	y = ny;
	z = nz;
	vx = nvx;
	vy = nvy;
	vz = nvz;
}