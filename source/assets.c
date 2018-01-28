#include "config.h"
#include "assets.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdio.h>

/*****************************************************************************/
SDL_Surface * skyBmp = NULL;
SDL_Surface * waterBmp = NULL;
SDL_Surface * cliffBmp = NULL;
SDL_Surface * gearBmp = NULL;
SDL_Surface * basketBmp = NULL;
SDL_Surface * itemBmp[4];
SDL_Surface * getReadyBmp;
SDL_Surface * vogelBmp[9];

SDL_Texture * skyTxt;
SDL_Texture * waterTxt;
SDL_Texture * cliffTxt;
SDL_Texture * gearTxt;
SDL_Texture * basketTxt;
SDL_Texture * itemTxt[4];
SDL_Texture * gearTxt;
SDL_Texture * getReadyTxt;
SDL_Texture * vogelTxt[9];

Mix_Chunk * musicTracks[2][6];
Mix_Chunk * musicKeys[3];

Mix_Chunk * musicTimeBeat;
Mix_Chunk * musicTimeDelivered;

Mix_Chunk * musicMonster;
Mix_Chunk * musicBird;
Mix_Chunk * musicGear;

/*****************************************************************************/
void loadAssets()
{
    skyBmp = IMG_Load("assets/sky.png");
    waterBmp = IMG_Load("assets/water.png");
    cliffBmp = IMG_Load("assets/cliff.png");
    gearBmp = IMG_Load("assets/gear.png");
    basketBmp = IMG_Load("assets/basket.png");
    itemBmp[0] = IMG_Load("assets/item1.png");
    getReadyBmp = IMG_Load("assets/getready.png");

    char path[] = "assets/bx-s.png";
    for (int b = 0; b < 9; b++) {
        path[8] = b+1 + '0';
        vogelBmp[b] = IMG_Load(path);
        vogelTxt[b] = SDL_CreateTextureFromSurface(render, vogelBmp[b]);
    }

    skyTxt = SDL_CreateTextureFromSurface(render, skyBmp);
    waterTxt = SDL_CreateTextureFromSurface(render, waterBmp);
    cliffTxt = SDL_CreateTextureFromSurface(render, cliffBmp);
    gearTxt = SDL_CreateTextureFromSurface(render, gearBmp);
    basketTxt = SDL_CreateTextureFromSurface(render, basketBmp);
    itemTxt[0] = SDL_CreateTextureFromSurface(render, itemBmp[0]);
    getReadyTxt = SDL_CreateTextureFromSurface(render, getReadyBmp);

// General
    musicTimeBeat = Mix_LoadWAV("assets/music/general/TIME-BEAT.wav");
    musicTimeDelivered = Mix_LoadWAV("assets/music/general/TIME-DELIVERED.wav");

// Level1 music
    musicTracks[1][0] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLNS.wav");
    musicTracks[1][1] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLN-1.wav");
    musicTracks[1][2] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLN-2.wav");
    musicTracks[1][3] = Mix_LoadWAV("assets/music/level1/STRINGS-ALL.wav");
    musicTracks[1][4] = Mix_LoadWAV("assets/music/level1/STRINGS-EXTRA-BASSES.wav");
    musicTracks[1][5] = Mix_LoadWAV("assets/music/level1/KEYBOARDS-EXTRA.wav");

// Percussions
    musicKeys[0] = Mix_LoadWAV("assets/music/general/TASTER-1.wav");
    musicKeys[1] = Mix_LoadWAV("assets/music/general/TASTER-2.wav");
    musicKeys[2] = Mix_LoadWAV("assets/music/general/TASTER-3.wav");

// Monsters / misc
    musicMonster = Mix_LoadWAV("assets/music/general/MONSTER.wav");
    musicBird = Mix_LoadWAV("assets/music/general/BIRD.wav");
    musicGear = Mix_LoadWAV("assets/music/general/GEAR.wav");

}

void unloadAssets()
{


}
