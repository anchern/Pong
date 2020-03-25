#include "../inc/GameObject.hpp"
#include "../inc/TextureManager.hpp"
#include "../inc/Game.hpp"

GameObject::GameObject(const char *texturesheet, int x, int y, int h, int w)
{
	objectTexture = TextureManager::loadTexture(texturesheet, 30);
	xPos = x;
	yPos = y;
	xStart = x;
	yStart = y;
	hObj = h;
	wObj = w;
	speedObj = 5;
}

void GameObject::setDirection(int degrees)
{
	directionMoving = degrees;
}

void GameObject::move()
{
	xPos += (int) std::round(std::cos(directionMoving * M_PI / 180) * speedObj);
	yPos -= (int) std::round(std::sin(directionMoving * M_PI / 180) * speedObj);
	if (yPos < 1)
		yPos = 1;
	else if (yPos + hObj > Game::heightWindow - 1)
		yPos = Game::heightWindow - 1 - hObj;
}

void GameObject::update()
{
	dstRect.h = hObj;
	dstRect.w = wObj;
	dstRect.x = xPos;
	dstRect.y = yPos;
}

void GameObject::draw()
{
	SDL_RenderCopy(Game::renderer, objectTexture, nullptr, &dstRect);
}

void GameObject::reset()
{
	xPos = xStart;
	yPos = yStart;
}

int GameObject::getYPos() const
{
	return yPos;
}

int GameObject::getHObj() const
{
	return hObj;
}

int GameObject::getXPos() const
{
	return xPos;
}

int GameObject::getWObj() const
{
	return wObj;
}
