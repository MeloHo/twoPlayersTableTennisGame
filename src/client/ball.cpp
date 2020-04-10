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
}

Ball::Ball(float xIn, float yIn, float zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
	rad = 0.05f;
	vx =0;
	vy = 0;
	vz = 0;
}



void Ball::draw()
{
	const float pi = 3.14159265;
	glColor3ub(245, 214, 137);
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

void Ball::update(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
}
