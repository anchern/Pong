#ifndef PONG_GAMEOBJECT_HPP
#define PONG_GAMEOBJECT_HPP

#include <SDL2/SDL.h>

#include "IEntity.hpp"

class GameObject : public IEntity
{
public:
	GameObject(const char *texturesheet, int x, int y, int h, int w);
	~GameObject() = default;

	void setDirection(int degrees);

	virtual void reset();

	virtual void move();
	virtual void update() override;
	void draw() override;

	int getYPos() const;
	int getHObj() const;
	int getXPos() const;
	int getWObj() const;

protected:
	int				xStart;
	int 			yStart;
	int				xPos;
	int				yPos;
	int 			speedObj;
	int				hObj;
	int				wObj;
	int				directionMoving;

	SDL_Texture		*objectTexture;
	SDL_Rect		dstRect;
};


#endif
