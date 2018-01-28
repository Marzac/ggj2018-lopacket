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
    float size;
}Bird;

Bird birds[4];
int birdsNb = 0;

Bird birdsFake[32];
int birdsFakeNb = 0;

/*****************************************************************************/
void gameMakePacketPosition();

void gameUpdateGear();

void gameBirdsInit(int nb);
void gameBirdsFakeInit(int nb);

void gameBirdsUpdate();
void gameBirdsFakeUpdate();

void gameItemInit();
void gameItemUpdate();

/*****************************************************************************/
#define MAX_LEVEL   7
const int levelBPM[MAX_LEVEL]   = {70, 100, 130, 160, 200};
const int levelBirds[MAX_LEVEL] = {3, 1, 1, 2, 2, 1, 3};

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


/*****************************************************************************/
void gameInitMenu()
{
    game.state = STATE_MENU;
    game.bpm = 120;
    game.level = -1;

    musicInit(0, 120);
}

void gameInitLevel(int level)
{
    game.state = STATE_STEADY;

    game.bpm = levelBPM[level];
    game.level = level;

    gameBirdsInit(levelBirds[level]);
    gameBirdsInitFake(16);

    playersInit();

    game.packetCursorNext = 0.0f;
    game.packetCursor = 0.0f;
    gameMakePacketPosition();

    game.waterHeight = 600;
    game.gearAngles[0] = 0.0f;
    game.gearAngles[1] = 0.0f;
    game.gearAnglesNext[0] = 0.0f;
    game.gearAnglesNext[1] = 0.0f;

    gameItemInit();

    musicInit(level + 1, game.bpm);

}

/*****************************************************************************/
void gameUpdate()
{
    playersUpdate();

    if (game.state == STATE_STEADY) {
        if (players[0].ready && players[1].ready) {
            game.state = STATE_GO;
            game.counter = 60;
        }
        gameBirdsFakeUpdate();
        gameUpdateGears();
        game.packetCursor = 0.0f;
        game.packetCursorNext = 0.0f;

    }else if (game.state == STATE_GO) {
        game.counter --;
        if (!game.counter) {
            game.state = STATE_RUN_RIGHT;
        }
        gameBirdsFakeUpdate();
        gameUpdateGears();
        game.packetCursor = 0.0f;
        game.packetCursorNext = 0.0f;

    }else if (game.state == STATE_RUN_RIGHT) {
        if (game.packetCursor > TRAVEL_LINE_LENGTH) {
            game.state = STATE_EXCHANGE;
            game.itemAttached = ITEM_PIG;
            game.itemAttachedIndex = 1;
        }
        gameUpdateGears();
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

    }else if (game.state == STATE_EXCHANGE) {
        if (game.packetCursor > TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
            game.state = STATE_RUN_LEFT;
            game.itemAttached = ITEM_BASKET;
            game.itemAttachedIndex = 0;
        }

        gameUpdateGears();
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

    }else if (game.state == STATE_RUN_LEFT) {
        if (game.packetCursor > 2.0f * TRAVEL_LINE_LENGTH + TRAVEL_CURVE_LENGTH) {
            game.state == STATE_WINWAIT;
            game.itemAttached = ITEM_PIG;
            game.itemAttachedIndex = 0;
            game.counter = 60;
        }

        gameUpdateGears();
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

    }else if (game.state == STATE_WINWAIT) {
        gameUpdateGears();
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

        game.counter --;
        if (!game.counter) {
            if (++ game.level < MAX_LEVEL) {
                game.state = STATE_WINLEVEL;
                gameInitLevel(game.level);
            }else{
                game.state = STATE_WINGAME;
            }
        }

    }else if (game.state == STATE_STOLEN_HEART ||
              game.state == STATE_STOLEN_TREFLE) {
        if (game.itemX < 0 || game.itemX > SCREEN_WIDTH)
            game.state = STATE_REWIND;
        gameUpdateGears();
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

    }else if (game.state == STATE_REWIND) {
        players[0].crankDir = 0;
        players[1].crankDir = 0;
        gameBirdsUpdate();
        gameBirdsFakeUpdate();

        game.packetCursorNext = 0.0f;
        if (game.packetCursor < 0.25f)
            gameInitLevel(game.level);
    }

    for (int i = 0; i < 2; i++)
        game.gearAngles[i] = game.gearAnglesNext[i] - (game.gearAnglesNext[i] - game.gearAngles[i]) * 0.95f;

    if (game.state == STATE_REWIND)
        game.packetCursor = game.packetCursorNext + (game.packetCursor - game.packetCursorNext) * 0.98f;
    else{
        game.packetCursor = game.packetCursorNext + (game.packetCursor - game.packetCursorNext) * 0.95f;
    }
    gameMakePacketPosition();
    gameItemUpdate();

    musicUpdate();
    gameDraw();

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

    static float vf = 0;
    vf = fmodf(vf + 0.2f, 9);

    for (int i = 0; i < birdsFakeNb; i++) {
        Bird * bird = &birdsFake[i];
        pos.x = bird->x;
        pos.y = bird->y;
        pos.w = 134 * bird->size;
        pos.h = 175 * bird->size;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (bird->angleDir < 0) flip = SDL_FLIP_HORIZONTAL;

        int f = (int) fmodf(vf + i, 9);
        SDL_RenderCopyEx(render, vogelBackTxt[f], NULL, &pos, 0, NULL, flip);
    }

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

    pos.x = 252;
    pos.y = 188;
    pos.w = 114;
    pos.h = 174;
    int pa = fmodf(game.gearAngles[0] / 22.5f, 2.0f);
    if (pa < 0) pa += 2;
    SDL_RenderCopyEx(render, pigsTxt[pa], NULL, &pos, 0, NULL, SDL_FLIP_HORIZONTAL);

    pos.x = 1084;
    pos.y = 190;
    pos.w = 114;
    pos.h = 174;
    pa = fmodf(game.gearAngles[1] / 22.5f, 2.0f);
    if (pa < 0) pa += 2;
    SDL_RenderCopyEx(render, pigsTxt[pa], NULL, &pos, 0, NULL, SDL_FLIP_NONE);

    if (game.state >= STATE_RUN_RIGHT) {
        pos.w = 134;
        pos.h = 175;
        for (int i = 0; i < birdsNb; i++) {
            Bird * bird = &birds[i];
            pos.x = bird->x;
            pos.y = bird->y;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (bird->angleDir < 0) flip = SDL_FLIP_HORIZONTAL;

            int f = (int) fmodf(vf + i, 9);
            SDL_RenderCopyEx(render, vogelTxt[f], NULL, &pos, 0, NULL, flip);
        }
    }

    int it = ((game.state < STATE_RUN_LEFT) || game.state == STATE_STOLEN_TREFLE) ? 1 : 0;
    pos.x = game.itemX;
    pos.y = game.itemY;
    pos.w = 32;
    pos.h = 31;
    SDL_RenderCopy(render, itemTxt[it], NULL, &pos);

    if (game.state == STATE_STEADY) {
        pos.x = 480;
        pos.y = 32;
        pos.w = 466;
        pos.h = 170;
        SDL_RenderCopy(render, getReadyTxt, NULL, &pos);
    }

    if (game.state <= STATE_GO) {

        if (players[0].ready) {
            pos.x = 260;
            pos.y = 212+12;
            pos.w = 82;
            pos.h = 28;
            SDL_RenderCopy(render, oinkTxt[0], NULL, &pos);
        }

        if (players[1].ready) {
            pos.x = 1112;
            pos.y = 226;
            pos.w = 89;
            pos.h = 27;
            SDL_RenderCopy(render, oinkTxt[1], NULL, &pos);
        }

    }
    SDL_RenderPresent(render);
}

