#ifndef ASSETS_H
#define ASSETS_H

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>

extern SDL_Surface * bgBmp;
extern SDL_Surface * packetBmp;

extern Mix_Chunk * bdWav;
Mix_Chunk * musicTracks[2][6];

/*****************************************************************************/
void loadAssets();
void unloadAssets();

#endif
