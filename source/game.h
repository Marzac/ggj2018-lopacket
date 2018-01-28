#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/*****************************************************************************/
typedef enum{
    STATE_STEADY,
    STATE_RUN,
    STATE_STOLEN,
    STATE_REWIND,
}GAME_STATE;

typedef enum{
    ITEM_BASKET,
    ITEM_BIRD,
}ITEM_ATTACHEMENT;

/*****************************************************************************/
typedef struct {
    GAME_STATE state;
    int counter;

    float packetCursorNext;
    float packetCursor;
    float packetX;
    float packetY;

    float waterHeight;
    float waterAngles[2];

    float gearAngles[2];
    float gearAnglesNext[2];

    int itemAttached;
    int itemAttachedIndex;

    float itemX;
    float itemY;

}Game;

extern Game game;

/*****************************************************************************/
void gameInit();
void gameUpdate();
void gameDraw();

#endif
