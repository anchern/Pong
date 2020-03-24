//
// Created by anton on 22/03/2020.
//

#ifndef PONG_TEXTUREMANAGER_HPP
#define PONG_TEXTUREMANAGER_HPP

# include "Game.hpp"

class TextureManager
{
public:
	static SDL_Texture *loadTexture(const char *filename);
	static void draw(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect);
private:
};


#endif //PONG_TEXTUREMANAGER_HPP
