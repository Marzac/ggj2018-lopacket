#include "config.h"
#include "assets.h"
#include "game.h"
#include "music.h"
#include "players.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************************************/
uint32_t timeCurrent;
uint32_t timeLast;
int32_t  timeAcc;

int musicBeatWindow;
int musicBeatLength;

/*****************************************************************************/
void musicInit(int track, float bpm)
{
    timeAcc = 0;
    timeLast = SDL_GetTicks();
    timeCurrent = timeLast;

    musicBeatLength = (uint32_t) ((60.0f * 1000.0f) / bpm);
    musicBeatWindow = 1;
}

void musicUpdate()
{
    timeCurrent = SDL_GetTicks();
    timeAcc += timeCurrent - timeLast;
    timeLast = timeCurrent;

    int32_t timeDelta = timeAcc - musicBeatLength;
    if (timeDelta >= 0) {
        Mix_PlayChannel(-1, bdWav, 0);
        timeAcc -= musicBeatLength;
    }

    musicBeatWindow = 0;
    int32_t timeToNextBeat = musicBeatLength - timeAcc;
    int32_t timeToPreviousBeat = timeAcc;
    if (timeToNextBeat < SCREEN_TOLERANCE ||
        timeToPreviousBeat < SCREEN_TOLERANCE)
        musicBeatWindow = 1;
}

