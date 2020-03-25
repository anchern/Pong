#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include "GameObject.hpp"

#include <ctime>
#include <random>

class Ball : public GameObject
{
public:
	Ball(const char *texturesheet, int x, int y, int h, int w);

	void randomDirection();

	void reset() override;

	void move() override;

	void update() override;
	void reflectionY();
	void reflectionX();

};


#endif
