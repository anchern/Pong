#include "../inc/Game.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/AILogic.hpp"
#include "../inc/TextureManager.hpp"
#include "../inc/Ball.hpp"
#include "../inc/GameObjManager.hpp"

#include <SDL2/SDL_ttf.h>

Game 			*Game::_pInstance = nullptr;

int				Game::widthWindow;
int				Game::heightWindow;
SDL_Renderer	*Game::renderer = nullptr;

SDL_Texture		*backgroundTexture = nullptr;
GameObjManager	objManager;
AILogic			*AI;



void Game::init(const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;
	widthWindow = width;
	heightWindow = height;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);
		std::cout << "Subsystems initialised..." << std::endl;

		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (_window)
			std::cout << "Window created." << std::endl;
		renderer = SDL_CreateRenderer(_window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0x1E, 0x8A, 0x00, 0xFF);
			std::cout << "Renderer created." << std::endl;
		}
		_isRunning = true;
	} else
		_isRunning = false;

	ScoreManager::loadFont("assets/Times.ttf", 14);
	backgroundTexture = TextureManager::loadTexture("assets/background.png", 800);

	objManager.addObject<GameObject, const char *, int, int, int, int>("assets/player.png", 10, height / 2 - 50, 100, 20);
	objManager.addObject<GameObject, const char *, int, int, int, int>("assets/ai.png", width - 30, height / 2 - 50, 100, 20);
	objManager.addObject<Ball, const char *, int, int, int, int>("assets/ball.png", width / 2 - 10, height / 2 - 10, 30, 30);


	AI = new AILogic(objManager.getObject(BALL), objManager.getObject(RIGHT_PLAYER));

}


void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	objManager.handleObjectEvents();
	switch (event.type)
	{
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
	ScoreManager::draw();
	objManager.draw();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	objManager.update();
	AI->update();
}

void Game::clean()
{
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned." << std::endl;
}

bool Game::running()
{
	return _isRunning;
}

Game *Game::getInstance()
{
	if (!_pInstance)
		_pInstance = new Game();
	return _pInstance;
}
