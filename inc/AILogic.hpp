#ifndef PONG_AILOGIC_HPP
#define PONG_AILOGIC_HPP

#include "GameObject.hpp"

class AILogic
{
public:
	AILogic(GameObject *ball, GameObject *AIRacquet);
	void update();
private:
	GameObject *ball;
	GameObject *AIRacquet;
};


#endif
