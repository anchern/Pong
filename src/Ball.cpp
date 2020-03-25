#include "../inc/Ball.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/Game.hpp"

namespace
{
	int getRandomNumber(int low, int high)
	{
		std::mt19937 gen(time(nullptr));
		std::uniform_int_distribution<> id(low, high);
		return (id(gen));
	}

	int getBallDitection()
	{
		int result = getRandomNumber(-180, 179);

		if ((result <= 95 && result >= 90) || (result <= -85 && result >= -90) ||
			(result <= 5 && result >= 0) || (result >= -180 && result <= -175))
			result += 5;
		else if ((result >= 85 && result < 90) || (result >= -95 && result < -90) ||
				(result >= -5 && result < 0) || (result >= 175 && result <= 179))
			result -= 5;
		return result;
	}
}

Ball::Ball(const char *texturesheet, int x, int y, int h, int w) :
GameObject(texturesheet, x, y, h, w)
{
	directionMoving = getBallDitection();
	speedObj = 7;

}

void Ball::reflectionY()
{
	directionMoving = -directionMoving;
}

void Ball::reflectionX()
{
	if (directionMoving == 0)
		directionMoving = 180;
	else if (std::abs(directionMoving) > 90)
		directionMoving = ((directionMoving > 0) ? 180 : -180) - directionMoving;
	else
		directionMoving += (directionMoving > 0) ? 90 : -90;
}

void Ball::reset()
{
	xPos = xStart;
	yPos = yStart;
}

void Ball::update()
{
	move();
	GameObject::update();
}

void Ball::move()
{
	xPos += (int) std::round(std::cos(directionMoving * M_PI / 180) * speedObj);
	yPos -= (int) std::round(std::sin(directionMoving * M_PI / 180) * speedObj);
	if (yPos < 1)
	{
		reflectionY();
		yPos = 1;
	}
	else if (yPos + hObj > Game::heightWindow - 1)
	{
		reflectionY();
		yPos = Game::heightWindow - 1 - hObj;
	}
	else if ((xPos < 2 || xPos + wObj > Game::widthWindow - 2))
	{
		if (directionMoving > 0)
			directionMoving -= 180;
		else
			directionMoving += 180;
	}
}

void Ball::randomDirection()
{
	directionMoving = getBallDitection();
}
