#ifndef ASSETS_H
#define ASSETS_H

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>

extern SDL_Surface * skyBmp;
extern SDL_Surface * waterBmp;
extern SDL_Surface * cliffBmp;
extern SDL_Surface * gearBmp;
extern SDL_Surface * basketBmp;
extern SDL_Surface * itemBmp[4];
extern SDL_Surface * getReadyBmp;
extern SDL_Surface * vogelBmp[9];
extern SDL_Surface * vogelBackBmp[9];
extern SDL_Surface * pigsBmp[2];
extern SDL_Surface * oinkBmp[2];

extern SDL_Texture * skyTxt;
extern SDL_Texture * waterTxt;
extern SDL_Texture * cliffTxt;
extern SDL_Texture * gearTxt;
extern SDL_Texture * basketTxt;
extern SDL_Texture * itemTxt[4];
extern SDL_Texture * gearTxt;
extern SDL_Texture * getReadyTxt;
extern SDL_Texture * vogelTxt[9];
extern SDL_Texture * vogelBackTxt[9];
extern SDL_Texture * pigsTxt[2];
extern SDL_Texture * oinkTxt[2];

extern Mix_Chunk * musicTracks[3][6];
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
