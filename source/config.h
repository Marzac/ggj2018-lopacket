#ifndef CONFIG_H
#define CONFIG_H

/*****************************************************************************/
#define SCREEN_RATIO        1
#define SCREEN_WIDTH        (1366 / SCREEN_RATIO)
#define SCREEN_HEIGHT       (768 / SCREEN_RATIO)
#define SCREEN_TOLERANCE    100

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>
extern SDL_Window * window;
extern SDL_Surface * screen;

#endif // CONFIG_H
