#ifndef CONFIG_H
#define CONFIG_H

/*****************************************************************************/
#define GAME_FPS            60
#define GAME_FRAME_TIME     (1000 / GAME_FPS)

#define SCREEN_RATIO        1
#define SCREEN_WIDTH        (1366 / SCREEN_RATIO)
#define SCREEN_HEIGHT       (768 / SCREEN_RATIO)
#define MUSIC_TOLERANCE     100

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>
extern SDL_Window * window;
extern SDL_Surface * screen;

#endif // CONFIG_H
