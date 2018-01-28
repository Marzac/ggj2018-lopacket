#include "config.h"
#include "assets.h"
#include "game.h"
#include "music.h"
#include "players.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*****************************************************************************/
const int playersKeysCode[2][3] = {
    {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A},
    {SDL_SCANCODE_O, SDL_SCANCODE_L, SDL_SCANCODE_K},
};

/*****************************************************************************/
Player players[2];

/*****************************************************************************/
void playersInit()
{
    for (int p = 0; p < 2; p++) {
        Player * player = &players[p];
        memset(player->keysState, 0, sizeof(int) * 3);
        memset(player->keysStamp, 0, sizeof(int) * 3);
        player->lastKey = -1;
        player->ready = 0;
    }
}

void playersUpdate()
{
    const uint8_t * keyboard = SDL_GetKeyboardState(NULL);

    for (int p = 0; p < 2; p++) {
        Player * player = (Player *) &players[p];
        int keyNew = -1;
        for (int i = 0; i < 3; i++) {
            int k = keyboard[playersKeysCode[p][i]];
            if (k && !player->keysState[i]) {
                player->keysStamp[i] = SDL_GetTicks();
                keyNew = i;
            }
            player->keysState[i] = k;
        }
        if (keyNew < 0) continue;
        player->ready = 1;

        if (player->lastKey < 0) {
            player->lastKey = keyNew;
            continue;
        }

        int dir = keyNew - player->lastKey;
        if (dir == -2) dir = 1;
        if (dir ==  2) dir = -1;
        player->lastKey = keyNew;

        int channel = CHANNEL_P1K1 + keyNew + 3 * p;
        Mix_PlayChannel(channel, musicKeys[keyNew], 0);

        if (musicBeatWindow) {
            player->crankDir = dir;
            game.gearAnglesNext[p] += 45.0f * dir;
        }else player->crankScramble = 1;

        if (player->crankDir) printf("Player %i, crank dir %i\n", p, player->crankDir);
        if (player->crankScramble) printf("Player %i, scramble\n", p);
    }

}
