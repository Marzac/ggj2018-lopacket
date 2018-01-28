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
int musicVariationLength;

float musicTrackLevels[6];
float musicTrackLevelsNext[6];


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

    Mix_VolumeChunk(musicTimeBeat, 128.0f * 0.25f);
    for (int k = 0; k < 3; k++)
        Mix_VolumeChunk(musicKeys[k], 128.0f * 0.15f);

    Mix_HaltChannel(-1);
    for (int c = 0; c < 6; c++) {
        Mix_VolumeChunk(musicTracks[musicTrack][c], 0);
        Mix_PlayChannel(CHANNEL_MUSIC_TRACK1+c, musicTracks[musicTrack][c], -1);
    }

    musicSetVariation(MUSIC_BASIC);
}

/*****************************************************************************/
void musicUpdate()
{
    for (int c = 0; c < 6; c++) {
        musicTrackLevels[c] = musicTrackLevelsNext[c] - (musicTrackLevelsNext[c] - musicTrackLevels[c]) * 0.995f;
        Mix_VolumeChunk(musicTracks[musicTrack][c], musicTrackLevels[c]);
    }
}

void musicUpdateRealtime()
{
    timeCurrent = SDL_GetTicks();
    timeAcc += timeCurrent - timeLast;
    timeLast = timeCurrent;

    int32_t timeDelta = timeAcc - musicBeatLength;
    if (timeDelta >= 0) {
        Mix_PlayChannel(CHANNEL_TICK, musicTimeBeat, 0);
        timeAcc -= musicBeatLength;
        musicVariationLength++;
        if (musicVariationLength > 15 && (rand() % 8 == 0)) {
            if (musicVariation == MUSIC_BASIC) {
                printf("music medium low\n");
                musicSetVariation(MUSIC_MEDIUM_LOW);
            }else if (musicVariation == MUSIC_MEDIUM_LOW) {
                printf("music basic\n");
                musicSetVariation(MUSIC_BASIC);
            }
        }
    }

    musicBeatWindow = 0;
    int32_t timeToNextBeat = musicBeatLength - timeAcc;
    int32_t timeToPreviousBeat = timeAcc;
    if (timeToNextBeat < MUSIC_TOLERANCE ||
        timeToPreviousBeat < MUSIC_TOLERANCE)
        musicBeatWindow = 1;
}

/*****************************************************************************/
void musicSetVariation(int variation)
{
    musicVariationLength = 0;
    musicVariation = variation;

    if (musicTrack == 0) {
        memset(musicTrackLevelsNext, 0, 6 * sizeof(float));
        musicTrackLevelsNext[0] = 128.0f;
    }else if (musicTrack >= 1) {
        memset(musicTrackLevelsNext, 0, 6 * sizeof(float));
        if (musicVariation == MUSIC_FULL) {
            musicTrackLevelsNext[3] = 100.0f * 0.50f;
            musicTrackLevelsNext[4] = 128.0f * 1.0f;
            musicTrackLevelsNext[5] = 128.0f * 0.75f;
        }else if (musicVariation == MUSIC_MEDIUM_HIGH) {
            musicTrackLevelsNext[3] = 128.f * 1.00f;
        }else if (musicVariation == MUSIC_MEDIUM_LOW) {
            musicTrackLevelsNext[5] = 128.f * 1.00f;
            musicTrackLevelsNext[1] = 128.f * 1.00f;
        }else if (musicVariation == MUSIC_FULL) {
            musicTrackLevelsNext[3] = 100.0f * 0.50f;
            musicTrackLevelsNext[4] = 128.0f * 1.0f;
            musicTrackLevelsNext[5] = 128.0f * 0.75f;
        }else if (musicVariation == MUSIC_BASIC) {
            musicTrackLevelsNext[2] = 128.0f;
        }
    }
}
