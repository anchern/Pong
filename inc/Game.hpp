#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include <iostream>

class Game
{
public:
	static Game *getInstance();

	void init(const char *title, int width, int height, bool fullscreen);

	void handleEvents();

	void update();

	void render();

	void clean();

	bool running();

	static SDL_Renderer *renderer;

private:
	Game() = default;
	Game(const Game &);
	Game &operator=(Game &);

	void handleGameEvents();

private:
	bool isRunning;
	SDL_Window *window;

	static Game *pInstance;
};

int getRandomNumber(int low, int high);

#endif
