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
void musicInit(int track, float bpm);
void musicUpdate();

#endif
