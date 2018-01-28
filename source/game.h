#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/*****************************************************************************/
typedef enum{
    STATE_MENU,
    STATE_CREDIT,
    STATE_STEADY,
    STATE_GO,
    STATE_RUN_RIGHT,
    STATE_EXCHANGE,
    STATE_RUN_LEFT,
    STATE_WINWAIT,
    STATE_WINLEVEL,
    STATE_WINGAME,
    STATE_STOLEN_HEART,
    STATE_STOLEN_TREFLE,
    STATE_REWIND,
    STATE_FINISHED,
}GAME_STATE;

typedef enum{
    ITEM_BASKET,
    ITEM_BIRD,
    ITEM_PIG,
}ITEM_ATTACHEMENT;

/*****************************************************************************/
typedef struct {
    int level;
    int bpm;

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
void gameInitLevel(int level);
void gameInitMenu();

void gameUpdate();
void gameDraw();

#endif
