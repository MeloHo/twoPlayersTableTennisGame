/*
Base class
*/

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	virtual void draw() const = 0;
	static double timeInvertal = 0.1;
	
};

#endif