#ifndef PLAYERS_H
#define PLAYERS_H

/*****************************************************************************/
typedef struct {
    int keysState[3];
    int keysStamp[3];
    int lastKey;

    int crankDir;
    int crankScramble;
    int ready;

}Player;

extern Player players[2];

/*****************************************************************************/
void playersInit();
void playersUpdate();

#endif
