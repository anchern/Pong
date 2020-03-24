#include "../inc/TextureManager.hpp"

SDL_Texture *TextureManager::loadTexture(const char *filename)
{
	SDL_Texture *result = NULL;

	SDL_Surface *pSurface = IMG_Load(filename);

	if (pSurface == NULL)
	{
		printf("Error image load: %s\n", IMG_GetError());
	} else
	{
		const int limit = 30;
		int width = pSurface->w;
		int height = pSurface->h;

		if ((width > limit) ||
			(height > limit))
		{
			SDL_Rect sourceDimensions;
			sourceDimensions.x = 0;
			sourceDimensions.y = 0;
			sourceDimensions.w = width;
			sourceDimensions.h = height;

			float scale = (float) limit / (float) width;
			float scaleH = (float) limit / (float) height;

			if (scaleH < scale)
			{
				scale = scaleH;
			}

			SDL_Rect targetDimensions;
			targetDimensions.x = 0;
			targetDimensions.y = 0;
			targetDimensions.w = (int) (width * scale);
			targetDimensions.h = (int) (height * scale);

			// create a 32 bits per pixel surface to Blit the image to first, before BlitScaled
			SDL_Surface *p32BPPSurface = SDL_CreateRGBSurface(
					pSurface->flags,
					sourceDimensions.w,
					sourceDimensions.h,
					32,
					pSurface->format->Rmask,
					pSurface->format->Gmask,
					pSurface->format->Bmask,
					pSurface->format->Amask);

			if (SDL_BlitSurface(pSurface, NULL, p32BPPSurface, NULL) < 0)
			{
				printf("Error did not blit surface: %s\n", SDL_GetError());
			} else
			{
				// create another 32 bits per pixel surface are the desired scale
				SDL_Surface *pScaleSurface = SDL_CreateRGBSurface(
						p32BPPSurface->flags,
						targetDimensions.w,
						targetDimensions.h,
						p32BPPSurface->format->BitsPerPixel,
						p32BPPSurface->format->Rmask,
						p32BPPSurface->format->Gmask,
						p32BPPSurface->format->Bmask,
						p32BPPSurface->format->Amask);

				// 32 bit per pixel surfaces (loaded from the original file) won't scale down with BlitScaled, suggestion to first fill the surface
				// 8 and 24 bit depth pngs did not require this
				SDL_FillRect(pScaleSurface, &targetDimensions, SDL_MapRGBA(pScaleSurface->format, 0, 0, 0, 0));

				if (SDL_BlitScaled(p32BPPSurface, NULL, pScaleSurface, NULL) < 0)
				{
					printf("Error did not scale surface: %s\n", SDL_GetError());

					SDL_FreeSurface(pScaleSurface);
					pScaleSurface = NULL;
				} else
				{
					SDL_FreeSurface(pSurface);

					pSurface = pScaleSurface;
					width = pSurface->w;
					height = pSurface->h;
				}
			}

			SDL_FreeSurface(p32BPPSurface);
			p32BPPSurface = NULL;
		}

		SDL_Texture *pTexture = SDL_CreateTextureFromSurface(Game::renderer, pSurface);

		if (pTexture == NULL)
		{
			printf("Error image load: %s\n", SDL_GetError());
		} else
		{
			SDL_SetTextureBlendMode(
					pTexture,
					SDL_BLENDMODE_BLEND);

			result = pTexture;
		}

		SDL_FreeSurface(pSurface);
		pSurface = NULL;
	}

	return result;
}

void TextureManager::draw(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect)
{
	SDL_RenderCopy(Game::renderer, texture, srcRect, dstRect);
}
