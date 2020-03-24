#include "../inc/Game.hpp"
#include "../inc/GameObject.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/AILogic.hpp"

#include <SDL2/SDL_ttf.h>

#include <ctime>
#include <random>

Game *Game::pInstance = nullptr;
SDL_Renderer *Game::renderer = nullptr;


GameObject	*playerRacquet;
GameObject	*AIRacquet;
GameObject	*ball;

AILogic			*AI;

int getRandomNumber(int low, int high)
{
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<> id(low, high);
	return (id(gen));
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);
		std::cout << "Subsystems initialised..." << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
			std::cout << "Window created." << std::endl;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0x1E, 0x8A, 0x00, 0xFF);
			std::cout << "Renderer created." << std::endl;
		}
		isRunning = true;
	} else
		isRunning = false;

	ScoreManager::loadFont("assets/Times.ttf", 14);

	playerRacquet = new GameObject("assets/player.png", 10, height / 2 - 50, 100, 20, false);

	AIRacquet = new GameObject("assets/ai.png", width - 30, height / 2 - 50, 100, 20, false);

	ball = new GameObject("assets/ball.png", width / 2 - 10, height / 2 - 10, 30, 30, true);

	ball->setDirection(getRandomNumber(1, 360));

	AI = new AILogic(ball, AIRacquet);

}

void Game::handleGameEvents()
{
	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	else if (keystates[SDL_SCANCODE_W])
	{
		playerRacquet->setDirection(90);
		playerRacquet->move();
	}
	else if (keystates[SDL_SCANCODE_S])
	{
		playerRacquet->setDirection(-90);
		playerRacquet->move();
	}
//	else if (keystates[SDL_SCANCODE_SPACE])
//	{
//		playerRacquet->reset();
//		ball->reset();
//		ball->setDirection(getRandomNumber(1, 360));
//		AIRacquet->reset();
//		ScoreManager::reset();
//	}
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	handleGameEvents();
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	ScoreManager::draw();
	playerRacquet->render();
	AIRacquet->render();
	ball->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	AI->update();
	playerRacquet->update();
	ball->update();
	ball->collisionHandle(playerRacquet);
	ball->collisionHandle(AIRacquet);
}

void Game::clean()
{
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned." << std::endl;
}

bool Game::running()
{
	return isRunning;
}

Game *Game::getInstance()
{
	if (!pInstance)
		pInstance = new Game();
	return pInstance;
}
