
#include "assets.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

/*****************************************************************************/
SDL_Surface * bgBmp = NULL;
SDL_Surface * packetBmp = NULL;

Mix_Chunk * bdWav = NULL;

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
    bgBmp     = SDL_LoadBMP("assets/bg_small.bmp");
    packetBmp = SDL_LoadBMP("assets/box.bmp");

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
