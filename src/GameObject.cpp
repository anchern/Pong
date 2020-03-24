#include "../inc/GameObject.hpp"
#include "../inc/TextureManager.hpp"
#include "../inc/ScoreManager.hpp"

GameObject::GameObject(const char *texturesheet, int x, int y, int h, int w, bool constantlyMoving)
{
	objectTexture = TextureManager::loadTexture(texturesheet, 30);
	xpos = x;
	ypos = y;
	xStart = x;
	yStart = y;
	hobj = h;
	wobj = w;
	this->constantlyMoving = constantlyMoving;
}

void GameObject::setDirection(int degrees)
{
	directionMoving = degrees;
}

void GameObject::move()
{
	int tmp = 5;

	if (constantlyMoving)
		tmp = 8;
	xpos += (int) std::round(std::cos(directionMoving * M_PI / 180) * tmp);
	ypos -= (int) std::round(std::sin(directionMoving * M_PI / 180) * tmp);
	if (ypos < 1)
	{
		if (constantlyMoving)
			invertDirection();
		ypos = 1;
	} else if (ypos + hobj > 639)
	{
		if (constantlyMoving)
			invertDirection();
		ypos = 639 - hobj;
	} else if (constantlyMoving && (xpos < 2 || xpos + wobj > 798))
	{
		reset();
		if (directionMoving > 0)
			directionMoving -= 180;
		else
			directionMoving += 180;
	}
}

void GameObject::update()
{
	if (constantlyMoving)
		move();

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.h = hobj;
	dstRect.w = wobj;
	dstRect.x = xpos;
	dstRect.y = ypos;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &dstRect);
}

void GameObject::reset()
{
	if (xpos < 2)
		ScoreManager::addScore(RIGHT_PLAYER);
	else if (xpos + wobj > 798)
		ScoreManager::addScore(LEFT_PLAYER);
	xpos = xStart;
	ypos = yStart;
	std::cout << ScoreManager::playersScore.first << " " << ScoreManager::playersScore.second << std::endl;
}

void GameObject::invertDirection()
{
	directionMoving = -directionMoving;
}

bool GameObject::pointInObject(int x, int y, GameObject *gameObject)
{
	return x > gameObject->xpos &&
		   y > gameObject->ypos &&
		   x < gameObject->xpos + gameObject->wobj &&
		   y < gameObject->ypos + gameObject->hobj;
}

void GameObject::collisionHandle(GameObject *gameObject)
{
	if (constantlyMoving)
	{
		if (pointInObject(xpos, ypos, gameObject) ||
			pointInObject(xpos + wobj, ypos, gameObject) ||
			pointInObject(xpos, ypos + hobj, gameObject) ||
			pointInObject(xpos + wobj, ypos + hobj, gameObject)
				)
			directionMoving = 180 - directionMoving;
	}
}

int GameObject::getYpos() const
{
	return ypos;
}

int GameObject::getHobj() const
{
	return hobj;
}
