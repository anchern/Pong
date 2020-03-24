#ifndef PONG_GAMEOBJECT_HPP
#define PONG_GAMEOBJECT_HPP

#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char *texturesheet, int x, int y, int h, int w, bool constantlyMoving);
	~GameObject() = default;

	void setDirection(int degrees);

	void reset();
	void invertDirection();

	void collisionHandle(GameObject *gameObject);


	void move();
	void update();
	void render();

private:
	bool pointInObject(int x, int y, GameObject *gameObject);

public:
	int getYpos() const;

	int getHobj() const;

private:
	int				xStart;
	int 			yStart;
	int				xpos;
	int				ypos;
	int				hobj;
	int				wobj;
	int				directionMoving{};
	bool 			constantlyMoving;

	SDL_Texture		*objectTexture;
	SDL_Rect		srcRect{};
	SDL_Rect		dstRect{};
};


#endif
