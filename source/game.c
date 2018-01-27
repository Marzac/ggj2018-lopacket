#include "config.h"
#include "assets.h"
#include "game.h"
#include "music.h"
#include "players.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/*****************************************************************************/
Game game;

/*****************************************************************************/
void gameMakePacketPosition();

/*****************************************************************************/
void gameInit()
{
    game.packetCursorNext = 0.0f;
    game.packetCursor = 0.0f;
    game.packetX = 0.0f;
    game.packetY = 0.0f;
}

/*****************************************************************************/
void gameUpdate()
{
    int d1 = players[0].crankDir;
    int d2 = players[1].crankDir;

    if (d1 == d2 && d1 != 0) {
        game.packetCursorNext += (float) d1;
        players[0].crankDir = 0;
        players[1].crankDir = 0;
    }

    game.packetCursor = game.packetCursorNext + (game.packetCursor - game.packetCursorNext) * 0.95f;
    gameMakePacketPosition();
}

void gameDraw()
{

    SDL_Rect pos;
    pos.x = game.packetX;
    pos.y = game.packetY;
    pos.w = 32;
    pos.h = 32;

    SDL_BlitSurface(bgBmp, NULL, screen, NULL);
    SDL_BlitSurface(packetBmp, NULL, screen, &pos);

    SDL_UpdateWindowSurface(window);
}

/*****************************************************************************/
#define TRAVEL_LINE_LENGTH      20
#define TRAVEL_CURVE_LENGTH     2
#define TRAVEL_TOTAL_LENGTH     (TRAVEL_LINE_LENGTH * 2 + TRAVEL_CURVE_LENGTH * 2)

#define TRAVEL_START_X1         368
#define TRAVEL_START_Y1         187
#define TRAVEL_STOP_X1          1076
#define TRAVEL_STOP_Y1          187
#define TRAVEL_WHEEL_DIAMETER   68

#define TRAVEL_START_X2         TRAVEL_STOP_X1
#define TRAVEL_START_Y2         (TRAVEL_STOP_Y1 + TRAVEL_WHEEL_DIAMETER)
#define TRAVEL_STOP_X2          TRAVEL_START_X1
#define TRAVEL_STOP_Y2          (TRAVEL_START_Y1 + TRAVEL_WHEEL_DIAMETER)

void gameMakePacketPosition()
{
    float t = fmodf(game.packetCursor, TRAVEL_TOTAL_LENGTH);
    if (t < TRAVEL_LINE_LENGTH) {
        t -= 0;
        float f = t / (float) TRAVEL_LINE_LENGTH;
        game.packetX = TRAVEL_START_X1 + f * (TRAVEL_STOP_X1 - TRAVEL_START_X1);
        game.packetY = TRAVEL_START_Y1 + f * (TRAVEL_STOP_Y1 - TRAVEL_START_Y1);
    }else if (t < TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
        t -= TRAVEL_LINE_LENGTH;
        float f = t / (float) TRAVEL_CURVE_LENGTH;
        game.packetX = TRAVEL_STOP_X1;
        game.packetY = TRAVEL_STOP_Y1 + f * TRAVEL_WHEEL_DIAMETER;
    }else if (t < 2 * TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
        t -= TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH;
        float f = t / (float) TRAVEL_LINE_LENGTH;
        game.packetX = TRAVEL_START_X2 + f * (TRAVEL_STOP_X2 - TRAVEL_START_X2);
        game.packetY = TRAVEL_START_Y2 + f * (TRAVEL_STOP_Y2 - TRAVEL_START_Y2);
    }else{
        t -= 2 * TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH;
        float f = t / (float) TRAVEL_CURVE_LENGTH;
        game.packetX = TRAVEL_STOP_X2;
        game.packetY = TRAVEL_STOP_Y2 - f * TRAVEL_WHEEL_DIAMETER;
    }
}
