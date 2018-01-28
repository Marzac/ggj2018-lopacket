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
    CHANNEL_MONSTERS,
    CHANNEL_OTHERS,
}MUSIC_CHANNELS;

/*****************************************************************************/
void musicInit(int track, float bpm);
void musicUpdateRealtime();
void musicUpdate();

void musicSetVariation(int variation);

#endif
