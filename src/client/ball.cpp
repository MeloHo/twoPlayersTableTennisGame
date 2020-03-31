#include "ball.h"

Ball::Ball()
{
	x = 0.75f;
	y = 0.0f;
	z = 1.0f;
	rad = 0.02f;
	vx =0;
	vy = 0;
	vz = 0;
	grav = -9.8;
	isOut = false;
	isHit = false;
}

Ball::Ball(float xIn, float yIn, float zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
	rad = 0.02f;
	vx =0;
	vy = 0;
	vz = 0;
	grav = -9.8;
	isOut = false;
	isHit = false;
}

void Ball::GetPosition(float &xOut, float &yOut, float &zOut)
{
	xOut = x;
	yOut = y;
	zOut = z;
}

void Ball::GetVelocity(float &vxOut, float &vyOut, float &vzOut)
{
	vxOut = vx;
	vyOut = vy;
	vzOut = vz;
}

void Ball::SetPosition(float xIn, float yIn, float zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
}

void Ball::SetVelocity(float vxIn, float vyIn, float vzIn)
{
	vx = vxIn;
	vy = vyIn;
	vz = vzIn;
}

void Ball::Move(float dt)
{
	if(z > rad){
		x += vx * dt;
		y += vy * dt;
		z += (vz*dt + 0.5*grav*dt*dt);
		vz += grav * dt;
	}
	else if((z-rad<=0) && (0<=x<=1.75) && (0.5<=y<=3.24)){
		vz = -1 * vz;
		z += (vz*dt + 0.5*grav*dt*dt);
	}
	// out of table
	else{
		isOut = true;
	}
}

void Ball::draw()
{
	const float pi = 3.14159265;

	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLE_FAN);

	for(int j = 0; j <= 64; ++j){
		double roll = (double)j * pi / 32.0;
		double c_z = cos(roll);
		double s_z = sin(roll);
		for(int i = 0; i <= 64; ++i){
			double angle = (double)i * pi / 32.0;
			double r = c_z * rad;
			double c = cos(angle);
			double s = sin(angle);
			glVertex3d((double)x + c*r, (double)y + s*r, (double)z + s_z*rad);
		}
	}

	glEnd();
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
