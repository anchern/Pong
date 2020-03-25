#include "../inc/GameObjManager.hpp"
#include "../inc/Game.hpp"
#include "../inc/Ball.hpp"
#include "../inc/ScoreManager.hpp"


void GameObjManager::handleObjectEvents()
{
	const Uint8 *keystates = SDL_GetKeyboardState(nullptr);

	if (keystates[SDL_SCANCODE_W])
	{
		_gameObjects[LEFT_PLAYER]->setDirection(90);
		_gameObjects[LEFT_PLAYER]->move();
	} else if (keystates[SDL_SCANCODE_S])
	{
		_gameObjects[LEFT_PLAYER]->setDirection(-90);
		_gameObjects[LEFT_PLAYER]->move();
	}
	else if (keystates[SDL_SCANCODE_SPACE])
	{
		for (auto &gameObject : _gameObjects)
			gameObject->reset();
		ScoreManager::reset();
		dynamic_cast<Ball *>(_gameObjects[BALL].get())->randomDirection();
	}
}

bool GameObjManager::pointInObject(int x, int y, GameObject *gameObject)
{
	return x > gameObject->getXPos() &&
		   y > gameObject->getYPos() &&
		   x < gameObject->getXPos() + gameObject->getWObj() &&
		   y < gameObject->getYPos() + gameObject->getHObj();
}

void GameObjManager::collisionHandle()
{
	Ball *pBall = dynamic_cast<Ball *>(_gameObjects[BALL].get());
	GameObject *gameObject = nullptr;

	for (int i = 0; i < 2; i++)
	{
		gameObject = _gameObjects[i].get();
		if (pointInObject(pBall->getXPos(), pBall->getYPos(), gameObject) ||
			pointInObject(pBall->getXPos() + pBall->getWObj(), pBall->getYPos(), gameObject) ||
			pointInObject(pBall->getXPos(), pBall->getYPos() + pBall->getHObj(), gameObject) ||
			pointInObject(pBall->getXPos() + pBall->getWObj(), pBall->getYPos() + pBall->getHObj(), gameObject)
				)
		{
			Game::soundManager.playCollisionEffect();
			pBall->reflectionX();

		}
	}
}

GameObject *GameObjManager::getObject(int objNumber)
{
	return _gameObjects[objNumber].get();
}

void GameObjManager::update()
{
	Ball *pBall;

	for (auto &gameObject : _gameObjects)
	{
		pBall = dynamic_cast<Ball *>(gameObject.get());
		gameObject->update();
		if (pBall != nullptr)
		{
			collisionHandle();
			if (pBall->getXPos() < 2)
			{
				gameObject->reset();
				Game::soundManager.playLoseEffect();
				ScoreManager::addScore(RIGHT_PLAYER);
			} else if (pBall->getXPos() + pBall->getWObj() > Game::widthWindow - 2)
			{
				gameObject->reset();
				Game::soundManager.playGoalEffect();
				ScoreManager::addScore(LEFT_PLAYER);
			}
		}
	}
}

void GameObjManager::draw()
{
	for (auto &gameObject : _gameObjects)
		gameObject->draw();
}
