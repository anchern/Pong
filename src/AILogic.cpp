#include "../inc/AILogic.hpp"

AILogic::AILogic(GameObject *ball, GameObject *AIRacquet)
{
	this->ball = ball;
	this->AIRacquet = AIRacquet;
}

void AILogic::update()
{
	if (AIRacquet->getYpos() + 0.5 * AIRacquet->getHobj() > ball->getYpos() + 0.5 * ball->getHobj())
	{
		AIRacquet->setDirection(90);
		AIRacquet->move();
	}
	else if (AIRacquet->getYpos() + 0.5 * AIRacquet->getHobj() < ball->getYpos() + 0.5 * ball->getHobj())
	{
		AIRacquet->setDirection(-90);
		AIRacquet->move();
	}
	AIRacquet->update();
}
