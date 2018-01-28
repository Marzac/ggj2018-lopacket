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

#ifndef ASSETS_H
#define ASSETS_H

/*****************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>

extern SDL_Surface * skyBmp;
extern SDL_Surface * waterBmp;
extern SDL_Surface * cliffBmp;
extern SDL_Surface * gearBmp;
extern SDL_Surface * basketBmp;
extern SDL_Surface * itemBmp[4];
extern SDL_Surface * getReadyBmp;
extern SDL_Surface * vogelBmp[9];
extern SDL_Surface * vogelBackBmp[9];
extern SDL_Surface * pigsBmp[2];
extern SDL_Surface * oinkBmp[2];
extern SDL_Surface * creditBmp[2];


extern SDL_Texture * skyTxt;
extern SDL_Texture * waterTxt;
extern SDL_Texture * cliffTxt;
extern SDL_Texture * gearTxt;
extern SDL_Texture * basketTxt;
extern SDL_Texture * itemTxt[4];
extern SDL_Texture * gearTxt;
extern SDL_Texture * getReadyTxt;
extern SDL_Texture * vogelTxt[9];
extern SDL_Texture * vogelBackTxt[9];
extern SDL_Texture * pigsTxt[2];
extern SDL_Texture * oinkTxt[2];
extern SDL_Texture * creditTxt[2];

extern Mix_Chunk * musicTracks[3][6];
extern Mix_Chunk * musicKeys[3];

extern Mix_Chunk * musicTimeBeat;
extern Mix_Chunk * musicTimeDelivered;

extern Mix_Chunk * musicMonster;
extern Mix_Chunk * musicBird;
extern Mix_Chunk * musicGear;

/*****************************************************************************/
void loadAssets();
void unloadAssets();

#endif
