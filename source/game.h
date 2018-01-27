#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/*****************************************************************************/
typedef struct {
    float packetCursor;
    float packetX;
    float packetY;
}Game;
extern Game game;

/*****************************************************************************/
void gameInit();
void gameUpdate();
void gameDraw();

#endif
