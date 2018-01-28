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
SDL_Renderer * render = NULL;

int level = 0;
const levelBaseBPM[5] = {70, 100, 130, 160, 200};
float bpm = 70;

/*****************************************************************************/
int main(int argc, char * argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf( "SDL init error %s\n", SDL_GetError());
		return -1;
	}

    window = SDL_CreateWindow("GGJ2018 LoPacket", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 256);
    Mix_AllocateChannels(16);

    loadAssets();

// Start of a level
    bpm = levelBaseBPM[level];

    musicInit(level + 1, bpm);
    playersInit();
    gameInit();

    uint32_t fpsTimeCurrent = SDL_GetTicks();
    uint32_t fpsTimeLast = fpsTimeCurrent;

    int run = 1;
    while(run)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                run = 0;

        musicUpdate();

        fpsTimeCurrent = SDL_GetTicks();
        if (fpsTimeCurrent - fpsTimeLast < GAME_FRAME_TIME)
            continue;
        fpsTimeLast = fpsTimeCurrent;

        musicPlay();
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
