#include "../inc/SoundManager.hpp"

void SoundManager::init()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void SoundManager::loadBackgroundMusic(const char *filename)
{
	_backgroundMusic = Mix_LoadMUS(filename);
}

void SoundManager::destroy()
{
	Mix_FreeMusic(_backgroundMusic);
}

void SoundManager::playBackgroundMusic()
{
	Mix_PlayMusic(_backgroundMusic, -1);
}

void SoundManager::loadCollisionEffect(const char *filename)
{
	_collisionEffect = Mix_LoadWAV(filename);
}

void SoundManager::playCollisionEffect()
{
	Mix_PlayChannel(-1, _collisionEffect, 0);
}

void SoundManager::loadGoalEffect(const char *filename)
{
	_goalEffect = Mix_LoadWAV(filename);
}

void SoundManager::playGoalEffect()
{
	Mix_PlayChannel(-1, _goalEffect, 0);
}

void SoundManager::loadLoseEffect(const char *filename)
{
	_loseEffect = Mix_LoadWAV(filename);
}

void SoundManager::playLoseEffect()
{
	Mix_PlayChannel(-1, _loseEffect, 0);
}
