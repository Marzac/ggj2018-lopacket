
#include "assets.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

/*****************************************************************************/
SDL_Surface * bgBmp = NULL;
SDL_Surface * packetBmp = NULL;

Mix_Chunk * bdWav = NULL;

/*****************************************************************************/
void loadAssets()
{
    bgBmp     = SDL_LoadBMP("assets/bg_small.bmp");
    packetBmp = SDL_LoadBMP("assets/box.bmp");

    bdWav = Mix_LoadWAV("assets/bd.wav");

}

void unloadAssets()
{


}
