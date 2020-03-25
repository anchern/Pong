#ifndef PONG_SCOREMANAGER_HPP
#define PONG_SCOREMANAGER_HPP

#include <utility>
#include <iostream>
#include <sstream>

#include <SDL2/SDL_ttf.h>

#include "../inc/Game.hpp"


class ScoreManager
{
public:
	ScoreManager() = default;

	static void draw();

	static void addScore(int playerPosition);
	static void loadFont(const char *filename, int ptsize);
	static void reset();
	static std::pair<int, int> playersScore;
};


#endif
