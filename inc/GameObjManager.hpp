#ifndef PONG_GAMEOBJMANAGER_HPP
#define PONG_GAMEOBJMANAGER_HPP

#include "GameObject.hpp"
#include <vector>
#include <bits/unique_ptr.h>

class GameObjManager
{
public:
	template<typename T, typename... TArgs>
	void addObject(TArgs &&...mArgs)
	{
		T *c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<GameObject> uPtr{c};
		_gameObjects.emplace_back(std::move(uPtr));
	}

	void update();

	void draw();

	void collisionHandle();
	void handleObjectEvents();



	GameObject *getObject(int objNumber);

private:
	bool pointInObject(int x, int y, GameObject *gameObject);

private:
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
};


#endif
