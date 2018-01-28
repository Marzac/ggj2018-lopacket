/*
The MIT License (MIT)
Copyright (c) 2015-2018 The Love transmission team
Till Gilsbach, Frederic Meslin, Francisco Chaves, Christian LeFou

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
extern SDL_Renderer * render;

#endif // CONFIG_H
