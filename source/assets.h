#ifndef ASSETS_H
#define ASSETS_H

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>

extern SDL_Surface * bgBmp;
extern SDL_Surface * packetBmp;

extern Mix_Chunk * musicTracks[2][6];
extern Mix_Chunk * musicKeys[3];

extern Mix_Chunk * musicTimeBeat;
extern Mix_Chunk * musicTimeDelivered;

extern Mix_Chunk * musicMonster;
extern Mix_Chunk * musicBird;
extern Mix_Chunk * musicGear;

/*****************************************************************************/
void loadAssets();
void unloadAssets();

#endif
