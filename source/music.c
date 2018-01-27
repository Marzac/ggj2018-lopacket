#include "config.h"
#include "assets.h"
#include "game.h"
#include "music.h"
#include "players.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*****************************************************************************/
uint32_t timeCurrent;
uint32_t timeLast;
int32_t  timeAcc;

int musicBeatWindow;
int musicBeatLength;

int musicTrack;
int musicVariation;
float musicTrackLevels[6];
float musicTrackLevelsNext[6];

/*****************************************************************************/
void musicPlay();

/*****************************************************************************/
void musicInit(int track, float bpm)
{
    timeAcc = 0;
    timeLast = SDL_GetTicks();
    timeCurrent = timeLast;

    musicBeatLength = (uint32_t) ((60.0f * 1000.0f) / bpm);
    musicBeatWindow = 1;

    musicTrack = track;
    memset(musicTrackLevels, 0, 6 * sizeof(float));
    memset(musicTrackLevelsNext, 0, 6 * sizeof(float));

    Mix_HaltChannel(-1);
    for (int c = 0; c < 6; c++) {
        Mix_VolumeChunk(musicTracks[musicTrack][c], 0);
        Mix_PlayChannel(2+c, musicTracks[musicTrack][c], -1);
    }
}

void musicUpdate()
{
    timeCurrent = SDL_GetTicks();
    timeAcc += timeCurrent - timeLast;
    timeLast = timeCurrent;

    int32_t timeDelta = timeAcc - musicBeatLength;
    if (timeDelta >= 0) {
        Mix_PlayChannel(0, bdWav, 0);
        timeAcc -= musicBeatLength;
    }

    musicBeatWindow = 0;
    int32_t timeToNextBeat = musicBeatLength - timeAcc;
    int32_t timeToPreviousBeat = timeAcc;
    if (timeToNextBeat < MUSIC_TOLERANCE ||
        timeToPreviousBeat < MUSIC_TOLERANCE)
        musicBeatWindow = 1;

    musicPlay();
}

/*****************************************************************************/
void musicSetVariation(int variation)
{
    if (musicTrack == 1) {
        memset(musicTrackLevelsNext, 0, 6 * sizeof(float));
        musicVariation = variation;
        if (musicVariation == MUSIC_FULL) {
            musicTrackLevelsNext[3] = 100.0f;
            musicTrackLevelsNext[4] = 100.0f;
            musicTrackLevelsNext[5] = 100.0f;
        }else if (musicVariation == MUSIC_BASIC) {
            musicTrackLevelsNext[0] = 100.0f;
        }
    }
}

/*****************************************************************************/
void musicPlay()
{
    //1.0 / 1.0f + t / FPS
    for (int c = 0; c < 6; c++) {
        musicTrackLevels[c] = musicTrackLevelsNext[c] - (musicTrackLevelsNext[c] - musicTrackLevels[c]) * 0.98f;
        Mix_VolumeChunk(musicTracks[musicTrack][c], musicTrackLevels[c]);
    }
}


