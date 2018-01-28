#ifndef MUSIC_H
#define MUSIC_H

#include <stdint.h>

/*****************************************************************************/
extern uint32_t timeCurrent;
extern uint32_t timeLast;
extern int32_t  timeAcc;

extern int musicBeatWindow;
extern int musicBeatLength;

/*****************************************************************************/
typedef enum{
    MUSIC_FULL,
    MUSIC_MEDIUM_HIGH,
    MUSIC_MEDIUM_LOW,
    MUSIC_BASIC,
}MUSIC_VARIATION;

typedef enum{
    CHANNEL_TICK,
    CHANNEL_P1K1,
    CHANNEL_P1K2,
    CHANNEL_P1K3,
    CHANNEL_P2K1,
    CHANNEL_P2K2,
    CHANNEL_P2K3,
    CHANNEL_MUSIC_TRACK1,
    CHANNEL_MUSIC_TRACK2,
    CHANNEL_MUSIC_TRACK3,
    CHANNEL_MUSIC_TRACK4,
    CHANNEL_MUSIC_TRACK5,
    CHANNEL_MUSIC_TRACK6,
}MUSIC_CHANNELS;

/*****************************************************************************/
void musicInit(int track, float bpm);
void musicUpdateRealtime();
void musicUpdate();

void musicSetVariation(int variation);

#endif
