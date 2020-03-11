/*
This class defines the ball.
*/

#ifndef BALL_H
#define BALL_H

#include <cstdlib>
#include <iostream>
#include "Entity.h"

class Ball: public Entity {
private:
	int posX;
	int posY;
	int velX;
	int velY;
	int r,g,b;

public:
	Ball(){}
	Ball(int initialX, int initialY, int initialVX, int initialVY);
	~Ball(){}
	void draw() const;
	void update();
};


#endif