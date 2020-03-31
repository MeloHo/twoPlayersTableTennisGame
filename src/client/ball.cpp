#include "ball.h"

Ball::Ball()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	rad = 0.2f;
	vx =0;
	vy = 0;
	vz = 0;
	grav = 9.8;
	isActive = false;
	isHit = false;
}

Ball::Ball(float xIn, float yIn, float zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
	rad = 0.2f;
	vx =0;
	vy = 0;
	vz = 0;
	grav = 9.8;
	isActive = false;
	isHit = false;
}

void Ball::draw()
{
	const float pi = 3.14159265;

	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLE_FAN);

	// for(int j = 0; j <= 64; ++j){
	// 	float roll = (float)j * pi / 32.0;
	// 	float c_z = cos(roll);
	// 	float s_z = sin(roll);
	// 	for(int i = 0; i <= 64; ++i){
	// 		float angle = (float)i * pi / 32.0;
	// 		float r = c_z * rad;
	// 		float c = cos(angle);
	// 		float s = sin(angle);
	// 		glVertex3f((float)x + c*r, (float)y + s*r, (float)z + s_z*rad);
	// 	}
	// }
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
