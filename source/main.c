#include <SDL.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/time.h>

/*****************************************************************************/
float bpm = 120;

/*****************************************************************************/
#define SCREEN_RATIO        2
#define SCREEN_WIDTH        (1280 / SCREEN_RATIO)
#define SCREEN_HEIGHT       (768 / SCREEN_RATIO)
#define SCREEN_TOLERANCE    100

SDL_Window * window = NULL;
SDL_Surface * screen = NULL;

/*****************************************************************************/
int main(int argc, char * argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf( "SDL init error %s\n", SDL_GetError());
		return -1;
	}

    window = SDL_CreateWindow("Packet game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Surface * bgBmp = SDL_LoadBMP("assets/bg_small.bmp");
    Mix_Chunk * bdWav = Mix_LoadWAV("assets/bd.wav");

    SDL_BlitSurface(bgBmp, NULL, screen, NULL);
    SDL_UpdateWindowSurface(window);

    uint32_t beatTime = (uint32_t) ((60.0f * 1000.0f) / bpm);
    uint32_t timeLast = SDL_GetTicks();
    int32_t timeAcc = 0;

    int keysCode[3] = {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A};
    int keys[3] = {0, 0, 0};
    int keysStamp[3] = {0, 0, 0};
    int keyLast = 0;

    int run = 1;
    while(run)
    {
        uint32_t timeCurrent = SDL_GetTicks();
        timeAcc += timeCurrent - timeLast;
        timeLast = timeCurrent;

        int32_t timeDelta = timeAcc - beatTime;
        if (timeDelta >= 0) {
            Mix_PlayChannel(-1, bdWav, 0);
            timeAcc -= beatTime;
        }

        int inBeat = 0;
        int32_t timeToNextBeat = beatTime - timeAcc;
        int32_t timeToPreviousBeat = timeAcc;
        if (timeToNextBeat < SCREEN_TOLERANCE ||
            timeToPreviousBeat < SCREEN_TOLERANCE)
            inBeat = 1;

        const uint8_t * keyStates = SDL_GetKeyboardState(NULL);

        int keyNew = -1;
        for (int i = 0; i < 3; i++) {
            int k = keyStates[keysCode[i]];
            if (k && !keys[i]) {
                keysStamp[i] = SDL_GetTicks();
                if (inBeat) keyNew = i;
            }
            keys[i] = k;
        }

        int dir = 0;
        if (keyNew >= 0) {
            dir = keyNew - keyLast;
            if (dir == -2) dir = 1;
            if (dir ==  2) dir = -1;
            keyLast = keyNew;
        }

        if (dir) printf("Dir %i\n", dir);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) run = 0;
        }


        //SDL_Flip(screen);
    }

    SDL_DestroyWindow(window);

	Mix_FreeChunk(bdWav);

    Mix_Quit();
	SDL_Quit();

    return 0;
}
