#ifndef PONG_SOUNDMANAGER_HPP
#define PONG_SOUNDMANAGER_HPP

#include <SDL2/SDL_mixer.h>

class SoundManager
{
public:
	SoundManager() = default;
	void init();
	void destroy();

	void loadBackgroundMusic(const char *filename);
	void loadCollisionEffect(const char *filename);
	void loadGoalEffect(const char *filename);
	void loadLoseEffect(const char *filename);
	void playBackgroundMusic();
	void playCollisionEffect();
	void playGoalEffect();
	void playLoseEffect();
private:
	Mix_Music *_backgroundMusic;
	Mix_Chunk *_collisionEffect;
	Mix_Chunk *_goalEffect;
	Mix_Chunk *_loseEffect;
};


#endif
