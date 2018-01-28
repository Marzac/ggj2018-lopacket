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

typedef struct {
    float angle;
    float angleDir;
    float x, y;
}Bird;

Bird birds[32];
int birdsNb = 0;

/*****************************************************************************/
void gameMakePacketPosition();

void gameUpdateGear();

void gameBirdsInit(int nb);
void gameBirdsUpdate();
void gameItemInit();
void gameItemUpdate();

/*****************************************************************************/
void gameInit()
{
    game.state = STATE_RUN;

    game.packetCursorNext = 0.0f;
    game.packetCursor = 0.0f;
    gameMakePacketPosition();

    game.waterHeight = 600;
    game.gearAngles[0] = 0.0f;
    game.gearAngles[1] = 0.0f;
    game.gearAnglesNext[0] = 0.0f;
    game.gearAnglesNext[1] = 0.0f;

    gameBirdsInit(3);
    gameItemInit();
}

/*****************************************************************************/
void gameUpdate()
{
    if (game.state == STATE_STEADY) {
        players[0].crankDir = 0;
        players[1].crankDir = 0;

    }else if (game.state == STATE_RUN) {
        gameUpdateGears();
        gameBirdsUpdate();

    }else if (game.state == STATE_STOLEN) {
        if (game.itemX < 0 || game.itemX > SCREEN_WIDTH)
            game.state = STATE_REWIND;
        gameUpdateGears();
        gameBirdsUpdate();

    }else if (game.state == STATE_REWIND) {
        players[0].crankDir = 0;
        players[1].crankDir = 0;
        gameBirdsUpdate();

        if (game.packetCursorNext > 0.5f) {
            game.packetCursorNext = 1.0f;
            if (game.packetCursor > 0.99f) gameInit();
        }else{
            game.packetCursorNext = 0.0f;
            if (game.packetCursor < 0.01f) gameInit();
        }
    }

    for (int i = 0; i < 2; i++)
        game.gearAngles[i] = game.gearAnglesNext[i] - (game.gearAnglesNext[i] - game.gearAngles[i]) * 0.95f;

    game.packetCursor = game.packetCursorNext + (game.packetCursor - game.packetCursorNext) * 0.95f;
    gameMakePacketPosition();
    gameItemUpdate();
}

void gameDraw()
{
    SDL_RenderClear(render);
    SDL_RenderCopy(render, skyTxt, NULL, NULL);

    float a1 = game.waterAngles[0];
    float a2 = game.waterAngles[1];

    float dx = cosf(a1) * 16.0f + cosf(a2) * 8.0f;
    float dy = sinf(a1) * 16.0f + cosf(a2) * 8.0f;
    a1 += 0.5f * 3.14f / 60.0f;
    a2 += 0.7f * 3.14f / 60.0f;
    game.waterAngles[0] = fmodf(a1, 2.0f * M_PI);
    game.waterAngles[1] = fmodf(a2, 2.0f * M_PI);

    SDL_Rect pos;
    pos.x = dx;
    pos.y = game.waterHeight + dy;
    pos.w = SCREEN_WIDTH;
    pos.h = SCREEN_HEIGHT;
    SDL_RenderCopy(render, waterTxt, NULL, &pos);
    SDL_RenderCopy(render, cliffTxt, NULL, NULL);

    SDL_Point center;
    center.x = 37;
    center.y = 37;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    pos.x = 334;
    pos.y = 152;
    pos.w = 74;
    pos.h = 74;

    float a = game.gearAngles[0];
    SDL_RenderCopyEx(render, gearTxt, NULL, &pos, a, &center, flip);

    pos.x = 1040;
    pos.y = 152;
    a = game.gearAngles[1];
    SDL_RenderCopyEx(render, gearTxt, NULL, &pos, a, &center, flip);

    pos.x = game.packetX;
    pos.y = game.packetY;
    pos.w = 51;
    pos.h = 48;
    SDL_RenderCopy(render, basketTxt, NULL, &pos);

    pos.x = game.itemX;
    pos.y = game.itemY;
    pos.w = 32;
    pos.h = 31;
    SDL_RenderCopy(render, itemTxt[0], NULL, &pos);

    static float vf = 0;
    vf = fmodf(vf + 0.2f, 9);

    pos.w = 134;
    pos.h = 175;
    for (int i = 0; i < birdsNb; i++) {
        Bird * bird = &birds[i];
        pos.x = bird->x;
        pos.y = bird->y;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (bird->angleDir < 0) flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(render, vogelTxt[(int) vf], NULL, &pos, 0, NULL, flip);
    }

    if (game.state == STATE_STEADY) {
        pos.x = 480;
        pos.y = 32;
        pos.w = 466;
        pos.h = 170;
        SDL_RenderCopy(render, getReadyTxt, NULL, &pos);
    }

    SDL_RenderPresent(render);
}

/*****************************************************************************/
void gameUpdateGears()
{
    int d1 = players[0].crankDir;
    int d2 = players[1].crankDir;
    if (d1 == d2 && d1 != 0) {
        game.packetCursorNext += (float) d1;
        players[0].crankDir = 0;
        players[1].crankDir = 0;
    }
}

