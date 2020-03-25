#include "../inc/AILogic.hpp"

AILogic::AILogic(GameObject *ball, GameObject *AIRacquet)
{
	this->_ball = ball;
	this->_AIRacquet = AIRacquet;
}

void AILogic::update()
{
	if (_AIRacquet->getYPos() + 0.5 * _AIRacquet->getHObj() > _ball->getYPos() + 0.5 * _ball->getHObj())
	{
		_AIRacquet->setDirection(90);
		_AIRacquet->move();
	}
	else if (_AIRacquet->getYPos() + 0.5 * _AIRacquet->getHObj() < _ball->getYPos() + 0.5 * _ball->getHObj())
	{
		_AIRacquet->setDirection(-90);
		_AIRacquet->move();
	}
	_AIRacquet->update();
}
