
#include "assets.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

/*****************************************************************************/
SDL_Surface * bgBmp = NULL;
SDL_Surface * packetBmp = NULL;

Mix_Chunk * bdWav = NULL;

Mix_Chunk * musicTracks[2][6];

/*****************************************************************************/
void loadAssets()
{
    bgBmp     = SDL_LoadBMP("assets/bg_small.bmp");
    packetBmp = SDL_LoadBMP("assets/box.bmp");

    bdWav = Mix_LoadWAV("assets/bd.wav");

// Level1 music
    musicTracks[1][0] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLNS.wav");
    musicTracks[1][1] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLN-1.wav");
    musicTracks[1][2] = Mix_LoadWAV("assets/music/level1/STRINGS-NO-VLN-2.wav");
    musicTracks[1][3] = Mix_LoadWAV("assets/music/level1/STRINGS-ALL.wav");
    musicTracks[1][4] = Mix_LoadWAV("assets/music/level1/STRINGS-EXTRA-BASSES.wav");
    musicTracks[1][5] = Mix_LoadWAV("assets/music/level1/KEYBOARDS-EXTRA.wav");
}

void unloadAssets()
{


}