void gameBirdsInit(int nb)
{
    birdsNb = nb;
    for (int i = 0; i < birdsNb; i++) {
        birds[i].angle = (float) i / birdsNb;
        birds[i].angleDir = i & 1 ? 1 : -1;
    }
}

void gameBirdsUpdate()
{
    for (int i = 0; i < birdsNb; i++) {
        Bird * bird = &birds[i];

        float a = bird->angle;
        a += 0.0005f * bird->angleDir;

        if (a > 1.0f)
            bird->angleDir = -1.0f;
        if (a < 0.0f)
            bird->angleDir = 1.0f;

        bird->angle = a;

        float dy = sinf(a * 2.0f * M_PI * 3.0f) * 120.0f;
        bird->x = a * (1366.0f + 100.0f) - 50.0f;
        bird->y = dy * bird->angleDir + 180.0f;

        float bx = bird->x + 120.0f;
        float by = bird->y + 98.0f;
        if (bird->angleDir < 0)
            bx = bird->x - 106.0f;

        float cx = bx - (game.itemX + 16);
        float cy = by - (game.itemY + 16);
        float d = cx*cx + cy*cy;
        if (d < 16.0f * 16.0f) {
            game.itemAttached = ITEM_BIRD;
            game.itemAttachedIndex = i;
            game.state = STATE_STOLEN;
        }
    }
}

/*****************************************************************************/
void gameItemInit()
{
    game.itemAttached = ITEM_BASKET;
    game.itemAttachedIndex = 0;
    game.itemX = game.packetX;
    game.itemY = game.packetY;
}

void gameItemUpdate()
{
    float px = 0.0f;
    float py = 0.0f;
    float ca = 0.0f;
    if (game.itemAttached == ITEM_BASKET) {
        px = game.packetX + 8.0f;
        py = game.packetY + 4.0f;
        ca = 0.20f;
    }else if (game.itemAttached == ITEM_BIRD) {
        Bird * bird = &birds[game.itemAttachedIndex];
        px = bird->x + 67.0f;
        py = bird->y + 100.0f;
        ca = 0.90f;
    }
    game.itemX = px - (px - game.itemX) * ca;
    game.itemY = py - (py - game.itemY) * ca;
}

/*****************************************************************************/
#define TRAVEL_LINE_LENGTH      20
#define TRAVEL_CURVE_LENGTH     2
#define TRAVEL_TOTAL_LENGTH     (TRAVEL_LINE_LENGTH * 2 + TRAVEL_CURVE_LENGTH * 2)

#define TRAVEL_START_X1         364
#define TRAVEL_START_Y1         172
#define TRAVEL_STOP_X1          1034
#define TRAVEL_STOP_Y1          164
#define TRAVEL_WHEEL_DIAMETER   44

#define TRAVEL_START_X2         TRAVEL_STOP_X1
#define TRAVEL_START_Y2         (TRAVEL_STOP_Y1 + TRAVEL_WHEEL_DIAMETER)
#define TRAVEL_STOP_X2          TRAVEL_START_X1
#define TRAVEL_STOP_Y2          (TRAVEL_START_Y1 + TRAVEL_WHEEL_DIAMETER)

void gameMakePacketPosition()
{
    float t = fmodf(game.packetCursor, TRAVEL_TOTAL_LENGTH);
    if (t < 0.0f) t += TRAVEL_TOTAL_LENGTH;

    if (t < TRAVEL_LINE_LENGTH) {
        t -= 0;
        float f = t / (float) TRAVEL_LINE_LENGTH;
        float m = 0.5f - fabs(f - 0.5f);
        game.packetX = TRAVEL_START_X1 + f * (TRAVEL_STOP_X1 - TRAVEL_START_X1);
        game.packetY = TRAVEL_START_Y1 + f * (TRAVEL_STOP_Y1 - TRAVEL_START_Y1) + m * 36.0f;
    }else if (t < TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
        t -= TRAVEL_LINE_LENGTH;
        float f = t / (float) TRAVEL_CURVE_LENGTH;
        printf("t %f\n", f);
        game.packetX = TRAVEL_STOP_X1 + 0.5f * sinf(f * M_PI) * TRAVEL_WHEEL_DIAMETER;
        game.packetY = TRAVEL_STOP_Y1 + (0.5f - cosf(f * M_PI) * 0.5f) * TRAVEL_WHEEL_DIAMETER;
    }else if (t < 2 * TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
        t -= TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH;
        float f = t / (float) TRAVEL_LINE_LENGTH;
        float m = 0.5f - fabs(f - 0.5f);
        game.packetX = TRAVEL_START_X2 + f * (TRAVEL_STOP_X2 - TRAVEL_START_X2);
        game.packetY = TRAVEL_START_Y2 + f * (TRAVEL_STOP_Y2 - TRAVEL_START_Y2) + m * 30.0f;
    }else{
        t -= 2 * TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH;
        float f = t / (float) TRAVEL_CURVE_LENGTH;
        game.packetX = TRAVEL_STOP_X2 - 0.5f * sinf(f * M_PI) * TRAVEL_WHEEL_DIAMETER;
        game.packetY = TRAVEL_STOP_Y2 - (0.5f - cosf(f * M_PI) * 0.5f) * TRAVEL_WHEEL_DIAMETER;
    }
}