/*****************************************************************************/
void gameUpdateGears()
{
    //game.packetCursorNext += 0.04;
    //return;

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
    for (int i = 0; i < nb; i++) {
        Bird * bird = &birds[i];
        bird->angle = (float) i / nb;
        bird->angleDir = i & 1 ? 1 : -1;
        bird->angle -= bird->angleDir;
    }
    birdsNb = nb;
}

void gameBirdsInitFake(int nb)
{
    for (int i = 0; i < nb; i++) {
        Bird * bird = &birdsFake[i];
        bird->angle = (float) rand() / RAND_MAX;
        bird->angleDir = i & 1 ? 1 : -1;
        bird->size = 0.3f / (1.0f + 2.0f * rand() / RAND_MAX);
    }
    birdsFakeNb = nb;
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

        float dy = sinf(a * 2.0f * M_PI * 3.0f) * 140.0f;
        bird->x = a * (1366.0f + 100.0f) - 50.0f;
        bird->y = dy * bird->angleDir + 120.0f;

    // Collision with item
        if (game.state == STATE_STOLEN_HEART ||
            game.state == STATE_STOLEN_TREFLE)
                continue;

        float bx = bird->x + 120.0f;
        float by = bird->y + 98.0f;
        if (bird->angleDir < 0)
            bx -= 106.0f;

        float cx = bx - (game.itemX + 16.0f);
        float cy = by - (game.itemY + 16.0f);
        float d = cx * cx + cy * cy;
        if (d < 24.0f * 24.0f) {
            game.itemAttached = ITEM_BIRD;
            game.itemAttachedIndex = i;
            if (game.state < STATE_RUN_LEFT)
                game.state = STATE_STOLEN_TREFLE;
            else game.state = STATE_STOLEN_HEART;
        }
    }
}


void gameBirdsFakeUpdate()
{
    for (int i = 0; i < birdsFakeNb; i++) {
        Bird * bird = &birdsFake[i];

        float a = bird->angle;
        a += 0.0005f * bird->size * bird->angleDir;
        if (a > 1.0f)
            bird->angleDir = -1.0f;
        if (a < 0.0f)
            bird->angleDir = 1.0f;
        bird->angle = a;

        float dy = sinf(a * 2.0f * M_PI * 3.0f) * 200.0f;
        bird->x = a * (1366.0f + 100.0f) - 50.0f;
        bird->y = dy * bird->angleDir + 200.0f;
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
        if (bird->angleDir > 0) px = bird->x;
        else px = bird->x + 120.0f;
        py = bird->y + 120.0f;
        ca = 0.80f;
    }else if (game.itemAttached == ITEM_PIG) {
        if (game.itemAttachedIndex == 0) {
            px = 300.0f;
            py = 305.0f;
        }else{
            px = 1150.0f;
            py = 308.0f;
        }
        ca = 0.95f;
    }

    game.itemX = px - (px - game.itemX) * ca;
    game.itemY = py - (py - game.itemY) * ca;
}


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
