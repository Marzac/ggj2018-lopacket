/*
The MIT License (MIT)
Copyright (c) 2015-2018 The Love transmission team
Till Gilsbach, Frederic Meslin, Francisco Chaves, Christian LeFou

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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


/*****************************************************************************/
int main(int argc, char * argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf( "SDL init error %s\n", SDL_GetError());
		return -1;
	}

    window = SDL_CreateWindow("GGJ2018 : Transmission of Love", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 256);
    Mix_AllocateChannels(16);

    loadAssets();

    gameInitMenu(0);

    uint32_t fpsTimeCurrent = SDL_GetTicks();
    uint32_t fpsTimeLast = fpsTimeCurrent;

    int run = 1;
    while(run)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                run = 0;

        musicUpdateRealtime();

        fpsTimeCurrent = SDL_GetTicks();
        if (fpsTimeCurrent - fpsTimeLast < GAME_FRAME_TIME)
            continue;
        fpsTimeLast = fpsTimeCurrent;

        gameUpdate();
    }

    SDL_DestroyWindow(window);
    unloadAssets();

    Mix_Quit();
	SDL_Quit();

    return 0;
}
