#include "config.h"
#include "assets.h"
#include "game.h"
#include "music.h"
#include "players.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/time.h>

/*****************************************************************************/
SDL_Window * window = NULL;
SDL_Surface * screen = NULL;
float bpm = 120;

/*****************************************************************************/
int main(int argc, char * argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf( "SDL init error %s\n", SDL_GetError());
		return -1;
	}

    window = SDL_CreateWindow("GGJ2018 LoPacket", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    loadAssets();
    musicInit(0, 120.0f);
    playersInit();

    int run = 1;
    while(run)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                run = 0;

        musicUpdate();
        playersUpdate();

        gameUpdate();
        gameDraw();

    }

    SDL_DestroyWindow(window);
    unloadAssets();

    Mix_Quit();
	SDL_Quit();

    return 0;
}
