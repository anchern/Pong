#include "../inc/ScoreManager.hpp"

std::pair<int, int> ScoreManager::playersScore(0, 0);

static TTF_Font *Times = nullptr;

void ScoreManager::addScore(int playerPosition)
{
	switch (playerPosition)
	{
		case LEFT_PLAYER:
			playersScore.first++;
			break;
		case RIGHT_PLAYER:
			playersScore.second++;
			break;
		default:
			std::cout << "404: Player not found" << std::endl;
			break;
	}

}

void ScoreManager::loadFont(const char *filename, int ptsize)
{
	Times = TTF_OpenFont(filename, ptsize);
	if (Times == nullptr)
		std::cout << "Unable to load font: " << filename << std::endl << TTF_GetError() << std::endl;
}

void ScoreManager::draw()
{
	SDL_Color White = {0x00, 0x11, 0xFF};

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Times, std::to_string(playersScore.first).c_str(), White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = 150;
	Message_rect.y = 0;
	Message_rect.w = 100;
	Message_rect.h = 100;


	SDL_RenderCopy(Game::renderer, Message, nullptr, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	surfaceMessage = TTF_RenderText_Solid(Times, std::to_string(playersScore.second).c_str(), White);
	Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	Message_rect.x = 600;

	SDL_RenderCopy(Game::renderer, Message, nullptr, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

}

void ScoreManager::reset()
{
	playersScore = std::make_pair(0, 0);
}

